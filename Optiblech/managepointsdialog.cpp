#include "managepointsdialog.h"
#include "ui_managepointsdialog.h"
#include "problemmanager.h"

ManagePointsDialog::ManagePointsDialog(QWidget *parent, ProblemManager * pm, int selectedForm, int toedit ) :
    QDialog(parent),
    ui(new Ui::ManagePointsDialog)
{
    ui->setupUi(this);
    this->pm = pm;
    this->toedit = toedit;
    this->selectedForm = selectedForm;
}

ManagePointsDialog::~ManagePointsDialog()
{
    delete ui;
}

void ManagePointsDialog::on_buttonBox_accepted()
{
    if(toedit >= 0){
        pm->editPointOfForm(selectedForm, toedit, ui->xSpinBox->value(), ui->ySpinBox->value());
    }else{
        pm->addPointToForm(selectedForm, ui->xSpinBox->value(), ui->ySpinBox->value());
    }
}

void ManagePointsDialog::setPoint(float x, float y)
{
    ui->xSpinBox->setValue(x);
    ui->ySpinBox->setValue(y);
    setWindowTitle("Edit point (" + QString::number(x) + ", " + QString::number(y) +")");
}
