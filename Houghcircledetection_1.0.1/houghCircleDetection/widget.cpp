#include "widget.h"
#include "ui_widget.h"
#include "opencv2/opencv.hpp"

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
    cv::Mat grayImage, outputImg;
    cv::cvtColor(inputImg, grayImage, cv::COLOR_BGR2GRAY);

    cv::GaussianBlur(grayImage, grayImage, cv::Size(9, 9), 2, 2);

    // 设置阈值和最大值
    double thresholdValue = 50; // 阈值
    double maxValue = 255;       // 最大值（用于高于阈值的像素）

    // 应用二值化
    cv::Mat binaryImage;
    cv::threshold(grayImage, binaryImage, thresholdValue, maxValue, cv::THRESH_BINARY);

//    //执行阈值处理以创建仅包含黑色区域的二值图像
//    cv::Mat binaryImage;
//    cv::threshold(grayImage, binaryImage, 1, 255, cv::THRESH_BINARY);

    //霍夫圆检测
    std::vector<cv::Vec3f> circles;
    //cv::HoughCircles(grayImage, circles, cv::HOUGH_GRADIENT_ALT, 1, grayImage.rows / 4, 200, 100, 0, 0);
    cv::HoughCircles(binaryImage, circles, cv::HOUGH_GRADIENT,
                     1.5, binaryImage.rows / 4, 100, 30, 0, 400);

    if (circles.empty())
    {
        qDebug()<< "No circles detected." ;
    }
    else
    {
        qDebug()<< "Detected " << circles.size() << " circles." ;
        // Do further processing if needed
    }

    inputImg.copyTo(outputImg); //原始输入图像复制到'outputImg',在其上绘制圆
    // 在原始图像上绘制检测到的圆
    for(size_t i = 0; i < circles.size(); i++)
    {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        cv::circle(outputImg, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0); // 绘制圆心
        cv::circle(outputImg, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0); // 绘制圆
    }

    cv::namedWindow("outputImg", cv::WINDOW_NORMAL); //创建一个可调整大小的窗口
    cv::imshow("outputImg", outputImg); //'imshow'函数会调整图片大小以适应窗口大小？
}









