#include "managepointsdialog.h"
#include "ui_managepointsdialog.h"
#include "problemmanager.h"

ManagePointsDialog::ManagePointsDialog(QWidget *parent, ProblemManager * pm, int toedit ) :
    QDialog(parent),
    ui(new Ui::ManagePointsDialog)
{
    ui->setupUi(this);
    this->pm = pm;
    this->toedit = toedit;
}

ManagePointsDialog::~ManagePointsDialog()
{
    delete ui;
}

void ManagePointsDialog::on_buttonBox_accepted()
{
    if(toedit >= 0){

    }else{

    }
}

void ManagePointsDialog::setPoint(float x, float y)
{
    ui->xSpinBox->setValue(x);
    ui->ySpinBox->setValue(y);
    setWindowTitle("Edit point (" + QString::number(x) + ", " + QString::number(y) +")");
}
