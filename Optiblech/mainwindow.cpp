#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDir>
#include <QtWidgets>
#include <QTextStream>
#include <QtConcurrent/QtConcurrentRun>
#include <QTimer>

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
#include "globalParams.hpp"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_view(new SvgView),
    m_formview(new FormView),
    m_resultview(new FormView),
    pm(new ProblemManager()),
    bin_packing(0)
{
    ui->setupUi(this);

    pm->setLists(ui->absFormList,ui->pointList);

    ui->svgContainer->addWidget(m_resultview);
    m_resultview->setContainer(ui->svgContainer_2);

    ui->formViewer->addWidget(m_formview);
    m_formview->setContainer(ui->formViewerWidget);




    ui->toleranceSpinBox->setValue(GlobalParams::get_tolerance_digits());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateResultView(){
    if(bin_packing.next_step_of_algorithm()){
        setting = bin_packing.get_current_setting();
        m_resultview->showSetting(&setting);
        QTimer::singleShot(ceil(ui->delaySpinBox->value()*1000), this, SLOT(updateResultView()));
    }
}


void MainWindow::on_solveButton_clicked()
{


    if(!QDir("tmp").exists()){
        QDir().mkdir("tmp");
    }

    QString tmp = QString("tmp") + QDir::separator() + "out.svg";

    string output_filename_svg = tmp.toUtf8().data();



    Problem problem = *pm->getProblem();

    if (!problem.is_solveable())
        QMessageBox::warning(this, tr("Warning"), tr("Error! At least one form is too big to be placed on a form.\nPROBLEM NOT SOLVEABLE!"));
    else
    {
        ui->tabWidget->setCurrentIndex(2);
        bin_packing = BinPacking(&problem);

        if(ui->showCaseCheckBox->isChecked()){
             QTimer::singleShot(0, this, SLOT(updateResultView()));
        }else{
            setting = bin_packing.get_packed_setting();
            m_resultview->showSetting(&setting);
        }        
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
        qDebug("show Form");
        m_formview->showForm(pm->getForm(currentRow));
        if(ui->pointList->count() < 3){
            invalidForm(true);
        }else{
            invalidForm(false);
        }
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


void MainWindow::on_toleranceSpinBox_valueChanged(int arg1)
{
    GlobalParams::set_significant_digits(arg1);
}

void MainWindow::on_showCaseCheckBox_clicked(bool checked)
{
    if(checked){
        ui->showCaseGroup->setEnabled(true);
    }else{
        ui->showCaseGroup->setEnabled(false);
    }
}

void MainWindow::invalidForm(bool invalid)
{


    if(invalid){
        ui->currentFormBox->setStyleSheet("QListWidget {background-color:red;}");
    }else{
        ui->currentFormBox->setStyleSheet("QListWidget {background-color:green;}");
    }    
}
