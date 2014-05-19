#include "scenemodel.h"
#include <cameracomponent.h>
#include <infocomponent.h>

SceneModel::SceneModel(QObject *parent)
    : QAbstractItemModel(parent),
    _events(entityx::EventManager::make()),
    _entities(entityx::EntityManager::make(_events))
{
    _root = _tree.insert(_tree.end(), entityx::Entity(_entities, entityx::Entity::INVALID));

    entityx::Entity id1 = _entities->create();
    id1.assign<InfoComponent>("Main camera");
    id1.assign<CameraComponent>();
    entityx::Entity id2 = _entities->create();
    id2.assign<InfoComponent>("New Object");
    entityx::Entity id3 = _entities->create();
    id3.assign<InfoComponent>("Trololo");

    _tree.append_child(_root, id1);
    auto iter = _tree.append_child(_root, id2);
    _tree.append_child(iter, id3);
}

SceneModel::~SceneModel()
{

}

QVariant SceneModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    tree_node_<entityx::Entity> *node =
        static_cast<tree_node_<entityx::Entity> *>(index.internalPointer());
    tree<entityx::Entity>::iterator nodeItem(node);

    if (nodeItem == _root || !node->data.valid())
        return QVariant();

    auto info = node->data.component<InfoComponent>();
    return QString::fromStdString(info->name);
}

Qt::ItemFlags SceneModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant SceneModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

QModelIndex SceneModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    tree<entityx::Entity>::iterator parentItem;

    if (!parent.isValid())
        parentItem = _root;
    else
    {
        tree_node_<entityx::Entity> *node = 
            static_cast<tree_node_<entityx::Entity> *>(parent.internalPointer());
        parentItem = tree<entityx::Entity>::iterator(node);
    }

    
    if (parentItem.number_of_children() <= row)
        return QModelIndex();
    else
    {
        tree<entityx::Entity>::iterator childItem;
        childItem = _tree.child(parentItem, row);
        return createIndex(row, column, childItem.node);
    }
}

QModelIndex SceneModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    tree_node_<entityx::Entity> *node =
        static_cast<tree_node_<entityx::Entity> *>(index.internalPointer());
    tree_node_<entityx::Entity> *parent = node->parent;

    tree<entityx::Entity>::iterator parentItem(parent);
    if (parentItem == _root)
        return QModelIndex();

    return createIndex(_tree.index(parentItem), 0, parent);
}

int SceneModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    tree<entityx::Entity>::iterator parentItem;
    if (!parent.isValid())
        parentItem = _root;
    else
    {
        tree_node_<entityx::Entity> *node =
            static_cast<tree_node_<entityx::Entity> *>(parent.internalPointer());
        parentItem = tree<entityx::Entity>::iterator(node);
    }
    
    return parentItem.number_of_children();
}

int SceneModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}
