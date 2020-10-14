#include "MainWindow/SushiWokAdmin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SushiWokAdmin w;
    w.show();
    return a.exec();
}
