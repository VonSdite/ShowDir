/********************************************************************************
** Form generated from reading UI file 'DirGui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIRGUI_H
#define UI_DIRGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DirGuiClass
{
public:

    void setupUi(QWidget *DirGuiClass)
    {
        if (DirGuiClass->objectName().isEmpty())
            DirGuiClass->setObjectName(QStringLiteral("DirGuiClass"));
        DirGuiClass->resize(600, 400);

        retranslateUi(DirGuiClass);

        QMetaObject::connectSlotsByName(DirGuiClass);
    } // setupUi

    void retranslateUi(QWidget *DirGuiClass)
    {
        DirGuiClass->setWindowTitle(QApplication::translate("DirGuiClass", "DirGui", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DirGuiClass: public Ui_DirGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIRGUI_H
