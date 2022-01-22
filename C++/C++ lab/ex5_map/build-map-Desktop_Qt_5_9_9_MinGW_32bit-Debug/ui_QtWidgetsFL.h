/********************************************************************************
** Form generated from reading UI file 'QtWidgetsFL.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSFL_H
#define UI_QTWIDGETSFL_H

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

class Ui_QtWidgetsFL
{
public:
    QLabel *labelLine;
    QPushButton *pushButtonQuit;
    QPushButton *pushButtonDone;
    QTextEdit *textEditStop;
    QLabel *labelStop;
    QPushButton *pushButtonLine;
    QTextEdit *textEditLine;
    QPushButton *pushButtonStop;
    QLabel *labelWind;
    QLabel *labelHits;

    void setupUi(QWidget *QtWidgetsFL)
    {
        if (QtWidgetsFL->objectName().isEmpty())
            QtWidgetsFL->setObjectName(QStringLiteral("QtWidgetsFL"));
        QtWidgetsFL->resize(635, 292);
        QtWidgetsFL->setMinimumSize(QSize(635, 292));
        QtWidgetsFL->setMaximumSize(QSize(635, 292));
        labelLine = new QLabel(QtWidgetsFL);
        labelLine->setObjectName(QStringLiteral("labelLine"));
        labelLine->setEnabled(false);
        labelLine->setGeometry(QRect(10, 172, 81, 21));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(12);
        labelLine->setFont(font);
        pushButtonQuit = new QPushButton(QtWidgetsFL);
        pushButtonQuit->setObjectName(QStringLiteral("pushButtonQuit"));
        pushButtonQuit->setGeometry(QRect(380, 230, 75, 30));
        pushButtonDone = new QPushButton(QtWidgetsFL);
        pushButtonDone->setObjectName(QStringLiteral("pushButtonDone"));
        pushButtonDone->setGeometry(QRect(190, 230, 75, 30));
        textEditStop = new QTextEdit(QtWidgetsFL);
        textEditStop->setObjectName(QStringLiteral("textEditStop"));
        textEditStop->setGeometry(QRect(110, 100, 441, 31));
        labelStop = new QLabel(QtWidgetsFL);
        labelStop->setObjectName(QStringLiteral("labelStop"));
        labelStop->setEnabled(false);
        labelStop->setGeometry(QRect(10, 105, 81, 21));
        labelStop->setFont(font);
        pushButtonLine = new QPushButton(QtWidgetsFL);
        pushButtonLine->setObjectName(QStringLiteral("pushButtonLine"));
        pushButtonLine->setGeometry(QRect(550, 170, 75, 30));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::LinkVisited, brush);
        palette.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush);
        palette.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush);
        pushButtonLine->setPalette(palette);
        pushButtonLine->setToolTipDuration(-1);
        textEditLine = new QTextEdit(QtWidgetsFL);
        textEditLine->setObjectName(QStringLiteral("textEditLine"));
        textEditLine->setGeometry(QRect(110, 170, 441, 31));
        pushButtonStop = new QPushButton(QtWidgetsFL);
        pushButtonStop->setObjectName(QStringLiteral("pushButtonStop"));
        pushButtonStop->setGeometry(QRect(550, 100, 75, 30));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::LinkVisited, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush);
        pushButtonStop->setPalette(palette1);
        pushButtonStop->setMouseTracking(false);
        pushButtonStop->setToolTipDuration(-1);
        pushButtonStop->setCheckable(false);
        labelWind = new QLabel(QtWidgetsFL);
        labelWind->setObjectName(QStringLiteral("labelWind"));
        labelWind->setGeometry(QRect(180, 30, 281, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Agency FB"));
        font1.setPointSize(18);
        labelWind->setFont(font1);
        labelHits = new QLabel(QtWidgetsFL);
        labelHits->setObjectName(QStringLiteral("labelHits"));
        labelHits->setEnabled(false);
        labelHits->setGeometry(QRect(0, 270, 631, 21));
        labelHits->setFont(font);

        retranslateUi(QtWidgetsFL);
        QObject::connect(pushButtonStop, SIGNAL(clicked()), QtWidgetsFL, SLOT(inputStop()));
        QObject::connect(pushButtonLine, SIGNAL(clicked()), QtWidgetsFL, SLOT(inputLine()));
        QObject::connect(pushButtonDone, SIGNAL(clicked()), QtWidgetsFL, SLOT(checkFile()));
        QObject::connect(pushButtonQuit, SIGNAL(clicked()), QtWidgetsFL, SLOT(close()));

        QMetaObject::connectSlotsByName(QtWidgetsFL);
    } // setupUi

    void retranslateUi(QWidget *QtWidgetsFL)
    {
        QtWidgetsFL->setWindowTitle(QApplication::translate("QtWidgetsFL", "\346\226\207\344\273\266\345\212\240\350\275\275", Q_NULLPTR));
        labelLine->setText(QApplication::translate("QtWidgetsFL", "\347\272\277\350\267\257\346\226\207\344\273\266", Q_NULLPTR));
        pushButtonQuit->setText(QApplication::translate("QtWidgetsFL", "\351\200\200\345\207\272", Q_NULLPTR));
        pushButtonDone->setText(QApplication::translate("QtWidgetsFL", "\347\241\256\345\256\232", Q_NULLPTR));
        //textEditStop->setMarkdown(QString());
        textEditStop->setHtml(QApplication::translate("QtWidgetsFL", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", Q_NULLPTR));
        labelStop->setText(QApplication::translate("QtWidgetsFL", "\347\253\231\347\202\271\346\226\207\344\273\266", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButtonLine->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonLine->setText(QApplication::translate("QtWidgetsFL", "\346\265\217\350\247\210...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButtonStop->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonStop->setText(QApplication::translate("QtWidgetsFL", "\346\265\217\350\247\210...", Q_NULLPTR));
        labelWind->setText(QApplication::translate("QtWidgetsFL", "\347\253\231\347\202\271\345\217\212\347\272\277\350\267\257\346\226\207\344\273\266\345\212\240\350\275\275", Q_NULLPTR));
        labelHits->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsFL: public Ui_QtWidgetsFL {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSFL_H
