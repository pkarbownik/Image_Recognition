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

void TestingDialog::performTestingProcess(QString csvWeights, QString toImagePath, int inputN, int hiddenN, int outputN){

    csvWeights = csvWeightsPath;
    Gradient gradient;
    gradient.PerformHOGonFile(toImagePath);
    srand( (unsigned int) time(0) );

    //create data set reader and load data file
    dataReader d;
    d.loadOneRowDataFile(testImageCsvPath.toStdString().c_str(), gradient.inputNeurons, outputN);
    d.setCreationApproach( STATIC );

    //create neural network
    neuralNetwork nn(gradient.inputNeurons, hiddenN, outputN);
    printf("Inputs: %d, hidden: %d, output: %d\n", gradient.inputNeurons, hiddenN, outputN);
    printf("Loading %s", csvWeights.toStdString().c_str());
    nn.loadWeights(csvWeights.toStdString().c_str());
    printf("\n");
   // printf("%f\n", d.getTrainingDataSet()->trainingSet[0]->pattern[0]);
    nn.feedForward( d.getTrainingDataSet()->trainingSet[0]->pattern );
    int bestIndex = 0;
    for (int i = 0; i < outputN; i++){
        printf("Category %s: %0.1f%%\n", categories[i].toStdString().c_str(), (nn.getOutputValue(i) * 100.0));
        if (nn.getOutputValue(i) > nn.getOutputValue(bestIndex))
            bestIndex = i;
    }
    if (nn.getOutputValue(bestIndex) > 0.8)
        ui->label_Idetified->setText("Classified as: " + categories[bestIndex] + " (" + QString("%1").arg(100.0 * nn.getOutputValue(bestIndex), 5, 'g', 4) + "%)");
    else
        ui->label_Idetified->setText("Undefined (below 80%)");
}



void TestingDialog::on_pushButton_LoadWeights_clicked()
{
    pathToWeights=QFileDialog::getOpenFileName(this,tr("Open File"),QDir::currentPath(),"CSV Files(*.csv);;");
}

void TestingDialog::on_pushButton_SelectDierctoryToTest_clicked()
{
    pathToTestingDirectory= testImageDirPath;//QFileDialog::getExistingDirectory();
    QDir dir(pathToTestingDirectory);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Size);
    list = dir.entryInfoList();
    fileInfo = list.at(img_index);
    QImage img(fileInfo.filePath());
    img = img.scaledToHeight(320);
    ui->label_img->setPixmap(QPixmap::fromImage(img));
    performTestingProcess(pathToWeights, fileInfo.filePath());
}

void TestingDialog::on_pushButton_rightArrow_clicked()
{
    if(++img_index==(list.size())) img_index=0;
    fileInfo = list.at(img_index);
    QImage img(fileInfo.filePath());
    img = img.scaledToHeight(320);
    ui->label_img->setPixmap(QPixmap::fromImage(img));
    performTestingProcess(pathToWeights, fileInfo.filePath());
}

void TestingDialog::on_pushButton_leftArrow_clicked()
{
    if(--img_index==-1) img_index=(list.size()-1);
    fileInfo = list.at(img_index);
    QImage img(fileInfo.filePath());
    img = img.scaledToHeight(320);
    ui->label_img->setPixmap(QPixmap::fromImage(img));
    performTestingProcess(pathToWeights, fileInfo.filePath());
}
