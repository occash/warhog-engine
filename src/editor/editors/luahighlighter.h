#ifndef LUAHIGHLIGHTER_H
#define LUAHIGHLIGHTER_H

#include "syntaxhighlighter.h"

class LuaHighlighter : public SyntaxHighlighter
{
	Q_OBJECT

public:
	LuaHighlighter(QObject *parent = 0);
	~LuaHighlighter();

	void highlightBlock(const QString &text);
	virtual QStringList keywords() const;

};

#endif //LUAHIGHLIGHTER_H
