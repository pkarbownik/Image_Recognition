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

void TestingDialog::performTestingProcess(QString csvWeightsPath, QString toImagePath, int inputN, int hiddenN, int outputN){

}



void TestingDialog::on_pushButton_LoadWeights_clicked()
{
    pathToWeights=QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath(),"CSV Files(*.csv);;");
}

void TestingDialog::on_pushButton_SelectDierctoryToTest_clicked()
{
    pathToTestingDirectory= QFileDialog::getExistingDirectory();
    QDir dir(pathToTestingDirectory);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Size);
    list = dir.entryInfoList();
     //for (int i = 0; i < list.size(); ++i) {
    fileInfo = list.at(img_index);
    QImage img(fileInfo.filePath());
    ui->label_img->setPixmap(QPixmap::fromImage(img));
    performTestingProcess(pathToWeights, fileInfo.filePath());
     //}
}

void TestingDialog::on_pushButton_rightArrow_clicked()
{
    if(++img_index==(list.size())) img_index=0;
    fileInfo = list.at(img_index);
    QImage img(fileInfo.filePath());
    ui->label_img->setPixmap(QPixmap::fromImage(img));
    performTestingProcess(pathToWeights, fileInfo.filePath());
}

void TestingDialog::on_pushButton_leftArrow_clicked()
{
    if(--img_index==-1) img_index=(list.size()-1);
    fileInfo = list.at(img_index);
    QImage img(fileInfo.filePath());
    ui->label_img->setPixmap(QPixmap::fromImage(img));
    performTestingProcess(pathToWeights, fileInfo.filePath());
}
