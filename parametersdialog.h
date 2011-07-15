#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QtGui/QDialog>
#include "inputscene.h"
#include <QGraphicsView>
#include "ui_parametersdialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

namespace Ui {
    class ParametersDialog;
}

class ParametersDialog : public QDialog {
    Q_OBJECT
public:
    ParametersDialog(QWidget *parent = 0);
    ~ParametersDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ParametersDialog *m_ui;
	QGraphicsView *myView;
    InputScene *myScene;
	QString fileName;
	QList<QString> *chars;

public slots:

private slots:
    void on_loadButton_clicked();
    void on_startApp_clicked();
};

#endif // PARAMETERSDIALOG_H
