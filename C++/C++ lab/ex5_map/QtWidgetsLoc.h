#ifndef QTWIDGETSLOC_H
#define QTWIDGETSLOC_H
#pragma once
#include <QWidget>
#include "ui_QtWidgetsLoc.h"
#include <string>
#include <QMainWindow>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <map>
using namespace std;

class QtWidgetsLoc : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsLoc(QWidget *parent = Q_NULLPTR);
    ~QtWidgetsLoc();
    QGraphicsView* parnt;
    void myShow(QGraphicsView* p);

private:
    Ui::QtWidgetsLoc ui;

private slots:
    void inputLoc();
    void checkFile();
};

void loadLocFile(string fs);
#endif // QTWIDGETSLOC_H
