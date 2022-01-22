/********************************************************************************
** Form generated from reading UI file 'QtWidgetsQU.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSQU_H
#define UI_QTWIDGETSQU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsQU
{
public:
    QLabel *labelWind;
    QLabel *labelBegin;
    QPushButton *pushButtonDone;
    QPushButton *pushButtonQuit;
    QLabel *labelEnd;
    QComboBox *comboBoxBegin;
    QComboBox *comboBoxEnd;
    QLabel *labelHits;

    void setupUi(QWidget *QtWidgetsQU)
    {
        if (QtWidgetsQU->objectName().isEmpty())
            QtWidgetsQU->setObjectName(QStringLiteral("QtWidgetsQU"));
        QtWidgetsQU->resize(635, 293);
        labelWind = new QLabel(QtWidgetsQU);
        labelWind->setObjectName(QStringLiteral("labelWind"));
        labelWind->setGeometry(QRect(250, 20, 111, 31));
        QFont font;
        font.setPointSize(15);
        labelWind->setFont(font);
        labelBegin = new QLabel(QtWidgetsQU);
        labelBegin->setObjectName(QStringLiteral("labelBegin"));
        labelBegin->setGeometry(QRect(140, 90, 51, 21));
        QFont font1;
        font1.setPointSize(13);
        labelBegin->setFont(font1);
        pushButtonDone = new QPushButton(QtWidgetsQU);
        pushButtonDone->setObjectName(QStringLiteral("pushButtonDone"));
        pushButtonDone->setGeometry(QRect(90, 230, 93, 28));
        pushButtonQuit = new QPushButton(QtWidgetsQU);
        pushButtonQuit->setObjectName(QStringLiteral("pushButtonQuit"));
        pushButtonQuit->setGeometry(QRect(420, 230, 93, 28));
        labelEnd = new QLabel(QtWidgetsQU);
        labelEnd->setObjectName(QStringLiteral("labelEnd"));
        labelEnd->setGeometry(QRect(140, 150, 51, 31));
        labelEnd->setFont(font1);
        comboBoxBegin = new QComboBox(QtWidgetsQU);
        comboBoxBegin->setObjectName(QStringLiteral("comboBoxBegin"));
        comboBoxBegin->setGeometry(QRect(200, 90, 281, 31));
        comboBoxEnd = new QComboBox(QtWidgetsQU);
        comboBoxEnd->setObjectName(QStringLiteral("comboBoxEnd"));
        comboBoxEnd->setGeometry(QRect(200, 151, 281, 31));
        labelHits = new QLabel(QtWidgetsQU);
        labelHits->setObjectName(QStringLiteral("labelHits"));
        labelHits->setGeometry(QRect(60, 264, 491, 21));

        retranslateUi(QtWidgetsQU);
        QObject::connect(pushButtonDone, SIGNAL(clicked()), QtWidgetsQU, SLOT(Done()));
        QObject::connect(pushButtonQuit, SIGNAL(clicked()), QtWidgetsQU, SLOT(close()));

        QMetaObject::connectSlotsByName(QtWidgetsQU);
    } // setupUi

    void retranslateUi(QWidget *QtWidgetsQU)
    {
        QtWidgetsQU->setWindowTitle(QApplication::translate("QtWidgetsQU", "\346\226\207\344\273\266\345\212\240\350\275\275", Q_NULLPTR));
        labelWind->setText(QApplication::translate("QtWidgetsQU", "\345\234\260\347\202\271\350\276\223\345\205\245", Q_NULLPTR));
        labelBegin->setText(QApplication::translate("QtWidgetsQU", "\350\265\267\347\202\271", Q_NULLPTR));
        pushButtonDone->setText(QApplication::translate("QtWidgetsQU", "\347\241\256\345\256\232", Q_NULLPTR));
        pushButtonQuit->setText(QApplication::translate("QtWidgetsQU", "\351\200\200\345\207\272", Q_NULLPTR));
        labelEnd->setText(QApplication::translate("QtWidgetsQU", "\347\273\210\347\202\271", Q_NULLPTR));
        labelHits->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsQU: public Ui_QtWidgetsQU {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSQU_H
