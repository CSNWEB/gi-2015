#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

#include "abstractForm.hpp"
#include "form.hpp"
#include "outputHandler.hpp"
#include "inputHandler.hpp"
#include "binPacking.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_solveButton_clicked()
{
    std::string output_filename = ui->outputFile->text().toUtf8().constData();
    std::string output_filename_txt;
    std::string output_filename_svg;

    output_filename_txt = output_filename + ".txt";
    output_filename_svg = output_filename + ".svg";

    InputHandler ih;

    ih.get_input(ui->inputFile->text().toLatin1().data());
    //ih._d_print_input();

    Problem problem = ih.create_problem();

    if (!problem.is_solveable())
        printf("Error! At least one form is too big to be placed on a form.\nPROBLEM NOT SOLVEABLE!\n");
    else
    {
        BinPacking bin_packing(&problem);

        Setting bin_packed = bin_packing.get_packed_setting();
        OutputHandler oh(&problem, &bin_packed, output_filename_txt, output_filename_svg);
        QMessageBox::information(this, tr("Info"), tr("Writing text output"));
        oh.write_setting_to_txt();
        QMessageBox::information(this, tr("Info"), tr("Writing svg Output"));
        oh.write_setting_to_svg(true);
    }
}



void MainWindow::on_selectInputButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        ui->inputFile->setText(fileName);
        /*QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();*/

    }
}

void MainWindow::on_selectOutputButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if (!fileName.isEmpty()) {
        ui->outputFile->setText(fileName);
    }
}
