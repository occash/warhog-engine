#ifndef EDITORCREATOR_H
#define EDITORCREATOR_H

#include <QObject>

class ResourceEditor;

/*! \brief Abstract factory for concrete editor widget
*/
class EditorCreator : public QObject
{
public:
    EditorCreator(QObject *parent = 0);
    ~EditorCreator();

    virtual ResourceEditor *create() = 0;
};

#endif //EDITORCREATOR_H
