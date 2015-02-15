#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <entityx/Entity.h>

#include <QAbstractItemModel>

class SceneModel : public QAbstractItemModel,
    public entityx::Receiver<SceneModel>
{
    Q_OBJECT

public:
    SceneModel(entityx::EntityManager *manager,
               entityx::EventManager *events,
               QObject *parent = nullptr);
    ~SceneModel();

    void prepare();
    void receive(const entityx::EntityCreatedEvent& event);

    //Handle index
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;

    //Handle data
    QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
    entityx::EntityManager *_entities;
    entityx::EventManager *_events;
    /*  tree<entityx::Entity> _tree;
        tree<entityx::Entity>::iterator _root;*/
};

#endif // SCENEMODEL_H
