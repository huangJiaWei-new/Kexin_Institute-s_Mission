#include "widget.h"
#include "ui_widget.h"
#include "opencv2/opencv.hpp"
#include <QtMath>

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
    cv::Mat inputImage = cv::imread("D:/KeXinSuo/HoughLinesdetection/Img2.png",
                                    cv::IMREAD_COLOR);

    cv::namedWindow("Image Viewer", cv::WINDOW_NORMAL); //创建一个可调整大小的窗口
    cv::imshow("Image Viewer", inputImage); //'imshow'函数会调整图片大小以适应窗口大小？
}


/*--------------@brief：进行霍夫圆检测-------------*/
void Widget::on_detectLines_clicked()
{
    cv::Mat inputImg = cv::imread("D:/KeXinSuo/HoughLinesdetection/ImgLines.bmp");

    if(inputImg.empty())
    {
        qDebug()<<"Error: Could not read the image.";
    }

    //转换为灰度图像
    cv::Mat grayImage, outputImg, dst;
    cv::cvtColor(inputImg, grayImage, cv::COLOR_BGR2GRAY);

    // 设置阈值和最大值
    double thresholdValue = 55;  // 阈值
    double maxValue = 255;       // 最大值（用于高于阈值的像素）

    // 应用二值化,消除噪声,高于阈值为设置为255(白色),低于阈值被设置为0(黑色)
    cv::Mat binaryImage;
    cv::threshold(grayImage, binaryImage, thresholdValue, maxValue, cv::THRESH_BINARY);

    // Edge detection
    cv::Canny(binaryImage, outputImg, 50, 200, 3);

    // 对图像进行霍夫直线检测
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(outputImg, lines, 1, CV_PI / 90, 220);

    if (lines.empty())
    {
        qDebug()<< "No circles detected." ;
    }
    else
    {
        qDebug()<< "Detected " << lines.size() << " circles." ;
    }

    inputImg.copyTo(dst); // 原始输入图像复制到'outputImg',在其上绘制圆

    // 将极坐标线段转换为像素坐标点
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0];
        float theta = lines[i][1];
        cv::Point pt1, pt2;
        // 打印 rho 和 theta
        std::cout << "Line " << i + 1 << ": rho = " << rho << ", theta = " << theta << std::endl;
        // 将极坐标转换为直角坐标
        double a = cos(theta);
        double b = sin(theta);
        double x0 = a * rho;
        double y0 = b * rho;

        // 计算线段的两个点，考虑图像尺寸来计算缩放因子
        double scale_factor = std::max(dst.cols, dst.rows);

        // 添加边界检查，确保点在图像范围内
        pt1.x = std::max(0, std::min(pt1.x, dst.cols - 1));
        pt1.y = std::max(0, std::min(pt1.y, dst.rows - 1));
        pt2.x = std::max(0, std::min(pt2.x, dst.cols - 1));
        pt2.y = std::max(0, std::min(pt2.y, dst.rows - 1));

        // 计算线段的两个点
        pt1.x = cvRound(x0 + scale_factor*(-b));
        pt1.y = cvRound(y0 + scale_factor*(a));

        pt2.x = cvRound(x0 - scale_factor*(-b));
        pt2.y = cvRound(y0 - scale_factor*(a));

        // 打印点的坐标
        std::cout << "Line " << i + 1 << ": (" << pt1.x << ", " << pt1.y << ") - (" << pt2.x << ", " << pt2.y << ")" << std::endl;

        // 在图像上绘制线段
        cv::line(dst, pt1, pt2, cv::Scalar(0, 0, 255), 2); //用红色线段绘制在'outputImg'上

    }

    cv::namedWindow("outputImg", cv::WINDOW_NORMAL); //创建一个可调整大小的窗口
    //cv::resizeWindow("outputImg", 400, 400); // 设置窗口的大小
    cv::imshow("outputImg", dst); //'imshow'函数会调整图片大小以适应窗口大小？
}


