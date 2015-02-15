#include "pathvalidator.h"

PathValidator::PathValidator(QObject *parent) :
    QValidator(parent)
{
}

void PathValidator::fixup(QString& input) const
{
}

QValidator::State PathValidator::validate(QString& input, int& pos) const
{
    static const char notAllowedChars[] = ",^@=+{}[]~!?:&*\"|#%<>$\"'();`'";

    for (const char *c = notAllowedChars; *c; c++)
    {
        if (input.contains(QLatin1Char(*c)))
            return QValidator::Invalid;
    }

    return QValidator::Acceptable;
}
