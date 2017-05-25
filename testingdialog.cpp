#include "testingdialog.h"


TestingDialog::TestingDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestingDialog)
{
    ui->setupUi(this);
}

TestingDialog::~TestingDialog()
{
    delete ui;
}
