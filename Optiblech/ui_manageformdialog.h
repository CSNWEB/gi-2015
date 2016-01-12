/********************************************************************************
** Form generated from reading UI file 'manageformdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEFORMDIALOG_H
#define UI_MANAGEFORMDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddFormDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *formName;
    QDialogButtonBox *Controls;

    void setupUi(QDialog *AddFormDialog)
    {
        if (AddFormDialog->objectName().isEmpty())
            AddFormDialog->setObjectName(QStringLiteral("AddFormDialog"));
        AddFormDialog->resize(400, 131);
        verticalLayout = new QVBoxLayout(AddFormDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(AddFormDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        formName = new QLineEdit(AddFormDialog);
        formName->setObjectName(QStringLiteral("formName"));

        horizontalLayout->addWidget(formName);


        verticalLayout->addLayout(horizontalLayout);

        Controls = new QDialogButtonBox(AddFormDialog);
        Controls->setObjectName(QStringLiteral("Controls"));
        Controls->setOrientation(Qt::Horizontal);
        Controls->setStandardButtons(QDialogButtonBox::Abort|QDialogButtonBox::Ok);

        verticalLayout->addWidget(Controls);


        retranslateUi(AddFormDialog);
        QObject::connect(Controls, SIGNAL(accepted()), AddFormDialog, SLOT(accept()));
        QObject::connect(Controls, SIGNAL(rejected()), AddFormDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddFormDialog);
    } // setupUi

    void retranslateUi(QDialog *AddFormDialog)
    {
        AddFormDialog->setWindowTitle(QApplication::translate("AddFormDialog", "Add Form", 0));
        label->setText(QApplication::translate("AddFormDialog", "Name:", 0));
    } // retranslateUi

};

namespace Ui {
    class AddFormDialog: public Ui_AddFormDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEFORMDIALOG_H
