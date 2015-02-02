#ifndef LUAEDITOR_H
#define LUAEDITOR_H

#include <QWidget>
#include <QString>
#include <QMap>

class Script;
class ScriptArea;
class LineNumberArea;
class SyntaxHighlighter;

class ScriptEditor : public QWidget
{
    Q_OBJECT

public:
    ScriptEditor(QWidget *parent = 0);
    ~ScriptEditor();

	void addHighLighter(const QString& engine, SyntaxHighlighter *h);
	void open(Script *script);

private:
	SyntaxHighlighter *chooseEngine(const QString& engine);

private:
	ScriptArea *_scriptArea;
	LineNumberArea *_lineArea;
	SyntaxHighlighter *_currentSyntax;
	QMap<QString, SyntaxHighlighter *> _syntaxes;

};

#endif // LUAEDITOR_H
