#ifndef QTWIDGETSQU_H
#define QTWIDGETSQU_H
#pragma once

#include <QWidget>
#include "ui_QtWidgetsQU.h"
#include <string>
#include <QMainWindow>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

class QtWidgetsQU : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsQU(QWidget *parent = Q_NULLPTR);
    ~QtWidgetsQU();
    QGraphicsView* parnt;
    void myShow(QGraphicsView* p);
private:
    Ui::QtWidgetsQU ui;

private slots:
    void Done();
};
#endif // QTWIDGETSQU_H
