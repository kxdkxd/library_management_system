#include "mainwindow.h"
#include <QApplication>

MainWindow *mainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow = new MainWindow();
    mainWindow->show();

    return a.exec();
}
