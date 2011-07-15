#include <QApplication>
#include "parametersdialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	ParametersDialog myDialog(0);
	myDialog.exec();
}

