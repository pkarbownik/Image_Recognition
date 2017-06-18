#include "trainingdialog.h"

extern bool stopTrainingFlag;
bool loadWeightsFlag = false;
QString csvWeithtsToLoadPath;

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


void TrainingDialog::performTrainingProcess(QString ImgDirPath, int inputN, int hiddenN, int outputN, int maxEp, int desiredAccu, float learnRate, float momentum){

    Gradient gradient;
    gradient.inputNeurons = inputN;
    gradient.PerformHOGonDir(ImgDirPath, ui);
    srand( (unsigned int) time(0) );

    //create data set reader and load data file
    dataReader d;
    d.loadDataFile((csvDirPath + csvDataFile).toStdString().c_str(), gradient.inputNeurons, outputN);
    d.setCreationApproach( STATIC, 10 );

    //create neural network
    neuralNetwork nn(gradient.inputNeurons, hiddenN, outputN);

    //create neural network trainer
    neuralNetworkTrainer nT( &nn );
    nT.setTrainingParameters(learnRate, momentum, false);
    nT.setStoppingConditions(maxEp, desiredAccu);
    nT.enableLogging("log.csv", outputN);

    if (loadWeightsFlag)
        nn.loadWeights(csvWeithtsToLoadPath.toStdString().c_str());

    //train neural network on data sets
    nT.trainNetwork( d.getTrainingDataSet(), ui);

    //save the weights
    nn.saveWeights(csvWeightsPath.toStdString().c_str());
    return;

}

void TrainingDialog::on_pushButton_startTraining_clicked()
{
    stopTrainingFlag = false;
    performTrainingProcess(imgDirPath, 324,
                           ui->lineEdit_hiddenNeurons->text().toInt(),
                           ui->lineEdit_outputNeurons->text().toInt(),
                           ui->lineEdit_maxEpochs->text().toInt(),
                           ui->lineEdit_desiredAccuracy->text().toInt(),
                           ui->lineEdit_learningRate->text().toFloat(),
                           ui->lineEdit_momentum->text().toFloat());
}

void TrainingDialog::on_pushButton_loadTrainingDirectory_clicked()
{
    QFileDialog dialog(this);
    imgDirPath = dialog.getExistingDirectory(this, tr("Open Directory"),"../Image_Recognition/train/");
}

void TrainingDialog::on_pushButton_EXIT_clicked()
{
    this->close();
}

void TrainingDialog::on_pushButton_stopTraining_clicked()
{
    stopTrainingFlag = true;
}

void TrainingDialog::on_pushButton_loadWeights_clicked()
{
    loadWeightsFlag = true;
    csvWeithtsToLoadPath = QFileDialog::getOpenFileName(this, tr("Open Weights File"), "../Image_Recognition/csv/");
}
