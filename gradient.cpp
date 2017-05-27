#include "gradient.h"

Gradient::Gradient(){}

void Gradient::PerformHOGonDir(QString ImgDirPath, Ui::TrainingDialog *ui){
    QDir dir = ImgDirPath;
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Size);
    QFileInfoList list = dir.entryInfoList();

    // Open CSV file and save outputVector
    QFile csvFile(csvDirPath + csvDataFile);
    if (!csvFile.open(QIODevice::WriteOnly | QIODevice::Text)){
        ui->textBrowser_trainingLogs->append(QString("Error while opening ").append(csvDirPath).append(csvDataFile));
        return;
    }
    QTextStream csvStream(&csvFile);

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);

        Mat img = imread(fileInfo.absoluteFilePath().toStdString(), CV_8UC1);
        printf("File: %s, width: %d, height: %d\n", fileInfo.fileName().toStdString().c_str(), img.cols, img.rows);
        cv::resize(img, img, Size(32, 32));
        int x_blocks = img.cols / BLOCK_SIZE;
        int y_blocks = img.rows / BLOCK_SIZE;
        inputNeurons = (x_blocks - 1) * (y_blocks - 1) * 36;
        ui->textBrowser_trainingLogs->append(QString("File: ").append(fileInfo.fileName()));
        QCoreApplication::processEvents();
        //printf("x_blocks: %d, y_blocks: %d\n", x_blocks, y_blocks);

        // Calculate gradients gx, gy
        Mat gx, gy;
        Sobel(img, gx, CV_32F, 1, 0, 1);
        Sobel(img, gy, CV_32F, 0, 1, 1);

        // Calculate gradient magnitude and direction (in degrees)
        Mat mag, angle;
        cartToPolar(gx, gy, mag, angle, 1);
        // Process angles values to provide 0 to 180.0 range instead of 0 to 360.0
        modulo180degrees(angle);

        // Perform histogram computations for blocks in entire image
        QVector<QVector<QVector<float>>> histogram(x_blocks, QVector<QVector<float>> (y_blocks, QVector<float>(9, 0.0)));
        imageToHistogram(histogram, mag, angle, BLOCK_SIZE, x_blocks, y_blocks);

        // Prepare final outputVector for neural network by normalizing block histograms
        QVector<float> outputVector = HOG_normalization(histogram, x_blocks, y_blocks);

        //printf("\nVector size: %d\n", outputVector.size());
        for(int i = 0; i < outputVector.size(); i++)
            csvStream << qSetRealNumberPrecision(6) << outputVector[i] << ',';
        if (fileInfo.fileName().contains("airplane"))
            csvStream << "1,0,0,0,0" << endl;
        else if (fileInfo.fileName().contains("car"))
            csvStream << "0,1,0,0,0" << endl;
        else if (fileInfo.fileName().contains("cat"))
            csvStream << "0,0,1,0,0" << endl;
        else if (fileInfo.fileName().contains("deer"))
            csvStream << "0,0,0,1,0" << endl;
        else if (fileInfo.fileName().contains("horse"))
            csvStream << "0,0,0,0,1" << endl;
    }

    csvFile.close();
}

