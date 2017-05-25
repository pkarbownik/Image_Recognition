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

void TestingDialog::on_pushButton_clicked()
{
    QImage img("..\\HOG_GUI\\image\\400_317.jpg");
    ui->label_img->setPixmap(QPixmap::fromImage(img));
}
