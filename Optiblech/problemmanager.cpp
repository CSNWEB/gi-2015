#include "problemmanager.h"

ProblemManager::ProblemManager(Ui::MainWindow *ui) : problem(0, 0, vector<AbstractForm>(), vector<int>(), vector<string>())
{
    this->ui = ui;
}

ProblemManager::~ProblemManager()
{

}

void ProblemManager::loadFromFile(QString fileName){
    InputHandler ih;
    ih.get_input(fileName.toLatin1().data());

    problem = ih.create_problem();

    initAbsFormList();
}


void ProblemManager::initAbsFormList()
{
    ui->absFormList->clear();

    for(int i = 0; i < problem.get_number_of_different_forms(); ++i){
        //Add name
        QString item = QString::fromStdString(problem.get_name_of_form(i));

        //Add points
        AbstractForm * form = problem.get_abstract_form_at_position(i);
        item += " (" + QString::number(form->get_number_of_points()) + " Points)";

        //Add number of Forms
        item += " (" + QString::number(problem.get_number_of_form_needed(i)) + " times)";

        ui->absFormList->addItem(item);
    }
}

Problem ProblemManager::getProblem(){
    return problem;
}
