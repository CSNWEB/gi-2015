#ifndef MANAGEPOINTSDIALOG_H
#define MANAGEPOINTSDIALOG_H

#include <QDialog>
#include "problemmanager.h"

namespace Ui {
class ManagePointsDialog;
}

class ManagePointsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManagePointsDialog(QWidget *parent = 0, ProblemManager * pm = 0, int toedit = -1);
    ~ManagePointsDialog();

    void setPoint(float x, float y);
private slots:
    void on_buttonBox_accepted();

private:
    Ui::ManagePointsDialog *ui;
    ProblemManager * pm;
    int toedit;
};

#endif // MANAGEPOINTSDIALOG_H
