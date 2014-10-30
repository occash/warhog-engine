#ifndef RESOURCEMODEL_H
#define RESOURCEMODEL_H

#include <QAbstractItemModel>
#include <QMap>
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

	void changePath();
	void addImporter(Importer *importer);

	void createGroup(const QModelIndex& parent, const QString& id);
	bool import(const QModelIndex& parent, const QString& filename);

public:
    //Indexing   
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &index) const override;

	//Data handling
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;

	//Drop
	Qt::DropActions supportedDropActions() const;
	bool canDropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent) const override;
	bool dropMimeData(const QMimeData *data, Qt::DropAction action,	int row, int column, const QModelIndex &parent);
	
	//Drag
	QStringList mimeTypes() const;
	QMimeData *mimeData(const QModelIndexList &indexes) const;

private:
	QMap<std::string, QString> _iconMap;
	QMap<QString, Importer *> _importers;
	std::shared_ptr<ResourceIO> _io;
	const ResourceNode *_root;

};

#endif