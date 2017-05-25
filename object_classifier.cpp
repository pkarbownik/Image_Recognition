#include "object_classifier.h"
#include "ui_object_classifier.h"


Object_Classifier::Object_Classifier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Object_Classifier)
{
    ui->setupUi(this);
}

Object_Classifier::~Object_Classifier()
{
    delete ui;
}

void Object_Classifier::on_trainButton_clicked()
{
    trainingDial= new TrainingDialog();
    trainingDial->show();
}

void Object_Classifier::on_testButton_clicked()
{
    testingDial= new TestingDialog();
    testingDial->show();
}

