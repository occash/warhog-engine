#ifndef RESOURCEMODEL_H
#define RESOURCEMODEL_H

#include <QAbstractItemModel>
#include <memory>

class ResourceIO;
class ResourceNode;

class Importer;

class ResourceModel : public QAbstractItemModel
{
    Q_OBJECT

public:
	ResourceModel(std::shared_ptr<ResourceIO> io, QObject *parent = nullptr);
    ~ResourceModel();

	void addImporter(Importer *importer);

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
	bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
	bool removeRows(int position, int rows,	const QModelIndex &parent = QModelIndex());

	bool canDropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent) const override;
	QStringList mimeTypes() const;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action,	int row, int column, const QModelIndex &parent);
	Qt::DropActions supportedDropActions() const;
	QMimeData *mimeData(const QModelIndexList &indexes) const;
	
private:
	Importer *findImporter(const QString& ext) const;

private:
	QList<Importer *> _importers;
	std::shared_ptr<ResourceIO> _io;
	const ResourceNode *_root;

};

#endif