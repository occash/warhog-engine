#include "resourcemodel.h"

#include <resourceio.h>
#include <resourcegroup.h>
#include <resource/scriptresource.h>

#include <QIcon>

ResourceModel::ResourceModel(std::shared_ptr<ResourceIO> io, QObject *parent) :
	_io(io),
	_root(io->rootNode())
{
}

ResourceModel::~ResourceModel()
{

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
			const ResourceHandle *handle = dynamic_cast<const ResourceHandle *>(node);
			if (!handle)
				return QIcon(":/icons/folder");

			if (handle->type() == ScriptResource::staticType())
				return QIcon(":/icons/script");
		}
	}
	default:
		return QVariant();
	}
}

Qt::ItemFlags ResourceModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
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

bool ResourceModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
	return false;
}

bool ResourceModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
	return false;
}

bool ResourceModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	return false;
}

bool ResourceModel::removeRows(int position, int rows, const QModelIndex &parent)
{
	return false;
}
