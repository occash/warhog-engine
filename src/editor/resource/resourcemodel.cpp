#include "resourcemodel.h"
#include "import/importer.h"

#include <resourceio.h>
#include <resource.h>
#include <resourcegroup.h>

#include <resource/meshresource.h>
#include <resource/scriptresource.h>
#include <resource/textureresource.h>

#include <QIcon>
#include <QMimeData>
#include <QUrl>
#include <QFileInfo>
#include <QModelIndex>

ResourceModel::ResourceModel(std::shared_ptr<ResourceIO> io, QObject *parent) :
	_io(io),
	_root(io->rootNode())
{
	//Set loaders
	_io->addLoader(std::make_shared<MeshResource>(nullptr));
	_io->addLoader(std::make_shared<ScriptResource>());
	_io->addLoader(std::make_shared<TextureResource>(nullptr));

	//set basic icon map
	_iconMap.insert(MeshResource::staticType(), ":/icons/mesh");
	_iconMap.insert(ScriptResource::staticType(), ":/icons/script");
	_iconMap.insert(TextureResource::staticType(), ":/icons/texture");
}

ResourceModel::~ResourceModel()
{

}

void ResourceModel::addImporter(Importer *importer)
{
	if (!importer)
		return;

	foreach(const QString& suffix, importer->suffixes())
		_importers.insert(suffix, importer);
}

void ResourceModel::createGroup(const QModelIndex& parent, const QString& id)
{
	ResourceNode *node = nullptr;
	if (parent.isValid())
		node = static_cast<ResourceNode *>(parent.internalPointer());
	else
		node = const_cast<ResourceNode *>(_root);

	int row = node->childCount();
	emit beginInsertRows(parent, row, row);
	static int nodeCount = 0;
	QString groupId = "New group " + nodeCount;
	_io->createGroup(node, id.toStdString());
	emit endInsertRows();
}

bool ResourceModel::import(const QModelIndex& parent, const QString& filename)
{
	QFileInfo fileInfo(filename);
	if (!fileInfo.exists() || !fileInfo.isFile())
		return false;

	//Find importer
	QString extension = fileInfo.suffix().toLower();
	Importer *importer = _importers.value(extension, nullptr);
	if (!importer)
		return false;

	//Try to import
	std::shared_ptr<Object> object = importer->import(filename);
	if (!object)
		return false;

	ResourceNode *node = nullptr;
	if (parent.isValid())
		node = static_cast<ResourceNode *>(parent.internalPointer());
	else
		node = const_cast<ResourceNode *>(_root);

	if (!node)
		return false;

	//Append to end
	int row = node->childCount();
	emit beginInsertRows(parent, row, row);
	QString nodeName = fileInfo.baseName();
	ResourceNode *newNode = _io->createHandle(node, BaseResource::Type(object->api()->name()), nodeName.toStdString());
	bool res = _io->save(newNode, object);
	emit endInsertRows();
	return res;
}

void ResourceModel::changePath()
{
	beginResetModel();
	_root = _io->rootNode();
	endResetModel();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ResourceModel::rowCount(const QModelIndex &parent) const
{
	if (parent.column() > 0)
		return 0;

	const ResourceNode *parentNode;

	if (!parent.isValid())
		parentNode = _root;
	else
		parentNode = static_cast<const ResourceNode *>(parent.internalPointer());

	if (!parentNode)
		return 0;

	return parentNode->childCount();
}

int ResourceModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

QModelIndex ResourceModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	const ResourceNode *parentNode = nullptr;

	if (!parent.isValid())
		parentNode = _root;
	else
		parentNode = static_cast<const ResourceNode *>(parent.internalPointer());

	if (!parentNode)
		return QModelIndex();

	if (parentNode->childCount() <= row)
		return QModelIndex();
	else
	{
		ResourceNode *child = parentNode->child(row);
		return createIndex(row, column, child);
	}
}

QModelIndex ResourceModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	const ResourceNode *node =
		static_cast<const ResourceNode *>(index.internalPointer());
	ResourceNode *parent = node->parent();

	if (parent == _root)
		return QModelIndex();

	return createIndex(0, 0, parent);
}

