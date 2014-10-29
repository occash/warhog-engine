#include "newproject.h"
#include "pathvalidator.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

NewProjectDialog::NewProjectDialog(QWidget * parent, Qt::WindowFlags f) :
	QDialog(parent, f)
{
	QVBoxLayout *verticalLayout = new QVBoxLayout(this);
	QFormLayout *formLayout = new QFormLayout(this);
	QHBoxLayout *pathLayout = new QHBoxLayout(this);

	_nameEdit = new QLineEdit(this);
	_pathEdit = new QLineEdit(this);
	_pathOpen = new QPushButton(tr("..."), this);

	PathValidator *validator = new PathValidator(this);
	_nameEdit->setValidator(validator);
	_pathEdit->setValidator(validator);

	_nameEdit->setText("New project");
	_pathEdit->setText(QStandardPaths::writableLocation(
		QStandardPaths::DocumentsLocation));

	pathLayout->addWidget(_pathEdit);
	pathLayout->addWidget(_pathOpen);

	formLayout->addRow(tr("Name"), _nameEdit);
	formLayout->addRow(tr("Location"), pathLayout);

	verticalLayout->addLayout(formLayout);

	_buttonBox = new QDialogButtonBox(
		QDialogButtonBox::Ok 
		| QDialogButtonBox::Cancel, this);
	verticalLayout->addWidget(_buttonBox);

	setLayout(verticalLayout);

	connect(_pathOpen, SIGNAL(clicked(bool)), this, SLOT(pathDialog()));
	connect(_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(_nameEdit, SIGNAL(textChanged(const QString&)),
		this, SLOT(inputChanged()));
	connect(_pathEdit, SIGNAL(textChanged(const QString&)),
		this, SLOT(inputChanged()));
}

QString NewProjectDialog::projectName() const
{
	return _nameEdit->text();
}

QString NewProjectDialog::projectPath() const
{
	return _pathEdit->text();
}

void NewProjectDialog::pathDialog()
{
	QString path = _pathEdit->text();
	if (path.isEmpty())
		path = QStandardPaths::writableLocation(
			QStandardPaths::DocumentsLocation);
	QString basePath = QFileDialog::getExistingDirectory(
		this, tr("Project location"), path);

	_pathEdit->setText(basePath);
}

void NewProjectDialog::inputChanged()
{
	QPushButton *okButton = _buttonBox->button(QDialogButtonBox::Ok);
	okButton->setEnabled(!_nameEdit->text().isEmpty()
		&& !_pathEdit->text().isEmpty());
	//TODO: more checks
}

void NewProjectDialog::tryAccept()
{
	if (QDir(_pathEdit->text()).cd(_nameEdit->text()))
	{
		int result = QMessageBox::warning(this, tr("Project warning"),
			tr("Project location already exists. Would you like override location?"),
			QMessageBox::Ok | QMessageBox::Cancel);

		if (result)
			accept();
	}
}
