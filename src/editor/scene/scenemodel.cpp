#include "scenemodel.h"
#include <components/cameracomponent.h>
#include <components/infocomponent.h>

SceneModel::SceneModel(entityx::EntityManager *manager,
	entityx::EventManager *events,
	QObject *parent)
    : QAbstractItemModel(parent),
    _entities(manager),
	_events(events)
{
    //_root = _tree.insert(_tree.end(), entityx::Entity(&_entities, entityx::Entity::INVALID));

    /*entityx::Entity id1 = _entities->create();
    id1.assign<InfoComponent>("Main camera");
    id1.assign<CameraComponent>();
    entityx::Entity id2 = _entities->create();
    id2.assign<InfoComponent>("New Object");
    entityx::Entity id3 = _entities->create();
    id3.assign<InfoComponent>("Trololo");*/

    //_tree.append_child(_root, id1);
    //auto iter = _tree.append_child(_root, id2);
    //_tree.append_child(iter, id3);
}

SceneModel::~SceneModel()
{
}

int SceneModel::rowCount(const QModelIndex &parent) const
{
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
	{
		SceneModel *_this = const_cast<SceneModel *>(this);
		//auto view = _this->_entities->entities_with_components<InfoComponent>();
		int counter = _this->_entities->size();
		//for (auto i = view.begin(); i != view.end(); ++i)
			//counter++;

		return counter;
	}
	else
		return 0;
}

int SceneModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

QModelIndex SceneModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

	SceneModel *_this = const_cast<SceneModel *>(this);
	//auto view = _this->_entities->entities_with_components<InfoComponent>();
	int counter = _this->_entities->size();
	//for (auto i = view.begin(); i != view.end(); ++i)
		//counter++;

    if (counter <= row)
        return QModelIndex();
    else
        return createIndex(row, column, row);
}

QModelIndex SceneModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    /*tree_node_<entityx::Entity> *node =
        static_cast<tree_node_<entityx::Entity> *>(index.internalPointer());
    tree_node_<entityx::Entity> *parent = node->parent;

    tree<entityx::Entity>::iterator parentItem(parent);
    if (parentItem == _root)
        return QModelIndex();

    return createIndex(_tree.index(parentItem), 0, parent);*/

	return QModelIndex();
}

QVariant SceneModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	/*tree_node_<entityx::Entity> *node =
		static_cast<tree_node_<entityx::Entity> *>(index.internalPointer());
	tree<entityx::Entity>::iterator nodeItem(node);

	if (nodeItem == _root || !node->data.valid())
		return QVariant();*/

	entityx::Entity entity(const_cast<entityx::EntityManager *>(_entities), entityx::Entity::Id(index.row(), 1));
	auto info = entity.component<InfoComponent>();
	if (info)
	{
		std::string name = info->name;
		QString qname = QString::fromStdString(name);
		QVariant res = QVariant(qname);
		return res;
	}
	else
		return "Unnamed";
}

Qt::ItemFlags SceneModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

bool SceneModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if (!index.isValid())
		return false;

	/*if (role == Qt::EditRole)
	{
		const ResourceNode *item =
			static_cast<const ResourceNode *>(index.internalPointer());
		return _io->renameNode(const_cast<ResourceNode *>(item), value.toString().toStdString());
	}*/

	return false;
}

void SceneModel::receive(const entityx::EntityCreatedEvent& event)
{
	int row = event.entity.id().index();
	beginInsertRows(QModelIndex(), row, row);
	//QModelIndex newItem = createIndex(row, 0, row);
	endInsertRows();
}

void SceneModel::prepare()
{
	_events->subscribe<entityx::EntityCreatedEvent>(*this);
}
