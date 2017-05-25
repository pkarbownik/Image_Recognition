#ifndef TRAININGDIALOG_H
#define TRAININGDIALOG_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include "ui_trainingdialog.h"

namespace Ui {
class TrainingDialog;
}

class TrainingDialog : public QWidget
{
    Q_OBJECT

public:
    explicit TrainingDialog(QWidget *parent = 0);
    ~TrainingDialog();
    void performTrainingProcess(QString ImgDirPath, int inputN, int hiddenN, int outputN, int maxEp, int desiredAccu, float learnRate);
private slots:
    void on_pushButton_startTraining_clicked();

    void on_pushButton_loadTrainingDirectory_clicked();

private:
    QString imgDirPath="no image";
    Ui::TrainingDialog *ui;
};

#endif // TRAININGDIALOG_H
