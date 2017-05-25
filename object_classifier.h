#ifndef OBJECT_CLASSIFIER_H
#define OBJECT_CLASSIFIER_H

#include <QMainWindow>
#include "trainingdialog.h"
#include "testingdialog.h"

namespace Ui {
class Object_Classifier;
}

class Object_Classifier : public QMainWindow
{
    Q_OBJECT

public:
    explicit Object_Classifier(QWidget *parent = 0);
    ~Object_Classifier();

private slots:
    void on_trainButton_clicked();

    void on_testButton_clicked();


private:
    Ui::Object_Classifier *ui;
    TrainingDialog *trainingDial;
    TestingDialog *testingDial;
};

#endif // OBJECT_CLASSIFIER_H
