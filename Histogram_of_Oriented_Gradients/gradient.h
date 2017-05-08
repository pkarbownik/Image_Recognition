#ifndef GRADIENT_H
#define GRADIENT_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdarg.h>
#include <QDebug>
#include <QtMath>
using namespace cv;
using namespace std;

namespace Ui {
class Gradient;
}

class Gradient : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gradient(QWidget *parent = 0);
    ~Gradient();
    QVector<float> HOG_normalization(QVector<QVector<QVector<float>>> vector, const unsigned int size_X, const unsigned int size_Y);

private:
    Ui::Gradient *ui;
};

#endif // GRADIENT_H
