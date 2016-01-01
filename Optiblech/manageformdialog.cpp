#include "manageformdialog.h"
#include "ui_manageformdialog.h"
#include "problemmanager.h"

AddFormDialog::AddFormDialog(QWidget *parent, ProblemManager * pm, int toedit ) :
    QDialog(parent),
    ui(new Ui::AddFormDialog)
{
    ui->setupUi(this);
    this->pm = pm;
    this->toedit = toedit;
}

AddFormDialog::~AddFormDialog()
{
    delete ui;
}

void AddFormDialog::on_Controls_accepted()
{
    if(toedit >= 0){
        pm->renameForm(toedit, ui->formName->text());
    }else{
     pm->addForm(ui->formName->text());
    }
}

void AddFormDialog::setName(QString name)
{
    ui->formName->setText(name);
    setWindowTitle("Edit form " + name);
}
