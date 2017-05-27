#include "trainingdialog.h"

extern bool stopTrainingFlag;

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


void TrainingDialog::performTrainingProcess(QString ImgDirPath, int inputN, int hiddenN, int outputN, int maxEp, int desiredAccu, float learnRate){
    ui->textBrowser_trainingLogs->append(QString::number(inputN));
    ui->textBrowser_trainingLogs->append(QString::number(hiddenN));
    ui->textBrowser_trainingLogs->append(QString::number(outputN));
    ui->textBrowser_trainingLogs->append(QString::number(maxEp));
    ui->textBrowser_trainingLogs->append(QString::number(desiredAccu));
    ui->textBrowser_trainingLogs->append(QString::number(learnRate));
    ImgDirPath = trainImageDirPath;
    ui->textBrowser_trainingLogs->append(ImgDirPath);

    Gradient gradient;
    gradient.PerformHOGonDir(ImgDirPath, ui);
    srand( (unsigned int) time(0) );

    //create data set reader and load data file
    dataReader d;
    d.loadDataFile((csvDirPath + csvDataFile).toStdString().c_str(), gradient.inputNeurons, outputN);
    d.setCreationApproach( STATIC, 10 );

    //create neural network
    neuralNetwork nn(gradient.inputNeurons, hiddenN, outputN);

    QString csvWeights = csvWeightsPath;
    if (csvWeights != "")
        nn.loadWeights(csvWeights.toStdString().c_str());

    //create neural network trainer
    neuralNetworkTrainer nT( &nn );
    nT.setTrainingParameters(learnRate, 0.9, false);
    nT.setStoppingConditions(maxEp, 90);
    nT.enableLogging("log.csv", 5);

    //train neural network on data sets
    for (int i=0; i < d.getNumTrainingSets(); i++ )
        nT.trainNetwork( d.getTrainingDataSet() );

    //save the weights
    nn.saveWeights(csvWeightsPath.toStdString().c_str());
}

void TrainingDialog::on_pushButton_startTraining_clicked()
{
    stopTrainingFlag = false;
    performTrainingProcess(imgDirPath,
                           ui->lineEdit_inputNeurons->text().toInt(),
                           ui->lineEdit_hiddenNeurons->text().toInt(),
                           ui->lineEdit_outputNeurons->text().toInt(),
                           ui->lineEdit_maxEpochs->text().toInt(),
                           ui->lineEdit_desiredAccuracy->text().toInt(),
                           ui->lineEdit_learningRate->text().toFloat());
}

void TrainingDialog::on_pushButton_loadTrainingDirectory_clicked()
{
    imgDirPath = QFileDialog::getExistingDirectory();
}

void TrainingDialog::on_pushButton_EXIT_clicked()
{
    this->close();
}

void TrainingDialog::on_pushButton_stopTraining_clicked()
{
    stopTrainingFlag = true;
}
