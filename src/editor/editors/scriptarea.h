#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QTextEdit>

class QCompleter;
class LineNumberArea;
class SyntaxHighlighter;

class ScriptArea : public QTextEdit
{
    Q_OBJECT

public:
    ScriptArea(QWidget *parent = 0);
    ~ScriptArea();

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    void setCompleter(QCompleter *c);
    QCompleter *completer() const;

	void setHighlighter(SyntaxHighlighter *h);
	SyntaxHighlighter *highlighter() const;

protected:
    void keyPressEvent(QKeyEvent *e);
    void focusInEvent(QFocusEvent *e);
    void resizeEvent(QResizeEvent *event);

private slots:
    void insertCompletion(const QString &completion);
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QString textUnderCursor() const;

private:
    QWidget *_lineNumberArea;
    QCompleter *_completer;
	SyntaxHighlighter *_highlighter;

};

#endif // SCRIPTEDITOR_H
