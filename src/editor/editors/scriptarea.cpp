#include "scriptarea.h"
#include "linenumberarea.h"

#include <QCompleter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QtDebug>
#include <QApplication>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QScrollBar>
#include <QTextDocument>
#include <QTextBlock>
#include <QPainter>

ScriptArea::ScriptArea(QWidget *parent)
    : QTextEdit(parent), _completer(0)
{
    _lineNumberArea = new LineNumberArea(this);

    connect(this->document(), SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    //connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();

    QCompleter *completer = new QCompleter(this);
    //completer->setModel(modelFromFile(":/resources/wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    setCompleter(completer);
}

ScriptArea::~ScriptArea()
{

}
void ScriptArea::setCompleter(QCompleter *completer)
{
    if (!_completer)
        return;

    QObject::disconnect(_completer, 0, this, 0);
    _completer = completer;

    _completer->setWidget(this);
    _completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    _completer->setCompletionMode(QCompleter::PopupCompletion);
    _completer->setCaseSensitivity(Qt::CaseInsensitive);

    QObject::connect(_completer, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion(QString)));
}

QCompleter *ScriptArea::completer() const
{
    return _completer;
}

void ScriptArea::setHighlighter(SyntaxHighlighter *h)
{
    _highlighter = h;
}

SyntaxHighlighter *ScriptArea::highlighter() const
{
    return _highlighter;
}

void ScriptArea::insertCompletion(const QString& completion)
{
    if (_completer->widget() != this)
        return;

    QTextCursor tc = textCursor();
    int extra = completion.length() - _completer->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

QString ScriptArea::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void ScriptArea::focusInEvent(QFocusEvent *e)
{
    if (_completer)
        _completer->setWidget(this);
    QTextEdit::focusInEvent(e);
}

void ScriptArea::keyPressEvent(QKeyEvent *e)
{
    if (_completer && _completer->popup()->isVisible())
    {
        // The following keys are forwarded by the completer to the widget
        switch (e->key())
        {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
        default:
            break;
        }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space);
    if (!_completer || !isShortcut) // do not process the shortcut when we have a completer
        QTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!_completer || (ctrlOrShift && e->text().isEmpty()))
        return;

    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || e->text().isEmpty() || completionPrefix.length() < 1
                        || eow.contains(e->text().right(1))))
    {
        _completer->popup()->hide();
        return;
    }

    if (completionPrefix != _completer->completionPrefix())
    {
        _completer->setCompletionPrefix(completionPrefix);
        _completer->popup()->setCurrentIndex(_completer->completionModel()->index(0, 0));
    }

    QRect cr = cursorRect();
    cr.setWidth(_completer->popup()->sizeHintForColumn(0)
                + _completer->popup()->verticalScrollBar()->sizeHint().width());
    _completer->complete(cr); // popup it up!
}

int ScriptArea::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, document()->blockCount());
    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void ScriptArea::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void ScriptArea::updateLineNumberArea(const QRect& rect, int dy)
{
    if (dy)
        _lineNumberArea->scroll(0, dy);
    else
        _lineNumberArea->update(0, rect.y(), _lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void ScriptArea::resizeEvent(QResizeEvent *e)
{
    QTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    _lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void ScriptArea::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(60, 60, 60);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void ScriptArea::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(_lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = document()->begin();
    while (block.isValid() && block.isVisible())
    {
        QString number = QString::number(block.blockNumber() + 1);
        painter.setPen(Qt::black);
        painter.drawText(0, 10, _lineNumberArea->width(), fontMetrics().height(),
                         Qt::AlignRight, number);
        block = block.next();
    }
}
