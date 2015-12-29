#ifndef PROBLEMMANAGER_H
#define PROBLEMMANAGER_H

#include <mainwindow.h>
#include <problem.hpp>
#include <abstractForm.hpp>
#include <ui_mainwindow.h>
#include <inputHandler.hpp>

class ProblemManager
{
public:
    ProblemManager(Ui::MainWindow *ui);
    ~ProblemManager();

    void initAbsFormList();
    void loadFromFile(QString fileName);

private:
    Problem problem;
    Ui::MainWindow *ui;
};

#endif // PROBLEMMANAGER_H
