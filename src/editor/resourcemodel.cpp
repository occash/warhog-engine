#include "resourcemodel.h"

ResourceModel::ResourceModel(QObject *parent /*= nullptr*/)
{

}

ResourceModel::~ResourceModel()
{

}

QVariant ResourceModel::data(const QModelIndex &index, int role) const
{
	return QVariant();
}

Qt::ItemFlags ResourceModel::flags(const QModelIndex &index) const
{
	return 0;
}

QVariant ResourceModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	return QVariant();
}

QModelIndex ResourceModel::index(int row, int column, const QModelIndex &parent /*= QModelIndex()*/) const
{
	return QModelIndex();
}

QModelIndex ResourceModel::parent(const QModelIndex &index) const
{
	return QModelIndex();
}

int ResourceModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	if (parent.column() > 0)
		return 0;

	return 0;
	//if (!parent.isValid())
}

int ResourceModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return 1;
}
