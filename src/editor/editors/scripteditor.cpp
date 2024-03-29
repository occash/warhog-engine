#include "scripteditor.h"
#include "script.h"
#include "scriptarea.h"
#include "luahighlighter.h"

#include <QVBoxLayout>

ScriptEditor::ScriptEditor(QWidget *parent)
    : QWidget(parent),
      _scriptArea(new ScriptArea(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    //ScriptArea *textEditor = new ScriptArea(this);
    _scriptArea->setFont(QFont("Consolas", 10));
    layout->addWidget(_scriptArea);
    setLayout(layout);

    addHighLighter("lua", new LuaHighlighter(this));
}

ScriptEditor::~ScriptEditor()
{
}

void ScriptEditor::addHighLighter(const QString& engine, SyntaxHighlighter *h)
{
    _syntaxes.insert(engine, h);
}

void ScriptEditor::open(Script *script)
{
    QString engine = QString::fromStdString(script->engine);
    SyntaxHighlighter *lighter = chooseEngine(engine);
    if (!lighter)
        return;

    //_currentSyntax->setDocument(nullptr);


    QString text = QString::fromStdString(script->source);
    _scriptArea->setPlainText(text);

    lighter->setDocument(_scriptArea->document());
}

SyntaxHighlighter *ScriptEditor::chooseEngine(const QString& engine)
{
    auto lighter = _syntaxes.find(engine);
    if (lighter != _syntaxes.end())
        return *lighter;

    return nullptr;
}
