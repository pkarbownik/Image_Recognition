#include "gradient.h"
#include "ui_gradient.h"

Gradient::Gradient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gradient)
{
    ui->setupUi(this);
}

Gradient::~Gradient()
{
    delete ui;
}
