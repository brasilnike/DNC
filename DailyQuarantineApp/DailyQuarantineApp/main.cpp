#include "DailyQuarantineApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DailyQuarantineApp w;
    w.show();
    return a.exec();
}
