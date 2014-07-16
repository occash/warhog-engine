#ifndef RESOURCEMODEL_H
#define RESOURCEMODEL_H

#include <QAbstractItemModel>
#include <memory>

class ResourceIO;
class ResourceNode;

class ResourceModel : public QAbstractItemModel
{
    Q_OBJECT

public:
	ResourceModel(std::shared_ptr<ResourceIO> io, QObject *parent = nullptr);
    ~ResourceModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
        const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole);
	bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex());
	bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex());
	bool insertRows(int position, int rows,	const QModelIndex &parent = QModelIndex());
	bool removeRows(int position, int rows,	const QModelIndex &parent = QModelIndex());
	
private:
	std::shared_ptr<ResourceIO> _io;
	const ResourceNode *_root;

};

#endif