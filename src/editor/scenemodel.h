#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <entityx/Entity.h>
#include <tree.h>

#include <QAbstractItemModel>

class SceneModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    SceneModel(QObject *parent = nullptr);
    ~SceneModel();

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
    entityx::EventManager _events;
    entityx::EntityManager _entities;
    tree<entityx::Entity> _tree;
    tree<entityx::Entity>::iterator _root;
};

#endif // SCENEMODEL_H
