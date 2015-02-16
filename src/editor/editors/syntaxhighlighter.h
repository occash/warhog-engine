#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class SyntaxFormat;

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    SyntaxHighlighter(QObject *parent = 0);
    ~SyntaxHighlighter();

    virtual QStringList keywords() const = 0;

    SyntaxFormat *syntaxFormat() const;
    void setSyntaxFormat(SyntaxFormat *format);

signals:
    void addWord(QString word);
    void removeWord(QString word);

private:
    SyntaxFormat *_format;

};

#endif //SYNTAXHIGHLIGHTER_H
