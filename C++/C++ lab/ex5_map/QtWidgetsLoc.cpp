#include "QtWidgetsLoc.h"
#include <QFileDialog>
#include <QMessageBox>
#include "fun.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "map.h"
using namespace std;
map<string, pair<int, int> > loc;
QtWidgetsLoc::QtWidgetsLoc(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.pushButtonLoc, SIGNAL(clicked()), this, SLOT(inputLoc()), Qt::UniqueConnection);
    connect(ui.pushButtonDone, SIGNAL(clicked()), this, SLOT(checkFile), Qt::UniqueConnection);
    connect(ui.pushButtonQuit, SIGNAL(clicked()), this, SLOT(close()), Qt::UniqueConnection);
}

void QtWidgetsLoc::myShow(QGraphicsView* p)
{
    parnt = p;
    show();
}

QtWidgetsLoc::~QtWidgetsLoc()
{
}

void QtWidgetsLoc::inputLoc() {
    ui.labelHits->setText("");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("*.txt"));
    ui.textEditLoc->setText(fileName);
}

void QtWidgetsLoc::checkFile() {
    QString  fs = ui.textEditLoc->toPlainText();
    if (fs.isEmpty())
    {
        //如果字符串为空
        ui.labelHits->setStyleSheet("color: rgb(255, 0, 0");
        ui.labelHits->setText(QString::fromLocal8Bit("操作提示：没有输入地点文件路径！"));
        ui.textEditLoc->setFocus();
        return;
    }
    //处理地点文件
    ui.labelHits->setStyleSheet("color: rgb(255, 0, 0)");	//设置操作提示信息显示颜色
    ui.labelHits->setText(QString::fromLocal8Bit("操作提示：正在处理地点文件..."));
    loadLocFile(fs.toStdString());
    ui.labelHits->setText("");
    close();
}



void loadLocFile(string fs)
{
    string filename = fs;
    string str;
    int x, y;
    char ch;

    ifstream infile;
    infile.open(filename);

    while (infile >> str)
    {
        infile >> x >> ch >> y;
        loc.insert(pair<string, pair<int, int> >(str, pair<int, int>(x, y)));
    }
    infile.close();

}
