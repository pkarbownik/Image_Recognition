#ifndef GRADIENT_H
#define GRADIENT_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdarg.h>
#include <QtMath>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <algorithm>
#include "globaldefs.h"
#include "trainingdialog.h"


#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/ml/ml.hpp>

#define BLOCK_SIZE 8

using namespace cv;
using namespace std;

class Gradient
{

public:
    Gradient();
    void Gradient::PerformHOGonDir(QString ImgDirPath, Ui::TrainingDialog *ui);
    void Gradient::PerformHOGonFile(QString imagePath);
    void modulo180degrees(Mat &angle);
    void imagePatchToHistogram(QVector<float> &patchHistogram, const Mat &mag, const Mat &angle, int x_block, int y_block, int blockSize);
    void imageToHistogram(QVector<QVector<QVector<float>>> &histogram, const Mat &mag, const Mat &angle, int blockSize, int x_blocks, int y_blocks);
    QVector<float> HOG_normalization(QVector<QVector<QVector<float>>> vector, const int x_blocks, const int y_blocks);
    int inputNeurons;

public:
    ~Gradient();
};

#endif // GRADIENT_H
