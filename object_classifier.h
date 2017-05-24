#ifndef OBJECT_CLASSIFIER_H
#define OBJECT_CLASSIFIER_H

#include <QMainWindow>

namespace Ui {
class Object_Classifier;
}

class Object_Classifier : public QMainWindow
{
    Q_OBJECT

public:
    explicit Object_Classifier(QWidget *parent = 0);
    ~Object_Classifier();

private:
    Ui::Object_Classifier *ui;
};

#endif // OBJECT_CLASSIFIER_H
