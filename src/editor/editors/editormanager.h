#ifndef EDITORMANAGER_H
#define EDITORMANAGER_H

#include <QObject>

class BaseResource;
class EditorCreator;

/*! \brief This class manages resource editor tabs
*/
class EditorManager : QObject
{
public:
    EditorManager(QObject *parent = 0);
    ~EditorManager();

    void open(BaseResource *resource);
    //void close(BaseResource *);
    //void close(const QString&);
    //void close(int);

    void addCreator(const QString&, EditorCreator *);
    //void removeCreator(const QString&);
    //void removeCreator(EditorCreator *);
};

#endif //EDITORMANAGER_H