QVariant ResourceModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	const ResourceNode *node =
		static_cast<const ResourceNode *>(index.internalPointer());

	switch (role)
	{
	case Qt::DisplayRole:
	case Qt::EditRole:
	{
		if (node == _root)
			return QVariant();

		return QString::fromStdString(node->name());
	}
	case Qt::DecorationRole:
	{
		if (node->nodeType() == ResourceNode::NodeType::Group)
			return QIcon(":/icons/folder");
		else if (node->nodeType() == ResourceNode::NodeType::Handle)
		{
			const ResourceHandle *handle = dynamic_cast<const ResourceHandle *>(node);
			QString iconPath = _iconMap.value(handle->type(), "");
			if (!iconPath.isEmpty())
				return QIcon(iconPath);

			return QIcon();
		}

		return QIcon();
	}
	case Qt::ToolTipRole:
	case Qt::StatusTipRole:
	case Qt::WhatsThisRole:
	{
		if (node->nodeType() == ResourceNode::NodeType::Group)
			return QString("Group ") + QString::fromStdString(node->name());
		else if (node->nodeType() == ResourceNode::NodeType::Handle)
		{
			const ResourceHandle *handle = dynamic_cast<const ResourceHandle *>(node);
			return QString::fromStdString(handle->type()) + " " + QString::fromStdString(node->name());
		}

		return QString();
	}
	default:
		return QVariant();
	}
}

bool ResourceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid())
		return false;

	if (role == Qt::EditRole)
	{
		const ResourceNode *item =
			static_cast<const ResourceNode *>(index.internalPointer());
		return _io->renameNode(const_cast<ResourceNode *>(item), value.toString().toStdString());
	}

	return false;
}

Qt::ItemFlags ResourceModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable |
		Qt::ItemIsDragEnabled;
	ResourceNode *node = static_cast<ResourceNode *>(index.internalPointer());
	if (node->nodeType() == ResourceNode::NodeType::Group)
		flags |= Qt::ItemIsDropEnabled;
	if (node->nodeType() == ResourceNode::NodeType::Handle)
		flags |= Qt::ItemNeverHasChildren;

	return flags;
}

Qt::DropActions ResourceModel::supportedDropActions() const
{
	return Qt::MoveAction | Qt::CopyAction;
}

bool ResourceModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
	if (Qt::IgnoreAction)
		return true;

	if (!data->hasUrls())
		return false;

	bool canImport = false;
	QList<QUrl> urls = data->urls();
	foreach (QUrl url, urls)
	{
		if (url.isValid() && url.isLocalFile())
		{
			QString fileName = url.toLocalFile();
			QFileInfo fileInfo(fileName);
			if (fileInfo.isFile())
			{
				QString extension = fileInfo.suffix().toLower();
				Importer *importer = _importers.value(extension, nullptr);
				if (importer)
					canImport = true;
			}
		}
	}

	return canImport;
}

bool ResourceModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
	if (!canDropMimeData(data, action, row, column, parent))
		return false;

	if (action == Qt::IgnoreAction)
		return true;

	if (!data->hasUrls())
		return false;

	QList<QUrl> urls = data->urls();
	foreach(QUrl url, urls)
	{
		if (url.isValid() && url.isLocalFile())
		{
			QString fileName = url.toLocalFile();
			return import(parent, fileName);
		}
	}

	return false;
}

QStringList ResourceModel::mimeTypes() const
{
	QStringList mime;
	mime << "text/uri-list";
	mime << "warhog/resource-node";
	return mime;
}

QMimeData *ResourceModel::mimeData(const QModelIndexList &indexes) const
{
	if (indexes.count() <= 0)
		return 0;

	QMimeData *data = new QMimeData();
	QString format = "warhog/resource-node";
	QByteArray encoded;
	encoded.resize(indexes.size() * sizeof(void*));
	QDataStream stream(&encoded, QIODevice::WriteOnly);
	foreach(const QModelIndex& index, indexes)
	{
		void *pointer = index.internalPointer();
		char *data = (char*)&pointer;
		stream.writeBytes(data, sizeof(void*));
	}
	data->setData(format, encoded);
	return data;
}
