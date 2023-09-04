#include "widget.h"
#include "ui_widget.h"
#include <opencv2/opencv.hpp>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


/*--------------@brief：点击'加载图像'按钮，显示图像-------------*/
void Widget::on_displayImg_clicked()
{
    cv::Mat inputImage = cv::imread("D:/KeXinSuo/Houghcircledetection/Img1.bmp",
                                    cv::IMREAD_COLOR);

    cv::namedWindow("Image Viewer", cv::WINDOW_NORMAL); //创建一个可调整大小的窗口
    cv::imshow("Image Viewer", inputImage); //'imshow'函数会调整图片大小以适应窗口大小？
}


/*--------------@brief：进行霍夫圆检测-------------*/
void Widget::on_detectCircle_clicked()
{
    cv::Mat inputImg = cv::imread("D:/KeXinSuo/Houghcircledetection/Img1.bmp");

    if(inputImg.empty())
    {
        qDebug()<<"Error: Could not read the image.";
    }

    //转换为灰度图像
    cv::Mat grayImage, gaussianBlurImg;
    cv::cvtColor(inputImg, grayImage, cv::COLOR_BGR2GRAY);

    //高斯滤波
    cv::GaussianBlur(grayImage, gaussianBlurImg, cv::Size(9, 9), 2, 2);

    // 设置阈值和最大值
    double thresholdValue = 50;  // 阈值
    double maxValue = 255;       // 最大值（用于高于阈值的像素）

    // 应用二值化,消除噪声,高于阈值为设置为255(白色),低于阈值被设置为0(黑色)
    cv::Mat binaryImage, cannyImg, outputImg;
    cv::threshold(gaussianBlurImg, binaryImage, thresholdValue, maxValue, cv::THRESH_BINARY);

    //边缘检测
    cv::Canny(binaryImage, cannyImg, 50, 200, 3);

    // 霍夫圆检测
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(
        cannyImg,          // 输入图像，一般为灰度图像
        circles,              // 输出的检测到的圆的信息，每一行是一个圆 [x, y, radius]
        cv::HOUGH_GRADIENT,   // 检测方法，一般为CV_HOUGH_GRADIENT
        3,                    // 累加器图像分辨率与输入图像分辨率的比率,反比，通常设置为1
        cannyImg.rows / 4, // 检测到的圆之间的最小距离
        100,                  // Canny边缘检测的高阈值，通常设置为100
        75,                   // 累加器阈值，用于确定圆心的阈值，值越大，检测到的圆越少
        290,                    // 最小圆半径
        310                   // 最大圆半径
    );

    if (circles.empty())
    {
        qDebug()<< "No circles detected." ;
    }
    else
    {
        qDebug()<< "Detected " << circles.size() << " circles." ;
    }

    inputImg.copyTo(outputImg); // 原始输入图像复制到'outputImg',在其上绘制圆
    // 在原始图像上绘制检测到的圆
    for(size_t i = 0; i < circles.size(); i++)
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        // 打印圆心坐标和半径
        qDebug() << "Circle " << i + 1 << " Center: (" << center.x << ", " << center.y << ")";
        qDebug() << "rRadius" << radius;

        // 绘制圆心
        cv::circle(outputImg, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
        // 绘制圆
        cv::circle(outputImg, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
    }

    cv::namedWindow("outputImg",cv::WINDOW_NORMAL); //创建一个可调整大小的窗口
    cv::imshow("outputImg", outputImg); //'imshow'函数会调整图片大小以适应窗口大小？
    // 保存图像为文件
    cv::imwrite("D:/KeXinSuo/Houghcircledetection/outputImage.bmp", outputImg);
}









