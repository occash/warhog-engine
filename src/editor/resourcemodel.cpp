#include "resourcemodel.h"

#include <resourcemanager.h>
#include <resourcegroup.h>

#include <QIcon>

ResourceModel::ResourceModel(ResourceManager *manager, QObject *parent) :
	_manager(manager),
	_root(manager->root())
{
}

ResourceModel::~ResourceModel()
{

}

QVariant ResourceModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	switch (role)
	{
	case Qt::DisplayRole:
	{
		const ResourceGroup *node =
			static_cast<const ResourceGroup *>(index.internalPointer());

		if (node == _root)
			return QVariant();

		return QString::fromStdString(node->name());
	}
	case Qt::DecorationRole:
	{
		return QIcon(":/icons/folder_opened");
	}
	default:
		return QVariant();
	}
}

Qt::ItemFlags ResourceModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ResourceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QVariant();
}

QModelIndex ResourceModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	const ResourceGroup *parentNode = nullptr;

	if (!parent.isValid())
		parentNode = _root;
	else
		parentNode = static_cast<const ResourceGroup *>(parent.internalPointer());

	if (parentNode->groupCount() <= row)
		return QModelIndex();
	else
	{
		ResourceGroup *child = parentNode->group(row);
		return createIndex(row, column, child);
	}
}

QModelIndex ResourceModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	const ResourceGroup *node =
		static_cast<const ResourceGroup *>(index.internalPointer());
	ResourceGroup *parent = node->parent();

	if (parent == _root)
		return QModelIndex();

	return createIndex(0, 0, parent);
}

int ResourceModel::rowCount(const QModelIndex &parent) const
{
	if (parent.column() > 0)
		return 0;

	const ResourceGroup *parentItem;
	if (!parent.isValid())
		parentItem = _root;
	else
		parentItem = static_cast<const ResourceGroup *>(parent.internalPointer());

	return parentItem->groupCount();
}

int ResourceModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return 1;
}
