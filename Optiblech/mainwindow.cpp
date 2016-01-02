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
#include "manageformdialog.h"
#include "managepointsdialog.h"

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

    output_filename_svg = 'tmp' + QDir::separator().toLatin1() + "out.svg";



    Problem* problem = pm->getProblem();

    if (!problem->is_solveable())
        QMessageBox::warning(this, tr("Warning"), tr("Error! At least one form is too big to be placed on a form.\nPROBLEM NOT SOLVEABLE!"));
    else
    {
        BinPacking bin_packing(problem);

        setting = bin_packing.get_packed_setting();
        OutputHandler oh(problem, &setting);
        oh.write_setting_to_svg(output_filename_svg, true);

        //Open file and show result
        QFile file(QString::fromStdString(output_filename_svg));
        m_view->openFile(file);
        ui->tabWidget->setCurrentIndex(2);
        ui->saveContainer->setEnabled(true);
    }
}



void MainWindow::on_selectInputButton_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
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
        ui->currentFormBox->setEnabled(true);
    }else{
        ui->currentFormBox->setEnabled(false);
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
             if(!file.endsWith(".svg")){
                 file += ".svg";
             }
             OutputHandler oh(pm->getProblem(), &setting);
             oh.write_setting_to_svg(file.toUtf8().data(), false);
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
    AddFormDialog dialog(this, pm, -1);
    dialog.exec();
}

void MainWindow::on_delFormButton_clicked()
{
    if(ui->absFormList->currentRow() >= 0){
        pm->delForm(ui->absFormList->currentRow());
    }
    /*for(int i = 0; i < editFormDialogs.size(); ++i){
        editFormDialogs[i].close();
    }
    editFormDialogs.clear();*/
}

void MainWindow::on_editFormButton_clicked()
{
    int row = ui->absFormList->currentRow();
    AddFormDialog dialog(this, pm, row);
    dialog.setName(QString::fromStdString(pm->getProblem()->get_name_of_form(row)));
    dialog.exec();
    //editFormDialogs.push_back(dialog);
}

void MainWindow::on_pointUpButton_clicked()
{
    if(ui->absFormList->currentRow() >= 0 && ui->pointList->currentRow() >= 0){
        pm->movePointUp(ui->absFormList->currentRow(), ui->pointList->currentRow());
    }
}

void MainWindow::on_pointDownButton_clicked()
{
    if(ui->absFormList->currentRow() >= 0 && ui->pointList->currentRow() >= 0){
        pm->movePointDown(ui->absFormList->currentRow(), ui->pointList->currentRow());
    }
}

void MainWindow::on_delPointButton_clicked()
{
    if(ui->absFormList->currentRow() >= 0 && ui->pointList->currentRow() >= 0){
        pm->delPointOfForm(ui->absFormList->currentRow(), ui->pointList->currentRow());
    }
}


void MainWindow::on_addPointButton_clicked()
{
    if(ui->absFormList->currentRow() >= 0){
        ManagePointsDialog dialog(this, pm, ui->absFormList->currentRow(), -1);
        dialog.exec();
    }
}

void MainWindow::on_editPointButton_clicked()
{
    int selectedForm = ui->absFormList->currentRow();
    int selectedPoint = ui->pointList->currentRow();
    if(selectedForm >= 0 && selectedPoint >= 0){
        ManagePointsDialog dialog(this, pm, selectedForm, selectedPoint);
        AbstractForm * form = pm->getProblem()->get_abstract_form_at_position(selectedForm);
        dialog.setPoint(form->get_point_at_index(selectedPoint).get_x(), form->get_point_at_index(selectedPoint).get_y());
        dialog.exec();
    }
}

void MainWindow::on_saveTXT_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setDirectory(QDir::homePath());

    QString file = dialog.getSaveFileName(this, tr("Save file"));

    if (!file.isEmpty()) {
        if(!file.endsWith(".txt")){
            file += ".txt";
        }
        OutputHandler oh(pm->getProblem(), &setting);
        oh.write_setting_to_txt(file.toUtf8().data());
    }
}
