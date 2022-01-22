#ifndef QTWIDGETSFL_H
#define QTWIDGETSFL_H
#pragma once

#include <QWidget>
#include "map.h"
#include "ui_QtWidgetsFL.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

class QtWidgetsFL : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsFL(QWidget *parent = Q_NULLPTR);
    ~QtWidgetsFL();
    QGraphicsView* parnt;
    void myShow(QGraphicsView* p);
private:
    Ui::QtWidgetsFL ui;
private slots:
    void inputStop();
    void inputLine();
    void checkFile();
};

#endif // QTWIDGETSFL_H
