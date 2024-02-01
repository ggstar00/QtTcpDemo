#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("tcp客户端");
    w.setWindowIcon(QIcon(":/images/star.svg"));
    w.show();
    return a.exec();
}
