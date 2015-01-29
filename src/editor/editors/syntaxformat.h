#ifndef SYNTAXFORMAT_H
#define SYNTAXFORMAT_H

#include <QObject>
#include <QVector>
#include <QTextCharFormat>

class SyntaxFormat : public QObject
{
	Q_OBJECT

public:
	enum Rule
	{
		Keyword = 0,
		Class = 1,
		Function = 2,
		Variable = 3,
		Constant = 4,
		Comment = 5,
		Quotation = 6
	};

public:
	SyntaxFormat(QObject *parent = 0);
	~SyntaxFormat();

	const QTextCharFormat &rule(Rule type) const;
	QTextCharFormat &rule(Rule type);

	bool localsInBold() const;
	void setLocalsInBold(bool b);

	bool globalsInItalic() const;
	void setGlobalsInItalic(bool b);

private:
	QVector<QTextCharFormat> _rules;
	bool _localsBold;
	bool _globalsItalic;

};

#endif //SYNTAXFORMAT_H
