#include "gradient.h"
#include "ui_gradient.h"

//#define __DEBUG__
//#define __DISPLAY__
//#define __NAME_WINDOW__

#ifdef __DEBUG__
    #define DEBUG(x) qDebug(x);
#else
    #define DEBUG(x)
#endif

#ifdef __DISPLAY__
    #define DISPLAY(x,y) imshow( x,y);
#else
    #define DISPLAY(x,y)
#endif

#ifdef __NAME_WINDOW__
    #define NAME_WINDOW(x,y) namedWindow( x,y);
#else
    #define NAME_WINDOW(x,y)
#endif


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
    NAME_WINDOW( "Source", CV_WINDOW_AUTOSIZE );

    DISPLAY( "Source", src );
    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

    NAME_WINDOW( "After GaussianBlur", CV_WINDOW_AUTOSIZE );

    DISPLAY( "After GaussianBlur", src );


    /// Convert it to gray
    cvtColor( src, src_gray, CV_BGR2GRAY );

    NAME_WINDOW( "After Convert to Gray", CV_WINDOW_AUTOSIZE );


    DISPLAY( "After Convert to Gray", src_gray );

    /// Create window


    /// Generate grad_x and grad_y
    Mat grad_x_sob, grad_x_sch, grad_y;
    Mat abs_grad_x_sob, abs_grad_x_sch, abs_grad_y;

    /// Gradient X
    Scharr( src_gray, grad_x_sch, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x_sch, abs_grad_x_sch );
    Sobel( src_gray, grad_x_sob, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x_sob, abs_grad_x_sob );


    NAME_WINDOW( "After X Sobel Gradient Convert", CV_WINDOW_AUTOSIZE );
    DISPLAY( "After X Sobel Gradient Convert", abs_grad_x_sob );
    NAME_WINDOW( "After X Scharr Gradient Convert", CV_WINDOW_AUTOSIZE );
    DISPLAY( "After X Scharr Gradient Convert", abs_grad_x_sch );
    /// Gradient Y
    //Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );
    NAME_WINDOW( "After Y Gradient Convert", CV_WINDOW_AUTOSIZE );
    DISPLAY( "After Y Gradient Convert", abs_grad_y );
    /// Total Gradient (approximate)
    addWeighted( abs_grad_x_sob, 0.5, abs_grad_y, 0.5, 0, grad );
    // C++ Calculate gradient magnitude and direction (in degrees)
    NAME_WINDOW( "Sobel Demo - Simple Edge Detector", CV_WINDOW_AUTOSIZE );
    DISPLAY( "Sobel Demo - Simple Edge Detector", grad );


    int dim_0 = 16;
    int dim_1 = 16;
    int dim_2 = 9;
    float default_val = 0.0;
    QVector < QVector < QVector< float > > > vec(dim_0,QVector < QVector <float > > (dim_1, QVector < float > (dim_2, default_val)));

    for( int i = 0; i < dim_0; i++)
    {
        for ( int j = 0; j < dim_1; j++)
        {
            for ( int k = 0; k < dim_2; k++)
            {
                vec[i][j][k] = 4.6;
            }
        }
    }
    //qDebug()<<vec;
    qDebug()<<HOG_normalization(vec,128,128)[8];

    // C++ gradient calculation.
    // Read image
  /*  Mat img = imread("..\\Histogram_of_Oriented_Gradients\\image\\400_317.jpg");
    img.convertTo(img, CV_32F, 1/255.0); //CV_32F is float - the pixel can have any value between 0-1.0

    // Calculate gradients gx, gy
    Mat gx, gy;
    Sobel(img, gx, CV_32F, 1, 0, 1);
    Sobel(img, gy, CV_32F, 0, 1, 1);
    DISPLAY( "GX", gx );
    DISPLAY( "GY", gy );
    // C++ Calculate gradient magnitude and direction (in degrees)
    Mat mag, angle;
    cartToPolar(gx, gy, mag, angle, 1);
    DISPLAY( "MAG", angle );




    Mat img = imread("..\\Histogram_of_Oriented_Gradients\\image\\400_317.jpg");
    Mat grey;
    cvtColor(img, grey, CV_BGR2GRAY);

    Mat sobelx;
    Sobel(grey, sobelx, CV_32F, 1, 0);

    double minVal, maxVal;
    minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities
    Mat draw;
    sobelx.convertTo(draw, CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));

    NAME_WINDOW("image", CV_WINDOW_AUTOSIZE);
    DISPLAY("image", draw);*/
}

Gradient::~Gradient()
{
    delete ui;
}


QVector<float> Gradient::HOG_normalization(QVector<QVector<QVector<float>>> vector, const unsigned int size_X, const unsigned int size_Y)
{
    QVector<float> normalized(36*(size_X/8)*(size_Y/8));
    float temp = 0;
    unsigned int index = 0;
    for (unsigned int i=0; i<(size_X/8)-1; i++){
        for(unsigned int j=0; j<(size_Y/8)-1; j++){
            temp = 0;
            for(unsigned int k=0; k<9; k++){
                temp+=qPow(vector[i][j][k],2);
                temp+=qPow(vector[i+1][j][k],2);
                temp+=qPow(vector[i+1][j+1][k],2);
                temp+=qPow(vector[i][j+1][k],2);
            }
            temp=qSqrt(temp);
            for(unsigned int k=0; k<9; k++){
                normalized[index]=vector[i][j][k]/temp;
                normalized[index++]=vector[i+1][j][k]/temp;
                normalized[index++]=vector[i][j+1][k]/temp;
                normalized[index++]=vector[i+1][j+1][k]/temp;
            }
        }
    }
    return normalized;

}
