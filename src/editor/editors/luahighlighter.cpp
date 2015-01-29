#include "luahighlighter.h"
#include "syntaxformat.h"

#include <QStringList>

LuaHighlighter::LuaHighlighter(QObject *parent) :
	SyntaxHighlighter(parent)
{
	setSyntaxFormat(new SyntaxFormat(this));
}

LuaHighlighter::~LuaHighlighter()
{
}

void LuaHighlighter::highlightBlock(const QString &text)
{
	QRegExp number("\\b[-+]?(?:(?:\\d+\\.\\d+)|(?:\\.\\d+)|(?:\\d+\\.?))\\b");
	int index = text.indexOf(number);
	while (index >= 0) {
		setFormat(index, number.matchedLength(), syntaxFormat()->rule(SyntaxFormat::Constant));
		index = text.indexOf(number, index + number.matchedLength());
	}

	QRegExp variable("\\b[A-Za-z_]\\w*");
	index = text.indexOf(variable);
	while (index >= 0) {
		/*if (index - 6 >= 0 && text.mid(index - 6, 5) == "local")
			setFormat(index, variable.matchedLength(), syntaxFormat()->rule(SyntaxFormat::Variable));
		else*/
			setFormat(index, variable.matchedLength(), syntaxFormat()->rule(SyntaxFormat::Variable));
		index = text.indexOf(variable, index + variable.matchedLength());
	}

	QRegExp keywords("\\b(and|break|class|do|else|elseif|end|false|for|function|if|in|local|nil|not|or|repeat|return|then|true|until|while)\\b");
	index = text.indexOf(keywords);
	while (index >= 0) {
		setFormat(index, keywords.matchedLength(), syntaxFormat()->rule(SyntaxFormat::Keyword));
		index = text.indexOf(keywords, index + keywords.matchedLength());
	}

	index = text.indexOf("--");
	if (index >= 0)
		setFormat(index, text.length() - index, syntaxFormat()->rule(SyntaxFormat::Comment));

	QRegExp luaClass("\\b([A-Za-z_]\\w*)[:.][A-Za-z_]\\w*\\b");
	index = text.indexOf(luaClass);
	while (index >= 0) {
		QStringList classDef = luaClass.capturedTexts();
		setFormat(index, classDef.at(1).length(), syntaxFormat()->rule(SyntaxFormat::Class));
		index = text.indexOf(luaClass, index + luaClass.matchedLength());
	}

	QRegExp function("\\b[A-Za-z0-9_]+ *(?=\\()");
	index = text.indexOf(function);
	while (index >= 0) {
		setFormat(index, function.matchedLength(), syntaxFormat()->rule(SyntaxFormat::Function));
		index = text.indexOf(function, index + function.matchedLength());
	}

	QRegExp quotation("(\"[^\"]*\")|('[^']*')");
	index = text.indexOf(quotation);
	while (index >= 0) {
		setFormat(index, quotation.matchedLength(), syntaxFormat()->rule(SyntaxFormat::Quotation));
		index = text.indexOf(quotation, index + quotation.matchedLength());
	}

	QRegExp varassignment("(\\b[a-z_]\\w*)\\s*=\\s*.+");
	index = text.indexOf(varassignment);
	while (index >= 0) {
		QStringList assignment = varassignment.capturedTexts();
		addWord(assignment.at(1));
		index = text.indexOf(varassignment, index + varassignment.matchedLength());
	}
}

QStringList LuaHighlighter::keywords() const
{
	static QStringList keywords{
		"and", "break", "do", "else",
		"elseif", "end", "false", "for",
		"function", "if", "in", "local",
		"nil", "not", "or", "repeat",
		"return", "then", "true", "until",
		"while", "class"
	};

	return keywords;
}
