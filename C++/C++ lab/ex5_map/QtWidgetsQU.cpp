#include "QtWidgetsQU.h"
#include <QFileDialog>
#include <QMessageBox>
#include "fun.h"
#include "map.h"
#include <qcompleter.h>
#include <QCommonStyle>
#include <map>
#include <string>
#include <qstring.h>
#include <QString>
#include <iostream>

using namespace std;
extern map<string, pair<int, int> > loc;
extern bool depart;
extern bool arrive;

QtWidgetsQU::QtWidgetsQU(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    if (loc.empty() == true) return;
    QStringList list;
    map<string, pair<int, int> >::iterator it;
    for (it = loc.begin(); it != loc.end(); it++) {
        list << QString::fromStdString(it->first);
    }
    ui.comboBoxBegin->addItems(list);
    ui.comboBoxEnd->addItems(list);
    QCompleter* completer = new QCompleter(list, this);
    completer->setFilterMode(Qt::MatchContains);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui.comboBoxBegin->setEditable(true);
    ui.comboBoxEnd->setEditable(true);
    ui.comboBoxBegin->setCompleter(completer);
    ui.comboBoxEnd->setCompleter(completer);
    connect(ui.pushButtonQuit, SIGNAL(clicked()), this, SLOT(close()), Qt::UniqueConnection);
    connect(ui.pushButtonDone, SIGNAL(clicked()), this, SLOT(Done()), Qt::UniqueConnection);
}

QtWidgetsQU::~QtWidgetsQU() {
}

void QtWidgetsQU::myShow(QGraphicsView* p) {
    parnt = p;
    show();
}

void QtWidgetsQU::Done() {
    QString str = ui.comboBoxBegin->currentText();
    string conStr = str.toStdString();
    QList<QGraphicsItem*> listItem = parnt->scene()->items();
    int lb = 1;
    depart = true;
    for (int i = listItem.length() - 1; i >= 0; i--) {
        MyItem* item = (MyItem*)listItem[i];
        if (item->f() == lb) {
            listItem.removeAt(i);
            delete item;
            break;
        }
    }
    parnt->scene()->addItem(new MyItem(loc[conStr].first, loc[conStr].second, lb));
    lb = 2;
    arrive = true;
    str = ui.comboBoxEnd->currentText();
    conStr = str.toStdString();
    for (int i = listItem.length() - 1; i >= 0; i--) {
        MyItem* item = (MyItem*)listItem[i];
        if (item->f() == lb) {
            listItem.removeAt(i);
            delete item;
            break;
        }
    }
    parnt->scene()->addItem(new MyItem(loc[conStr].first, loc[conStr].second, lb));
    close();
}
