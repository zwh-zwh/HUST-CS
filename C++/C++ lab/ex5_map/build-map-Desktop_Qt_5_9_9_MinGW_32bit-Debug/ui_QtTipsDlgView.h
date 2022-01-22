/********************************************************************************
** Form generated from reading UI file 'QtTipsDlgView.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTTIPSDLGVIEW_H
#define UI_QTTIPSDLGVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_QtTipsDlgView
{
public:
    QLabel *labelMsg;

    void setupUi(QDialog *QtTipsDlgView)
    {
        if (QtTipsDlgView->objectName().isEmpty())
            QtTipsDlgView->setObjectName(QStringLiteral("QtTipsDlgView"));
        QtTipsDlgView->resize(332, 38);
        labelMsg = new QLabel(QtTipsDlgView);
        labelMsg->setObjectName(QStringLiteral("labelMsg"));
        labelMsg->setGeometry(QRect(10, 10, 311, 21));

        retranslateUi(QtTipsDlgView);

        QMetaObject::connectSlotsByName(QtTipsDlgView);
    } // setupUi

    void retranslateUi(QDialog *QtTipsDlgView)
    {
        QtTipsDlgView->setWindowTitle(QApplication::translate("QtTipsDlgView", "Dialog", Q_NULLPTR));
        labelMsg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QtTipsDlgView: public Ui_QtTipsDlgView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTTIPSDLGVIEW_H
