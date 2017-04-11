#include "gradient.h"
#include "ui_gradient.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Gradient::Gradient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gradient)
{
    ui->setupUi(this);
    // C++ gradient calculation.
    // Read image
    Mat img = imread("..\\Histogram_of_Oriented_Gradients\\image\\400_317.jpg" , 1 );
    if( !img.data )
    {
        cout <<  "Could not open or find the image" << endl ;
    }
    img.convertTo(img, CV_32F, 1/255.0);

    // Calculate gradients gx, gy
    Mat gx, gy;
    Sobel(img, gx, CV_32F, 1, 0, 1);
    Sobel(img, gy, CV_32F, 0, 1, 1);


    // read an image

    // create image window named "My Image"
    namedWindow("My Image");
    // show the image on window
    imshow("My Image", img);
}

Gradient::~Gradient()
{
    delete ui;
}
