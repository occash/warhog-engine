#include "syntaxformat.h"

SyntaxFormat::SyntaxFormat(QObject *parent) :
	QObject(parent),
	_rules(7),
	_localsBold(false),
	_globalsItalic(false)
{
	//Default values
	rule(Rule::Keyword).setForeground(QColor("#00bbff"));
	rule(Rule::Class).setForeground(Qt::yellow);
	rule(Rule::Function).setForeground(QColor("#ff3300"));
	rule(Rule::Variable).setForeground(QColor("#ff6600"));
	rule(Rule::Constant).setForeground(Qt::magenta);
	rule(Rule::Comment).setForeground(Qt::green);
	rule(Rule::Quotation).setForeground(Qt::green);
}

SyntaxFormat::~SyntaxFormat()
{
}

const QTextCharFormat &SyntaxFormat::rule(Rule type) const
{
	return _rules.at(static_cast<int>(type));
}

QTextCharFormat &SyntaxFormat::rule(Rule type)
{
	return _rules[static_cast<int>(type)];
}

bool SyntaxFormat::localsInBold() const
{
	return _localsBold;
}

void SyntaxFormat::setLocalsInBold(bool b)
{
	_localsBold = b;
}

bool SyntaxFormat::globalsInItalic() const
{
	return _globalsItalic;
}

void SyntaxFormat::setGlobalsInItalic(bool b)
{
	_globalsItalic = b;
}
