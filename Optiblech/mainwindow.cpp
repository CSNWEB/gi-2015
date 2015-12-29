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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_view(new SvgView),
    pm(new ProblemManager(ui))
{
    ui->setupUi(this);

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



    Problem problem = pm->getProblem();

    if (!problem.is_solveable())
        QMessageBox::warning(this, tr("Warning"), tr("Error! At least one form is too big to be placed on a form.\nPROBLEM NOT SOLVEABLE!"));
    else
    {
        BinPacking bin_packing(&problem);

        Setting bin_packed = bin_packing.get_packed_setting();
        OutputHandler oh(&problem, &bin_packed, output_filename_txt, output_filename_svg);
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
        pm->loadFromFile(fileName);
    }
}

void MainWindow::on_selectOutputButton_clicked()
{
   // QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
     //                                               tr("Filename (*)"));

    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);

    QString path = dialog.getExistingDirectory(this, tr("Choose Directory"));

    if (!path.isEmpty()) {
        //ui->outputFile->setText(path);
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}



void MainWindow::on_absFormList_currentRowChanged(int currentRow)
{
    QMessageBox::information(this, tr("Info"), QString::number(currentRow));
}
