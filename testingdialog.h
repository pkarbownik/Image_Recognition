#ifndef TESTINGDIALOG_H
#define TESTINGDIALOG_H

#include <QWidget>
#include <QDebug>
#include <QFileDialog>
#include "ui_testingdialog.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "neuralNetwork.h"
#include "neuralNetworkTrainer.h"
#include <ctime>
#include <QApplication>
#include "globaldefs.h"
#include "gradient.h"

using namespace cv;

namespace Ui {
class TestingDialog;
}

class TestingDialog : public QWidget
{
    Q_OBJECT

public:
    explicit TestingDialog(QWidget *parent = 0);
    ~TestingDialog();

private slots:

    void on_pushButton_LoadWeights_clicked();

    void on_pushButton_SelectDierctoryToTest_clicked();

    void on_pushButton_rightArrow_clicked();

    void on_pushButton_leftArrow_clicked();

private:
    Ui::TestingDialog *ui;
    Mat src;
    QString pathToWeights;
    QString pathToTestingDirectory;
    QFileInfoList list;
    QFileInfo fileInfo;
    unsigned int img_index=0;
    void performTestingProcess(QString csvWeightsPath, QString toImagePath, int inputN = 324, int hiddenN = 500, int outputN = 5);
};

#endif // TESTINGDIALOG_H
