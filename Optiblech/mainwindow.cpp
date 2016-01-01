#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QtWidgets>

#include <svgview.h>
#include <problemmanager.h>

#include "abstractForm.hpp"
#include "form.hpp"
#include "outputHandler.hpp"
#include "inputHandler.hpp"
#include "binPacking.hpp"
#include "addformdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_view(new SvgView),
    pm(new ProblemManager())
{
    ui->setupUi(this);

    pm->setLists(ui->absFormList,ui->pointList);
    ui->svgContainer->addWidget(m_view);

   //QFile file("/Users/Christoph/Code/gi-2015/out.svg");
   //m_view->openFile(file);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_solveButton_clicked()
{
    std::string output_filename_txt;
    std::string output_filename_svg;

    if(!QDir("tmp").exists()){
        QDir().mkdir("tmp");
    }

    //output_filename_txt = 'tmp' + QDir::separator().toLatin1() + "out.txt";
    output_filename_svg = 'tmp' + QDir::separator().toLatin1() + "out.svg";



    Problem* problem = pm->getProblem();

    if (!problem->is_solveable())
        QMessageBox::warning(this, tr("Warning"), tr("Error! At least one form is too big to be placed on a form.\nPROBLEM NOT SOLVEABLE!"));
    else
    {
        BinPacking bin_packing(problem);

        Setting bin_packed = bin_packing.get_packed_setting();
        OutputHandler oh(problem, &bin_packed, output_filename_txt, output_filename_svg);
        //oh.write_setting_to_txt();
        oh.write_setting_to_svg(true);
        QFile file(QString::fromStdString(output_filename_svg));
        m_view->openFile(file);
        ui->tabWidget->setCurrentIndex(2);
    }
}



void MainWindow::on_selectInputButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.txt)"));


    if (!fileName.isEmpty()) {

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        file.close();
        QSizeF size = pm->loadFromFile(fileName);
        ui->planeWidth->setValue(size.width());
        ui->planeHeight->setValue(size.height());
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}



void MainWindow::on_absFormList_currentRowChanged(int currentRow)
{
    if(currentRow > -1){
        int amount = pm->initPoints(currentRow);
        ui->pointAmount->setValue(amount);
    }else{
        ui->pointList->clear();
    }
}

void MainWindow::on_saveSVG_clicked()
{
         QFileDialog dialog;
         dialog.setFileMode(QFileDialog::AnyFile);
         dialog.setDirectory(QDir::homePath());

         QString file = dialog.getSaveFileName(this, tr("Save file"));

         if (!file.isEmpty()) {
             if(!file.endsWith('.svg')){
                 file += ".svg";
             }
             //ui->outputFile->setText(path);
         }
}

void MainWindow::on_planeWidth_valueChanged(double arg1)
{
    pm->setPlaneWidth(arg1);
}

void MainWindow::on_planeHeight_valueChanged(double arg1)
{
    pm->setPlaneHeight(arg1);
}



void MainWindow::on_addFormButton_clicked()
{
    AddFormDialog dialog(this, pm, false);
    dialog.exec();
}

void MainWindow::on_delFormButton_clicked()
{
    if(ui->absFormList->currentRow() >= 0){
        pm->delForm(ui->absFormList->currentRow());
    }
}