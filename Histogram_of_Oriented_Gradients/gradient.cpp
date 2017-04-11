#include "gradient.h"
#include "ui_gradient.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
/*
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>*/

using namespace cv;

Gradient::Gradient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gradient)
{
    ui->setupUi(this);

    // read an image
    Mat image = cv::imread("c://1.jpg" , 1 );
    // create image window named "My Image"
    namedWindow("My Image");
    // show the image on window
    imshow("My Image", image);
}

Gradient::~Gradient()
{
    delete ui;
}
