#include "syntaxhighlighter.h"
#include "syntaxformat.h"

SyntaxHighlighter::SyntaxHighlighter(QObject *parent) :
    QSyntaxHighlighter(parent),
    _format(nullptr)
{
}

SyntaxHighlighter::~SyntaxHighlighter()
{
}

SyntaxFormat *SyntaxHighlighter::syntaxFormat() const
{
    return _format;
}

void SyntaxHighlighter::setSyntaxFormat(SyntaxFormat *format)
{
    _format = format;
}
