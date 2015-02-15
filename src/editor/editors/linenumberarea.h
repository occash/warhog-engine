#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>

class ScriptArea;

class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    LineNumberArea(ScriptArea *editor);

    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    ScriptArea *codeEditor;
};

#endif //LINENUMBERAREA_H