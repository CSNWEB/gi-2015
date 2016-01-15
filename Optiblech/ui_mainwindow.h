/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_3;
    QDoubleSpinBox *planeWidth;
    QLabel *label_5;
    QDoubleSpinBox *planeHeight;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *currentFormBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *pointList;
    QWidget *formViewerWidget;
    QHBoxLayout *formViewer;
    QWidget *pointManageContainer;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *addPointButton;
    QPushButton *editPointButton;
    QToolButton *pointUpButton;
    QToolButton *pointDownButton;
    QPushButton *delPointButton;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QSpinBox *pointAmount;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_7;
    QListWidget *absFormList;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *addFormButton;
    QPushButton *editFormButton;
    QPushButton *delFormButton;
    QPushButton *selectInputButton;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QDoubleSpinBox *toleranceSpinBox;
    QCheckBox *showCaseCheckBox;
    QGroupBox *showCaseGroup;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpinBox *stepsSpinBox;
    QLabel *label_2;
    QDoubleSpinBox *delaySpinBox;
    QPushButton *solveButton;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout;
    QWidget *svgContainer_2;
    QVBoxLayout *svgContainer;
    QWidget *saveContainer;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *saveSVG;
    QPushButton *saveTXT;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(780, 495);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QLatin1String("#centralWidget{\n"
"	background:white;\n"
"}\n"
"\n"
"QTabBar::tab{\n"
"	background:white;\n"
"	padding:10px;\n"
"	margin-bottom: -2px;\n"
"}\n"
"\n"
"\n"
"QTabBar::tab:selected{\n"
"	border-top:1px solid black;\n"
"	border-left:1px solid black;\n"
"	border-right:1px solid black;\n"
"\n"
"}\n"
"\n"
"QWidget{\n"
"	font-family: Roboto;\n"
"	background-color: white;\n"
"}\n"
"\n"
"QTabWidget{\n"
"	border-top: 0px solid black;\n"
"}\n"
"\n"
"QGroupBox{\n"
"	border:2px solid black;\n"
"	padding-top:5px;\n"
"}\n"
"\n"
"QPushButton{\n"
"	padding:7px;\n"
"	background-color:#222222;\n"
"	border:none;\n"
"	color:white;\n"
"}"));
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setStyleSheet(QStringLiteral(""));
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tab->setEnabled(true);
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(-1, 10, 0, -1);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_9->addWidget(label_3);

        planeWidth = new QDoubleSpinBox(tab);
        planeWidth->setObjectName(QStringLiteral("planeWidth"));

        horizontalLayout_9->addWidget(planeWidth);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_9->addWidget(label_5);

        planeHeight = new QDoubleSpinBox(tab);
        planeHeight->setObjectName(QStringLiteral("planeHeight"));
        planeHeight->setMaximum(98.99);

        horizontalLayout_9->addWidget(planeHeight);


        gridLayout->addLayout(horizontalLayout_9, 1, 1, 1, 2);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(5000, 16777215));

        gridLayout->addWidget(pushButton, 6, 2, 1, 1);

        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 6, 1, 1, 1);

        currentFormBox = new QGroupBox(tab);
        currentFormBox->setObjectName(QStringLiteral("currentFormBox"));
        currentFormBox->setEnabled(false);
        verticalLayout_6 = new QVBoxLayout(currentFormBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pointList = new QListWidget(currentFormBox);
        pointList->setObjectName(QStringLiteral("pointList"));

        horizontalLayout_4->addWidget(pointList);

        formViewerWidget = new QWidget(currentFormBox);
        formViewerWidget->setObjectName(QStringLiteral("formViewerWidget"));
        formViewerWidget->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(formViewerWidget->sizePolicy().hasHeightForWidth());
        formViewerWidget->setSizePolicy(sizePolicy);
        formViewerWidget->setMinimumSize(QSize(100, 0));
        formViewer = new QHBoxLayout(formViewerWidget);
        formViewer->setSpacing(6);
        formViewer->setContentsMargins(11, 11, 11, 11);
        formViewer->setObjectName(QStringLiteral("formViewer"));
        formViewer->setSizeConstraint(QLayout::SetDefaultConstraint);
        formViewer->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_4->addWidget(formViewerWidget);


        verticalLayout_6->addLayout(horizontalLayout_4);

        pointManageContainer = new QWidget(currentFormBox);
        pointManageContainer->setObjectName(QStringLiteral("pointManageContainer"));
        horizontalLayout_5 = new QHBoxLayout(pointManageContainer);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 1, -1, -1);
        addPointButton = new QPushButton(pointManageContainer);
        addPointButton->setObjectName(QStringLiteral("addPointButton"));

        horizontalLayout_5->addWidget(addPointButton);

        editPointButton = new QPushButton(pointManageContainer);
        editPointButton->setObjectName(QStringLiteral("editPointButton"));

        horizontalLayout_5->addWidget(editPointButton);

        pointUpButton = new QToolButton(pointManageContainer);
        pointUpButton->setObjectName(QStringLiteral("pointUpButton"));
        pointUpButton->setArrowType(Qt::UpArrow);

        horizontalLayout_5->addWidget(pointUpButton);

        pointDownButton = new QToolButton(pointManageContainer);
        pointDownButton->setObjectName(QStringLiteral("pointDownButton"));
        pointDownButton->setArrowType(Qt::DownArrow);

        horizontalLayout_5->addWidget(pointDownButton);

        delPointButton = new QPushButton(pointManageContainer);
        delPointButton->setObjectName(QStringLiteral("delPointButton"));

        horizontalLayout_5->addWidget(delPointButton);


        verticalLayout_6->addWidget(pointManageContainer);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(-1, 0, -1, -1);
        label_4 = new QLabel(currentFormBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_7->addWidget(label_4);

        pointAmount = new QSpinBox(currentFormBox);
        pointAmount->setObjectName(QStringLiteral("pointAmount"));

        horizontalLayout_7->addWidget(pointAmount);


        verticalLayout_6->addLayout(horizontalLayout_7);

        pointManageContainer->raise();

        gridLayout->addWidget(currentFormBox, 2, 2, 4, 1);

        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_7 = new QVBoxLayout(groupBox);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        absFormList = new QListWidget(groupBox);
        absFormList->setObjectName(QStringLiteral("absFormList"));

        verticalLayout_7->addWidget(absFormList);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        addFormButton = new QPushButton(groupBox);
        addFormButton->setObjectName(QStringLiteral("addFormButton"));

        horizontalLayout_6->addWidget(addFormButton);

        editFormButton = new QPushButton(groupBox);
        editFormButton->setObjectName(QStringLiteral("editFormButton"));

        horizontalLayout_6->addWidget(editFormButton);

        delFormButton = new QPushButton(groupBox);
        delFormButton->setObjectName(QStringLiteral("delFormButton"));

        horizontalLayout_6->addWidget(delFormButton);


        verticalLayout_7->addLayout(horizontalLayout_6);


        gridLayout->addWidget(groupBox, 2, 1, 1, 1);

        selectInputButton = new QPushButton(tab);
        selectInputButton->setObjectName(QStringLiteral("selectInputButton"));
        selectInputButton->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(selectInputButton, 0, 1, 1, 2);


        horizontalLayout_2->addLayout(gridLayout);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_2->setEnabled(true);
        verticalLayout_2 = new QVBoxLayout(tab_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);

        horizontalLayout_10->addWidget(label_6);

        toleranceSpinBox = new QDoubleSpinBox(tab_2);
        toleranceSpinBox->setObjectName(QStringLiteral("toleranceSpinBox"));
        toleranceSpinBox->setDecimals(4);
        toleranceSpinBox->setMinimum(0.0001);
        toleranceSpinBox->setMaximum(1);
        toleranceSpinBox->setSingleStep(0.001);
        toleranceSpinBox->setValue(0.0001);

        horizontalLayout_10->addWidget(toleranceSpinBox);


        verticalLayout_2->addLayout(horizontalLayout_10);

        showCaseCheckBox = new QCheckBox(tab_2);
        showCaseCheckBox->setObjectName(QStringLiteral("showCaseCheckBox"));
        showCaseCheckBox->setChecked(false);

        verticalLayout_2->addWidget(showCaseCheckBox);

        showCaseGroup = new QGroupBox(tab_2);
        showCaseGroup->setObjectName(QStringLiteral("showCaseGroup"));
        showCaseGroup->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(showCaseGroup->sizePolicy().hasHeightForWidth());
        showCaseGroup->setSizePolicy(sizePolicy2);
        horizontalLayout_3 = new QHBoxLayout(showCaseGroup);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label = new QLabel(showCaseGroup);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_3->addWidget(label);

        stepsSpinBox = new QSpinBox(showCaseGroup);
        stepsSpinBox->setObjectName(QStringLiteral("stepsSpinBox"));
        stepsSpinBox->setMinimum(1);

        horizontalLayout_3->addWidget(stepsSpinBox);

        label_2 = new QLabel(showCaseGroup);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        delaySpinBox = new QDoubleSpinBox(showCaseGroup);
        delaySpinBox->setObjectName(QStringLiteral("delaySpinBox"));
        delaySpinBox->setMinimum(0.01);
        delaySpinBox->setValue(0.5);

        horizontalLayout_3->addWidget(delaySpinBox);


        verticalLayout_2->addWidget(showCaseGroup);

        solveButton = new QPushButton(tab_2);
        solveButton->setObjectName(QStringLiteral("solveButton"));
        solveButton->setMaximumSize(QSize(300, 16777215));

        verticalLayout_2->addWidget(solveButton, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tab_3->setEnabled(true);
        verticalLayout = new QVBoxLayout(tab_3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        svgContainer_2 = new QWidget(tab_3);
        svgContainer_2->setObjectName(QStringLiteral("svgContainer_2"));
        svgContainer_2->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(svgContainer_2->sizePolicy().hasHeightForWidth());
        svgContainer_2->setSizePolicy(sizePolicy3);
        svgContainer_2->setMinimumSize(QSize(50, 50));
        svgContainer = new QVBoxLayout(svgContainer_2);
        svgContainer->setSpacing(6);
        svgContainer->setContentsMargins(11, 11, 11, 11);
        svgContainer->setObjectName(QStringLiteral("svgContainer"));

        verticalLayout->addWidget(svgContainer_2);

        saveContainer = new QWidget(tab_3);
        saveContainer->setObjectName(QStringLiteral("saveContainer"));
        saveContainer->setEnabled(false);
        horizontalLayout_8 = new QHBoxLayout(saveContainer);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, 10, -1, -1);
        saveSVG = new QPushButton(saveContainer);
        saveSVG->setObjectName(QStringLiteral("saveSVG"));

        horizontalLayout_8->addWidget(saveSVG);

        saveTXT = new QPushButton(saveContainer);
        saveTXT->setObjectName(QStringLiteral("saveTXT"));

        horizontalLayout_8->addWidget(saveTXT);


        verticalLayout->addWidget(saveContainer);

        tabWidget->addTab(tab_3, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Optiblech Solver", 0));
        label_3->setText(QApplication::translate("MainWindow", "Pane width: ", 0));
        label_5->setText(QApplication::translate("MainWindow", "Plane height", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Next", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Save Problem", 0));
        currentFormBox->setTitle(QApplication::translate("MainWindow", "Current Form", 0));
        addPointButton->setText(QApplication::translate("MainWindow", "+", 0));
        editPointButton->setText(QApplication::translate("MainWindow", "Edit Point", 0));
        pointUpButton->setText(QApplication::translate("MainWindow", "...", 0));
        pointDownButton->setText(QApplication::translate("MainWindow", "...", 0));
        delPointButton->setText(QApplication::translate("MainWindow", "-", 0));
        label_4->setText(QApplication::translate("MainWindow", "Amount:", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Forms", 0));
        addFormButton->setText(QApplication::translate("MainWindow", "+", 0));
        editFormButton->setText(QApplication::translate("MainWindow", "Rename Form", 0));
        delFormButton->setText(QApplication::translate("MainWindow", "-", 0));
        selectInputButton->setText(QApplication::translate("MainWindow", "Open Problem", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Enter Problem", 0));
        label_6->setText(QApplication::translate("MainWindow", "Tolerance", 0));
        showCaseCheckBox->setText(QApplication::translate("MainWindow", "Activate Step-by-Step Showcase mode", 0));
        showCaseGroup->setTitle(QApplication::translate("MainWindow", "Showcase params", 0));
        label->setText(QApplication::translate("MainWindow", "Steps", 0));
        label_2->setText(QApplication::translate("MainWindow", "Delay (seconds)", 0));
        solveButton->setText(QApplication::translate("MainWindow", "Solve", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Run Solver", 0));
        saveSVG->setText(QApplication::translate("MainWindow", "Save as SVG", 0));
        saveTXT->setText(QApplication::translate("MainWindow", "Save as TXT", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "View Result", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
