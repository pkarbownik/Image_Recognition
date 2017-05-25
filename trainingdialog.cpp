#include "trainingdialog.h"


TrainingDialog::TrainingDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrainingDialog)
{
    ui->setupUi(this);
}

TrainingDialog::~TrainingDialog()
{
    delete ui;
}
