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
    explicit AddFormDialog(QWidget *parent = 0, ProblemManager * pm = 0, bool edit = false);
    ~AddFormDialog();

private slots:
    void on_Controls_accepted();

private:
    Ui::AddFormDialog *ui;
    ProblemManager * pm;
    bool edit;
};

#endif // ADDFORMDIALOG_H
