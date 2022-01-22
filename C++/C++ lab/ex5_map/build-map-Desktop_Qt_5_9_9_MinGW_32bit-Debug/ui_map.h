/********************************************************************************
** Form generated from reading UI file 'map.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAP_H
#define UI_MAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MAP
{
public:
    QAction *action_open;
    QAction *action_exit;
    QAction *action_mintrans;
    QAction *action_cor;
    QAction *action_begin_end;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menu_F;
    QMenu *menu_Q;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MAP)
    {
        if (MAP->objectName().isEmpty())
            MAP->setObjectName(QStringLiteral("MAP"));
        MAP->resize(1168, 716);
        action_open = new QAction(MAP);
        action_open->setObjectName(QStringLiteral("action_open"));
        action_open->setCheckable(true);
        action_exit = new QAction(MAP);
        action_exit->setObjectName(QStringLiteral("action_exit"));
        action_exit->setCheckable(true);
        action_mintrans = new QAction(MAP);
        action_mintrans->setObjectName(QStringLiteral("action_mintrans"));
        action_mintrans->setCheckable(true);
        action_cor = new QAction(MAP);
        action_cor->setObjectName(QStringLiteral("action_cor"));
        action_cor->setCheckable(true);
        action_begin_end = new QAction(MAP);
        action_begin_end->setObjectName(QStringLiteral("action_begin_end"));
        action_begin_end->setCheckable(true);
        centralwidget = new QWidget(MAP);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMouseTracking(true);
        graphicsView->setStyleSheet(QStringLiteral("background-image: url(:/new/prefix1/map.bmp);"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        MAP->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MAP);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1168, 26));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName(QStringLiteral("menu_F"));
        menu_Q = new QMenu(menubar);
        menu_Q->setObjectName(QStringLiteral("menu_Q"));
        MAP->setMenuBar(menubar);
        statusbar = new QStatusBar(MAP);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MAP->setStatusBar(statusbar);

        menubar->addAction(menu_F->menuAction());
        menubar->addAction(menu_Q->menuAction());
        menu_F->addAction(action_open);
        menu_F->addAction(action_cor);
        menu_F->addAction(action_begin_end);
        menu_F->addAction(action_exit);
        menu_Q->addAction(action_mintrans);

        retranslateUi(MAP);
        QObject::connect(action_mintrans, SIGNAL(triggered(bool)), MAP, SLOT(mintrans()));
        QObject::connect(action_open, SIGNAL(triggered(bool)), MAP, SLOT(loadmap()));
        QObject::connect(action_exit, SIGNAL(triggered(bool)), MAP, SLOT(closewnd()));
        QObject::connect(action_begin_end, SIGNAL(triggered(bool)), MAP, SLOT(beginEnd()));
        QObject::connect(action_cor, SIGNAL(triggered(bool)), MAP, SLOT(loadloc()));

        QMetaObject::connectSlotsByName(MAP);
    } // setupUi

    void retranslateUi(QMainWindow *MAP)
    {
        MAP->setWindowTitle(QApplication::translate("MAP", "MAP", Q_NULLPTR));
        action_open->setText(QApplication::translate("MAP", "\346\267\273\345\212\240\345\234\260\345\233\276", Q_NULLPTR));
        action_exit->setText(QApplication::translate("MAP", "\351\200\200\345\207\272", Q_NULLPTR));
        action_mintrans->setText(QApplication::translate("MAP", "\346\234\200\345\260\221\350\275\254\344\271\230", Q_NULLPTR));
        action_cor->setText(QApplication::translate("MAP", "\350\257\273\345\205\245\345\234\260\347\202\271", Q_NULLPTR));
        action_begin_end->setText(QApplication::translate("MAP", "\350\276\223\345\205\245\350\265\267\347\202\271\345\222\214\347\273\210\347\202\271", Q_NULLPTR));
        menu_F->setTitle(QApplication::translate("MAP", "\346\226\207\344\273\266(F)", Q_NULLPTR));
        menu_Q->setTitle(QApplication::translate("MAP", "\346\237\245\350\257\242(Q)", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MAP: public Ui_MAP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAP_H
