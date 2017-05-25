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


void TrainingDialog::performTrainingProcess(QString ImgDirPath,int inputN, int hiddenN, int outputN, int maxEp, int desiredAccu, float learnRate){
    ui->textBrowser_trainingLogs->append(QString::number(inputN));
    ui->textBrowser_trainingLogs->append(QString::number(hiddenN));
    ui->textBrowser_trainingLogs->append(ImgDirPath);
}

void TrainingDialog::on_pushButton_startTraining_clicked()
{
    performTrainingProcess(imgDirPath,ui->lineEdit_inputNeurons->text().toInt(),ui->lineEdit_hiddenNeurons->text().toInt(),ui->lineEdit_outputNeurons->text().toInt(),ui->lineEdit_maxEpochs->text().toInt(),ui->lineEdit_desiredAccuracy->text().toInt(),ui->lineEdit_learningRate->text().toFloat());
}

void TrainingDialog::on_pushButton_loadTrainingDirectory_clicked()
{
    imgDirPath = QFileDialog::getExistingDirectory();
}

void TrainingDialog::on_pushButton_EXIT_clicked()
{
    this->close();
}
