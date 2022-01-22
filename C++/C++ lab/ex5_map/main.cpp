#include "map.h"
#include <QtWidgets/QApplication>
#include <qdesktopwidget.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MAP w;
    w.show();
    return a.exec();
}
