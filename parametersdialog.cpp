#include "parametersdialog.h"

ParametersDialog::ParametersDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ParametersDialog)
{
    m_ui->setupUi(this);
	this->chars = new QList<QString>();
}

ParametersDialog::~ParametersDialog() { }

void ParametersDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ParametersDialog::on_startApp_clicked()
{
	if (fileName == "")
	{
		QMessageBox box;
		box.setText("No *.pra file loaded");
		box.exec();
	}
	else
	{
		this->setBaseSize(610, 610);
		this->setMinimumSize(610, 610);
		myView = new QGraphicsView(this);
		myView->setBaseSize(610, 610);
		myView->setMinimumSize(610, 610);
		myScene = new InputScene(this, chars, m_ui->isEndless->isChecked());
		myView->setScene(myScene);
		myView->show();
		myView->setFocus();
	}
}

void ParametersDialog::on_loadButton_clicked()
{
	fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Practise File (*.pra)"));
	QString word;
	if (fileName == "")
	{
		QMessageBox box;
		box.setText("No *.pra file choosen");
		box.exec();
	}
	else
	{
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::warning(this, tr("Open file"), tr("Error, cannot load file").arg(fileName).arg(file.errorString()));
		}
		else
		{
			QTextStream fileStream(&file);
			chars->clear();
			while (!fileStream.atEnd())
			{
				fileStream >> word;
				chars->append(word);
			}
			chars->removeLast();
			m_ui->fileNameLabel->setText(fileName);
			m_ui->fileNameLabel->adjustSize();
		}
	}
}
