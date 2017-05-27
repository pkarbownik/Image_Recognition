#ifndef TRAININGDIALOG_H
#define TRAININGDIALOG_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include "ui_trainingdialog.h"
#include "neuralNetwork.h"
#include "neuralNetworkTrainer.h"
#include <ctime>
#include "globaldefs.h"
#include "gradient.h"

namespace Ui {
class TrainingDialog;
}

class TrainingDialog : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingDialog(QWidget *parent = 0);
    ~TrainingDialog();
    void performTrainingProcess(QString ImgDirPath, int inputN = 324, int hiddenN = 500, int outputN = 5, int maxEp = 300, int desiredAccu = 90, float learnRate = 0.002);
private slots:
    void on_pushButton_startTraining_clicked();

    void on_pushButton_loadTrainingDirectory_clicked();

    void on_pushButton_stopTraining_clicked();

    void on_pushButton_EXIT_clicked();

private:
    Ui::TrainingDialog *ui;
    QString imgDirPath = "";
};

#endif // TRAININGDIALOG_H
