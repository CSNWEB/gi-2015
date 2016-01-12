/********************************************************************************
** Form generated from reading UI file 'managepointsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGEPOINTSDIALOG_H
#define UI_MANAGEPOINTSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ManagePointsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QDoubleSpinBox *xSpinBox;
    QLabel *label_2;
    QDoubleSpinBox *ySpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ManagePointsDialog)
    {
        if (ManagePointsDialog->objectName().isEmpty())
            ManagePointsDialog->setObjectName(QStringLiteral("ManagePointsDialog"));
        ManagePointsDialog->resize(332, 132);
        verticalLayout = new QVBoxLayout(ManagePointsDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label = new QLabel(ManagePointsDialog);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        xSpinBox = new QDoubleSpinBox(ManagePointsDialog);
        xSpinBox->setObjectName(QStringLiteral("xSpinBox"));

        formLayout->setWidget(0, QFormLayout::FieldRole, xSpinBox);

        label_2 = new QLabel(ManagePointsDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        ySpinBox = new QDoubleSpinBox(ManagePointsDialog);
        ySpinBox->setObjectName(QStringLiteral("ySpinBox"));
        ySpinBox->setDecimals(2);

        formLayout->setWidget(1, QFormLayout::FieldRole, ySpinBox);


        verticalLayout->addLayout(formLayout);

        buttonBox = new QDialogButtonBox(ManagePointsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(ManagePointsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ManagePointsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ManagePointsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ManagePointsDialog);
    } // setupUi

    void retranslateUi(QDialog *ManagePointsDialog)
    {
        ManagePointsDialog->setWindowTitle(QApplication::translate("ManagePointsDialog", "Add Point", 0));
        label->setText(QApplication::translate("ManagePointsDialog", "x:", 0));
        label_2->setText(QApplication::translate("ManagePointsDialog", "y:", 0));
    } // retranslateUi

};

namespace Ui {
    class ManagePointsDialog: public Ui_ManagePointsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGEPOINTSDIALOG_H
