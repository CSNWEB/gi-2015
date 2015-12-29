#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QtWidgets>

#include <svgview.h>

#include "abstractForm.hpp"
#include "form.hpp"
#include "outputHandler.hpp"
#include "inputHandler.hpp"
#include "binPacking.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_view(new SvgView)
{
    ui->setupUi(this);

   ui->svgContainer->addWidget(m_view);

   QFile file("/Users/Christoph/Code/gi-2015/out.svg");

   m_view->openFile(file);
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


    output_filename_txt = output_filename + QDir::separator().toLatin1() + "out.txt";
    output_filename_svg = output_filename + QDir::separator().toLatin1() + "out.svg";

    InputHandler ih;

    /*ih.get_input(ui->inputFile->text().toLatin1().data());

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
    }*/
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

        InputHandler ih;
        ih.get_input(fileName.toLatin1().data());

        Problem problem = ih.create_problem();

        ui->absFormList->clear();
        for(int i = 0; i < problem.get_number_of_different_forms(); ++i){
            //Add name
            QString item = QString::fromStdString(problem.get_name_of_form(i));

            //Add points
            AbstractForm * form = problem.get_abstract_form_at_position(i);
            item += " (" + QString::number(form->get_number_of_points()) + " Points)";

            //Add number of Forms
            item += " (" + QString::number(problem.get_number_of_form_needed(i)) + " times)";

            ui->absFormList->addItem(item);
        }

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
        ui->outputFile->setText(path);
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}
