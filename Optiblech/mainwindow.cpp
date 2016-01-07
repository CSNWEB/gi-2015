#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QtWidgets>
#include <QTextStream>

#include <svgview.h>
#include <formview.h>
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
    m_formview(new FormView),
    pm(new ProblemManager())
{
    ui->setupUi(this);

    pm->setLists(ui->absFormList,ui->pointList);
    ui->svgContainer->addWidget(m_view);
    m_view->setContainer(ui->svgContainer_2);

    ui->formViewer->addWidget(m_formview);
    m_formview->setContainer(ui->formViewerWidget);
    m_formview->showForm();
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

    QString tmp = QString("tmp") + QDir::separator() + "out.svg";

    output_filename_svg = tmp.toUtf8().data();



    Problem* problem = pm->getProblem();

    if (!problem->is_solveable())
        QMessageBox::warning(this, tr("Warning"), tr("Error! At least one form is too big to be placed on a form.\nPROBLEM NOT SOLVEABLE!"));
    else
    {
        BinPacking bin_packing(problem);

        setting = bin_packing.get_packed_setting();
        OutputHandler oh(problem, &setting);
        oh.write_setting_to_svg(output_filename_svg, true);

        ui->tabWidget->setCurrentIndex(2);

        //Open file and show result
        QFile file(QString::fromStdString(output_filename_svg));
        m_view->openFile(file);
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
        m_formview->showForm(pm->getForm(currentRow));
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

void MainWindow::on_pointAmount_valueChanged(int arg1)
{
    pm->setAmountOfForm(ui->absFormList->currentRow(), arg1);
}

void MainWindow::on_pushButton_2_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setDirectory(QDir::homePath());

    QString filename = dialog.getSaveFileName(this, tr("Save file"));
    if (!filename.isEmpty()) {
        if(!filename.endsWith(".txt")){
            filename += ".txt";
        }
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite)) {
                QTextStream stream(&file);
                stream << pm->getProblem()->get_plane_width() << endl
                        << pm->getProblem()->get_plane_height() << endl
                        << pm->getProblem()->get_number_of_different_forms() << endl;
                for(int i = 0; i<pm->getProblem()->get_number_of_different_forms(); ++i){
                    AbstractForm * form = pm->getProblem()->get_abstract_form_at_position(i);
                    stream << QString::fromStdString(pm->getProblem()->get_name_of_form(i)) << endl
                           << pm->getProblem()->get_number_of_form_needed(i) << endl
                           << form->get_number_of_points() << endl;
                    for(int j=0; j < form->get_number_of_points(); ++j){
                        stream << form->get_point_at_index(j).get_x() << " " << form->get_point_at_index(j).get_y() << endl;
                    }
                }
                file.close();
        }


    }
}
