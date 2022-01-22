/********************************************************************************
** Form generated from reading UI file 'QtWidgetsLoc.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSLOC_H
#define UI_QTWIDGETSLOC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsLoc
{
public:
    QLabel *labelWind;
    QLabel *labelLoc;
    QTextEdit *textEditLoc;
    QPushButton *pushButtonLoc;
    QPushButton *pushButtonDone;
    QPushButton *pushButtonQuit;
    QLabel *labelHits;

    void setupUi(QWidget *QtWidgetsLoc)
    {
        if (QtWidgetsLoc->objectName().isEmpty())
            QtWidgetsLoc->setObjectName(QStringLiteral("QtWidgetsLoc"));
        QtWidgetsLoc->resize(635, 292);
        labelWind = new QLabel(QtWidgetsLoc);
        labelWind->setObjectName(QStringLiteral("labelWind"));
        labelWind->setGeometry(QRect(240, 40, 161, 31));
        QFont font;
        font.setPointSize(15);
        labelWind->setFont(font);
        labelLoc = new QLabel(QtWidgetsLoc);
        labelLoc->setObjectName(QStringLiteral("labelLoc"));
        labelLoc->setGeometry(QRect(30, 130, 91, 31));
        QFont font1;
        font1.setPointSize(13);
        labelLoc->setFont(font1);
        textEditLoc = new QTextEdit(QtWidgetsLoc);
        textEditLoc->setObjectName(QStringLiteral("textEditLoc"));
        textEditLoc->setGeometry(QRect(130, 130, 351, 31));
        pushButtonLoc = new QPushButton(QtWidgetsLoc);
        pushButtonLoc->setObjectName(QStringLiteral("pushButtonLoc"));
        pushButtonLoc->setGeometry(QRect(490, 130, 93, 28));
        pushButtonDone = new QPushButton(QtWidgetsLoc);
        pushButtonDone->setObjectName(QStringLiteral("pushButtonDone"));
        pushButtonDone->setGeometry(QRect(110, 220, 93, 28));
        pushButtonQuit = new QPushButton(QtWidgetsLoc);
        pushButtonQuit->setObjectName(QStringLiteral("pushButtonQuit"));
        pushButtonQuit->setGeometry(QRect(420, 220, 93, 28));
        labelHits = new QLabel(QtWidgetsLoc);
        labelHits->setObjectName(QStringLiteral("labelHits"));
        labelHits->setGeometry(QRect(40, 260, 561, 21));

        retranslateUi(QtWidgetsLoc);
        QObject::connect(pushButtonDone, SIGNAL(clicked()), QtWidgetsLoc, SLOT(checkFile()));
        QObject::connect(pushButtonLoc, SIGNAL(clicked()), QtWidgetsLoc, SLOT(inputLoc()));
        QObject::connect(pushButtonQuit, SIGNAL(clicked()), QtWidgetsLoc, SLOT(close()));

        QMetaObject::connectSlotsByName(QtWidgetsLoc);
    } // setupUi

    void retranslateUi(QWidget *QtWidgetsLoc)
    {
        QtWidgetsLoc->setWindowTitle(QApplication::translate("QtWidgetsLoc", "\346\226\207\344\273\266\345\212\240\350\275\275", Q_NULLPTR));
        labelWind->setText(QApplication::translate("QtWidgetsLoc", "\345\234\260\347\202\271\346\226\207\344\273\266\345\212\240\350\275\275", Q_NULLPTR));
        labelLoc->setText(QApplication::translate("QtWidgetsLoc", "\345\234\260\347\202\271\346\226\207\344\273\266", Q_NULLPTR));
        pushButtonLoc->setText(QApplication::translate("QtWidgetsLoc", "\346\265\217\350\247\210...", Q_NULLPTR));
        pushButtonDone->setText(QApplication::translate("QtWidgetsLoc", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButtonQuit->setText(QApplication::translate("QtWidgetsLoc", "\351\200\200\345\207\272", Q_NULLPTR));
        labelHits->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsLoc: public Ui_QtWidgetsLoc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSLOC_H
