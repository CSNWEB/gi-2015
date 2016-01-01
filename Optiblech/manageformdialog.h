#ifndef ADDFORMDIALOG_H
#define ADDFORMDIALOG_H

#include <QDialog>
#include "problemmanager.h"

namespace Ui {
class AddFormDialog;
}

class AddFormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFormDialog(QWidget *parent = 0, ProblemManager * pm = 0, int toedit = -1);
    ~AddFormDialog();

    void setName(QString name);

private slots:
    void on_Controls_accepted();

private:
    Ui::AddFormDialog *ui;
    ProblemManager * pm;
    int toedit;
};

#endif // ADDFORMDIALOG_H
