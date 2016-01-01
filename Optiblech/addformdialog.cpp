#include "addformdialog.h"
#include "ui_addformdialog.h"
#include "problemmanager.h"

AddFormDialog::AddFormDialog(QWidget *parent, ProblemManager * pm, bool edit ) :
    QDialog(parent),
    ui(new Ui::AddFormDialog)
{
    ui->setupUi(this);
    this->pm = pm;
    this->edit = edit;
}

AddFormDialog::~AddFormDialog()
{
    delete ui;
}

void AddFormDialog::on_Controls_accepted()
{
    if(edit){

    }else{
     pm->addForm(ui->formName->text());
    }
}
