#include "gradient.h"
#include "ui_gradient.h"


Gradient::Gradient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gradient)
{
    ui->setupUi(this);

    //source: http://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/sobel_derivatives/sobel_derivatives.html
    Mat src, src_gray;
    Mat grad;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    int c;

    /// Load an image
    src = imread( "..\\Histogram_of_Oriented_Gradients\\image\\400_317.jpg" );
    if( !src.data )
    {
         cout<<"Can't open image";
    }
    //Display original
    namedWindow( "Source", CV_WINDOW_AUTOSIZE );
    imshow( "Source", src );

    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    namedWindow( "After GaussianBlur", CV_WINDOW_AUTOSIZE );
    imshow( "After GaussianBlur", src );
    /// Convert it to gray
    cvtColor( src, src_gray, CV_BGR2GRAY );

    namedWindow( "After Convert to Gray", CV_WINDOW_AUTOSIZE );
    imshow( "After Convert to Gray", src_gray );
    /// Create window


    /// Generate grad_x and grad_y
    Mat grad_x_sob, grad_x_sch, grad_y;
    Mat abs_grad_x_sob, abs_grad_x_sch, abs_grad_y;

    /// Gradient X
    Scharr( src_gray, grad_x_sch, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x_sch, abs_grad_x_sch );
    Sobel( src_gray, grad_x_sob, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x_sob, abs_grad_x_sob );


    namedWindow( "After X Sobel Gradient Convert", CV_WINDOW_AUTOSIZE );
    imshow( "After X Sobel Gradient Convert", abs_grad_x_sob );
    namedWindow( "After X Scharr Gradient Convert", CV_WINDOW_AUTOSIZE );
    imshow( "After X Scharr Gradient Convert", abs_grad_x_sch );
    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );
    namedWindow( "After Y Gradient Convert", CV_WINDOW_AUTOSIZE );
    imshow( "After Y Gradient Convert", abs_grad_y );
    /// Total Gradient (approximate)
    addWeighted( abs_grad_x_sob, 0.5, abs_grad_y, 0.5, 0, grad );
    // C++ Calculate gradient magnitude and direction (in degrees)
    namedWindow( "Sobel Demo - Simple Edge Detector", CV_WINDOW_AUTOSIZE );
    imshow( "Sobel Demo - Simple Edge Detector", grad );



    // C++ gradient calculation.
    // Read image
  /*  Mat img = imread("..\\Histogram_of_Oriented_Gradients\\image\\400_317.jpg");
    img.convertTo(img, CV_32F, 1/255.0); //CV_32F is float - the pixel can have any value between 0-1.0

    // Calculate gradients gx, gy
    Mat gx, gy;
    Sobel(img, gx, CV_32F, 1, 0, 1);
    Sobel(img, gy, CV_32F, 0, 1, 1);
    imshow( "GX", gx );
    imshow( "GY", gy );
    // C++ Calculate gradient magnitude and direction (in degrees)
    Mat mag, angle;
    cartToPolar(gx, gy, mag, angle, 1);
    imshow( "MAG", angle );




    /*Mat img = imread("..\\Histogram_of_Oriented_Gradients\\image\\400_317.jpg");
    Mat grey;
    cvtColor(img, grey, CV_BGR2GRAY);

    Mat sobelx;
    Sobel(grey, sobelx, CV_32F, 1, 0);

    double minVal, maxVal;
    minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
    Mat draw;
    sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));

    namedWindow("image", CV_WINDOW_AUTOSIZE);
    imshow("image", draw);*/
}

Gradient::~Gradient()
{
    delete ui;
}


