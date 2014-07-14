#include <QAbstractItemModel>

class ResourceManager;
class ResourceNode;

class ResourceModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    ResourceModel(ResourceManager *manager, QObject *parent = nullptr);
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
	
private:
	ResourceManager *_manager;
	const ResourceNode *_root;

};