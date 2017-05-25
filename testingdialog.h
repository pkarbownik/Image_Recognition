#ifndef TESTINGDIALOG_H
#define TESTINGDIALOG_H

#include <QWidget>
#include <QDebug>
#include "ui_testingdialog.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

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
    void on_pushButton_clicked();

private:
    Ui::TestingDialog *ui;
    Mat src;
};

#endif // TESTINGDIALOG_H
