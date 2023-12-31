﻿#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#pragma execution_character_set("utf-8") //防止中文乱码

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

private:
    //void onMouse(int event, int x, int y, int flags, void* userdata);


private slots:
    void on_displayImg_clicked();
    void on_detectCircle_clicked();

signals:



};
#endif // WIDGET_H
