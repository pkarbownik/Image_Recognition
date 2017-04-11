#include "gradient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gradient w;
    w.show();

    return a.exec();
}
