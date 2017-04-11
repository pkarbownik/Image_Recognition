#ifndef GRADIENT_H
#define GRADIENT_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdarg.h>
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

private:
    Ui::Gradient *ui;
};

#endif // GRADIENT_H
