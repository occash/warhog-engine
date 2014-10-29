#ifndef PATHVALIDATOR_H
#define PATHVALIDATOR_H

#include <QValidator>

class PathValidator : public QValidator
{
	Q_OBJECT

public:
	PathValidator(QObject * parent = 0);

	void fixup(QString & input) const override;
	State validate(QString & input, int & pos) const override;

};

#endif