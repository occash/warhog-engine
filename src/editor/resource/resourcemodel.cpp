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
	_io->addLoader(std::make_shared<MeshResource>(nullptr));
	_io->addLoader(std::make_shared<ScriptResource>());
	_io->addLoader(std::make_shared<TextureResource>(nullptr));
}

ResourceModel::~ResourceModel()
{

}

void ResourceModel::addImporter(Importer *importer)
{
	if (!importer || _importers.contains(importer))
		return;

	_importers.append(importer);
}

Importer *ResourceModel::findImporter(const QString& ext) const
{
	foreach(Importer *importer, _importers)
	{
		QStringList suffixes = importer->suffixes();
		foreach(QString suffix, suffixes)
		{
			if (suffix == ext)
				return importer;
		}
	}

	return nullptr;
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
			return QIcon(":/icons/folder_opened");
		else if (node->nodeType() == ResourceNode::NodeType::Handle)
		{
			//TODO create resource icon map
			//const ResourceHandle *handle = dynamic_cast<const ResourceHandle *>(node);
			//if (handle && handle->type() == ScriptResource::staticType())
				return QIcon(":/icons/script");
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

Qt::ItemFlags ResourceModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsDropEnabled;

	Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable |
		Qt::ItemIsDragEnabled;
	ResourceNode *node = static_cast<ResourceNode *>(index.internalPointer());
	if (node->nodeType() == ResourceNode::NodeType::Group)
		flags |= Qt::ItemIsDropEnabled;

	return flags;
}

QVariant ResourceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QVariant();
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

int ResourceModel::rowCount(const QModelIndex &parent) const
{
	if (parent.column() > 0)
		return 0;

	const ResourceNode *parentItem;
	if (!parent.isValid())
		parentItem = _root;
	else
		parentItem = static_cast<const ResourceNode *>(parent.internalPointer());

	return parentItem->childCount();
}

int ResourceModel::columnCount(const QModelIndex &parent) const
{
	return 1;
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

bool ResourceModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
	return false;
}

bool ResourceModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	const ResourceNode *item =
		static_cast<const ResourceNode *>(parent.internalPointer());
	bool success;

	beginInsertRows(parent, position, position + rows - 1);
	//success = _io->
	endInsertRows();

	return success;
}

bool ResourceModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	return false;
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
				QString extension = fileInfo.suffix();
				Importer *importer = findImporter(extension);
				if (importer)
					canImport = true;
			}
		}
	}

	return canImport;
}

QStringList ResourceModel::mimeTypes() const
{
	QStringList mime;
	mime << "text/uri-list";
	mime << "application/x-qabstractitemmodeldatalist";
	return mime;
}

bool ResourceModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
	if (action == Qt::IgnoreAction)
		return true;

	if (!data->hasUrls())
		return false;

	int beginRow;
	if (row != -1)
		beginRow = row;
	else if (parent.isValid())
		beginRow = 0;
	else
		beginRow = rowCount(QModelIndex());

	if (!data->hasUrls())
		return false;

	QList<QUrl> urls = data->urls();
	foreach(QUrl url, urls)
	{
		if (url.isValid() && url.isLocalFile())
		{
			QString fileName = url.toLocalFile();
			QFileInfo fileInfo(fileName);
			if (fileInfo.isFile())
			{
				QString extension = fileInfo.suffix();
				Importer *importer = findImporter(extension);
				if (importer)
				{
					std::shared_ptr<Object> object = importer->import(fileName);
					ResourceNode *node = nullptr;
					if (parent.isValid())
						node = static_cast<ResourceNode *>(parent.internalPointer());
					else
						node = const_cast<ResourceNode *>(_root);

					emit beginInsertRows(parent, beginRow, beginRow + 1);
					ResourceNode *newNode = _io->createHandle(node, object->api()->name(), "new node");
					bool res = _io->save(newNode, object);
					emit endInsertRows();
					return res;
				}
			}
		}
	}

	return false;
}

Qt::DropActions ResourceModel::supportedDropActions() const
{
	return Qt::MoveAction | Qt::CopyAction;
}

QMimeData *ResourceModel::mimeData(const QModelIndexList &indexes) const
{
	return nullptr;
}
