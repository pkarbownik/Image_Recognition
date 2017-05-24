#include "object_classifier.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Object_Classifier w;
    w.show();

    return a.exec();
}
