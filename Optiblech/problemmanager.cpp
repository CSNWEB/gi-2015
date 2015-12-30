#include "problemmanager.h"

ProblemManager::ProblemManager() : problem(0, 0, vector<AbstractForm>(), vector<int>(), vector<string>())
{

}

ProblemManager::~ProblemManager()
{

}

void ProblemManager::setLists(QListWidget* absFormList, QListWidget* pointList){
    this->absFormList = absFormList;
    this->pointList = pointList;
}

QSizeF ProblemManager::loadFromFile(QString fileName){
    InputHandler ih;
    ih.get_input(fileName.toLatin1().data());

    problem = ih.create_problem();

    initAbsFormList();
    return QSizeF(problem.get_plane_width(), problem.get_plane_height());
}


void ProblemManager::initAbsFormList()
{
    absFormList->clear();

    for(int i = 0; i < problem.get_number_of_different_forms(); ++i){
        //Add name
        QString item = QString::fromStdString(problem.get_name_of_form(i));

        //Add points
        AbstractForm * form = problem.get_abstract_form_at_position(i);
        item += " (" + QString::number(form->get_number_of_points()) + " Points)";

        //Add number of Forms
        item += " (" + QString::number(problem.get_number_of_form_needed(i)) + " times)";

        absFormList->addItem(item);
    }
}

int ProblemManager::initPoints(int selectedForm)
{
    pointList->clear();
    AbstractForm * form = problem.get_abstract_form_at_position(selectedForm);

    for(int i=0; i< form->get_number_of_points(); ++i){
        Point point = form->get_point_at_index(i);
        QString item = QString::number(point.get_x()) + ", " + QString::number(point.get_y());

        pointList->addItem(item);
    }

   return problem.get_number_of_form_needed(selectedForm);
}

Problem ProblemManager::getProblem(){
    return problem;
}
