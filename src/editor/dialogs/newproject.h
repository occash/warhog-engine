#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QDialog>

class QDialogButtonBox;
class QLineEdit;
class QPushButton;

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    NewProjectDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);

    QString projectName() const;
    QString projectPath() const;

private slots:
    void pathDialog();
    void inputChanged();
    void tryAccept();

private:
    QDialogButtonBox *_buttonBox;
    QLineEdit *_nameEdit;
    QLineEdit *_pathEdit;
    QPushButton *_pathOpen;

};

#endif