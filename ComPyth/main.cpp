#include "mainwindow.h"
#include "keyenterreceiver.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow * window = new MainWindow;
    COMPy * python = new COMPy(window);
    keyEnterReceiver* key = new keyEnterReceiver(python);

    a.installEventFilter(key);

    window->show();



    return a.exec();
}
