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