void Gradient::PerformHOGonFile(QString imagePath){


    // Open CSV file and save outputVector
    QFile csvFile(testImageCsvPath);
    if (!csvFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream csvStream(&csvFile);

    //std::cout << qPrintable(QString("%1").arg(fileInfo.fileName()));
    //std::cout << std::endl;

    QFile fileInfo(imagePath);
    //std::cout << qPrintable(QString("%1").arg(imagePath.toStdString().c_str()));
    //printf("Image file: %s\n", imagePath.toStdString().c_str());
    Mat img = imread(imagePath.toStdString().c_str(), CV_8UC1);
    cv::resize(img, img, Size(32, 32));
    int x_blocks = img.cols / BLOCK_SIZE;
    int y_blocks = img.rows / BLOCK_SIZE;
    inputNeurons = (x_blocks - 1) * (y_blocks - 1) * 36;
    printf("File: %s, width: %d, height: %d\n", fileInfo.fileName().toStdString().c_str(), img.cols, img.rows);
    printf("x_blocks: %d, y_blocks: %d\n", x_blocks, y_blocks);

    // Calculate gradients gx, gy
    Mat gx, gy;
    Sobel(img, gx, CV_32F, 1, 0, 1);
    Sobel(img, gy, CV_32F, 0, 1, 1);

    // Calculate gradient magnitude and direction (in degrees)
    Mat mag, angle;
    cartToPolar(gx, gy, mag, angle, 1);
    // Process angles values to provide 0 to 180.0 range instead of 0 to 360.0
    modulo180degrees(angle);

    // Perform histogram computations for blocks in entire image
    QVector<QVector<QVector<float>>> histogram(x_blocks, QVector<QVector<float>> (y_blocks, QVector<float>(9, 0.0)));
    imageToHistogram(histogram, mag, angle, BLOCK_SIZE, x_blocks, y_blocks);

    // Prepare final outputVector for neural network by normalizing block histograms
    QVector<float> outputVector = HOG_normalization(histogram, x_blocks, y_blocks);

    printf("\nVector size: %d\n", outputVector.size());
    for(int i = 0; i < outputVector.size(); i++)
        csvStream << qSetRealNumberPrecision(6) << outputVector[i] << ',';
    csvStream << "1,1,1,1,1" << endl;

   csvFile.close();
}

void Gradient::imagePatchToHistogram(QVector<float> &patchHistogram, const Mat &mag, const Mat &angle, int x_block, int y_block, int blockSize){
    float lowerAngle, currentAngle, currentMag, leftFraction, rightFraction;
    int leftIndex;
    for (int row = 0; row < blockSize; row++){
        for(int col = 0; col < blockSize; col++){
            currentAngle = angle.at<float>(Point(x_block * blockSize + col, y_block * blockSize + row));
            currentMag = mag.at<float>(Point(x_block * blockSize + col, y_block * blockSize + row));
            leftIndex = int(currentAngle) / 20;
            lowerAngle = float(leftIndex) * 20.0;
            leftFraction = (currentAngle - lowerAngle) / 20.0;
            rightFraction = 1.0 - leftFraction;
            patchHistogram[leftIndex % 9] += (rightFraction * currentMag);
            patchHistogram[(leftIndex + 1) % 9] += (leftFraction * currentMag);
        }
    }
}

void Gradient::imageToHistogram(QVector<QVector<QVector<float>>> &histogram, const Mat &mag, const Mat &angle, int blockSize, int x_blocks, int y_blocks){
    for (int x_block = 0; x_block < x_blocks; x_block++){
        for(int y_block = 0; y_block < y_blocks; y_block++){
            imagePatchToHistogram(histogram[x_block][y_block], mag, angle, x_block, y_block, blockSize);
            /*
            printf("Histogram vector[%d][%d]\t", x_block, y_block);
            for(int i = 0; i < 9; i++)
                printf("%0.1f\t", histogram[x_block][y_block][i]);
            printf("\n");
            */
        }
    }
}

void Gradient::modulo180degrees(Mat &img){
    // Parallel execution using C++11 lambda.
    img.forEach<float>([](float &p, const int * position) -> void {
        if (p >= 180.0) p -= 180.0;
    });
}

QVector<float> Gradient::HOG_normalization(QVector<QVector<QVector<float>>> vector,  const int x_blocks, const int y_blocks){
    QVector<float> normalized(36 * (x_blocks - 1) * (y_blocks - 1));
    float temp = 0;
    int index = 0;
    for (int i=0; i<x_blocks-1; i++){
        for(int j=0; j<y_blocks-1; j++){
            temp = 0;
            for(int k=0; k<9; k++){
                temp+=qPow(vector[i][j][k],2);
                temp+=qPow(vector[i+1][j][k],2);
                temp+=qPow(vector[i+1][j+1][k],2);
                temp+=qPow(vector[i][j+1][k],2);
            }
            temp=qSqrt(temp);
            for(int k=0; k<9; k++){
                normalized[index]=vector[i][j][k]/temp;
                normalized[index++]=vector[i+1][j][k]/temp;
                normalized[index++]=vector[i][j+1][k]/temp;
                normalized[index++]=vector[i+1][j+1][k]/temp;
            }
        }
    }
    return normalized;

}

Gradient::~Gradient()
{
}


