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
        absFormList->addItem(getAbsFormListItem(i));
    }
}

QString ProblemManager::getAbsFormListItem(int i){
    //Add name
    QString item = QString::fromStdString(problem.get_name_of_form(i));

    //Add points
    AbstractForm * form = problem.get_abstract_form_at_position(i);
    item += " (" + QString::number(form->get_number_of_points()) + " Points)";

    //Add number of Forms
    item += " (" + QString::number(problem.get_number_of_form_needed(i)) + " times)";
    return item;
}

QString ProblemManager::getPointListItem(int form, int i)
{
    Point point = problem.get_abstract_form_at_position(form)->get_point_at_index(i);
    QString item = QString::number(point.get_x()) + ", " + QString::number(point.get_y());
    return item;
}

int ProblemManager::initPoints(int selectedForm)
{
    pointList->clear();
    AbstractForm * form = problem.get_abstract_form_at_position(selectedForm);

    for(int i=0; i< form->get_number_of_points(); ++i){        
        QString item = getPointListItem(selectedForm, i);
        pointList->addItem(item);
    }

   return problem.get_number_of_form_needed(selectedForm);
}

Problem* ProblemManager::getProblem(){
    return &problem;
}

void ProblemManager::setPlaneWidth(float width){
    problem.set_plane_width(width);
}

void ProblemManager::setPlaneHeight(float height){
    problem.set_plane_height(height);
}

void ProblemManager::addForm(QString name){
    AbstractForm form;
    problem.add_abstract_form(name.toUtf8().constData(), form);
    int row = problem.get_number_of_different_forms()-1;
    absFormList->addItem(getAbsFormListItem(row));
    absFormList->setCurrentRow(row);
}

void ProblemManager::renameForm(int selectedForm, QString name){
    problem.rename_abstract_form(selectedForm,name.toUtf8().data());
    QString item = getAbsFormListItem(selectedForm);
    absFormList->item(selectedForm)->setText(item);
}

void ProblemManager::delForm(int selectedForm){
    problem.erase_abstract_form(selectedForm);
    initAbsFormList();
    if(selectedForm >= absFormList->count()){
        selectedForm = absFormList->count()-1;
    }
    absFormList->setCurrentRow(selectedForm);
}

void ProblemManager::addPointToForm(int selectedForm, float x, float y)
{
    problem.get_abstract_form_at_position(selectedForm)->add_point_to_form(x,y);
    int row = problem.get_abstract_form_at_position(selectedForm)->get_number_of_points()-1;
    pointList->addItem(getPointListItem(selectedForm,row));
    pointList->setCurrentRow(row);
    absFormList->item(selectedForm)->setText(getAbsFormListItem(selectedForm));
}

void ProblemManager::editPointOfForm(int selectedForm, int selectedPoint, float x, float y)
{
    problem.get_abstract_form_at_position(selectedForm)->set_xy_of_point(selectedPoint, x, y);
    pointList->item(selectedPoint)->setText(getPointListItem(selectedForm, selectedPoint));
}

void ProblemManager::delPointOfForm(int selectedForm, int selectedPoint)
{
    qDebug( "Start deleting");
    problem.get_abstract_form_at_position(selectedForm)->erase_point_at_index(selectedPoint);
    qDebug("Finished deleting");
    initPoints(selectedForm);
    if(selectedPoint >= pointList->count()){
        selectedPoint = pointList->count()-1;
    }
    pointList->setCurrentRow(selectedPoint);
    absFormList->item(selectedForm)->setText(getAbsFormListItem(selectedForm));
}

void ProblemManager::movePointUp(int selectedForm, int selectedPoint){
    problem.get_abstract_form_at_position(selectedForm)->move_up_point_at_index(selectedPoint);
    initPoints(selectedForm);
    if(selectedPoint > 0){
        pointList->setCurrentRow(selectedPoint-1);
    }else{
        pointList->setCurrentRow(0);
    }
}

void ProblemManager::movePointDown(int selectedForm, int selectedPoint){
    problem.get_abstract_form_at_position(selectedForm)->move_down_point_at_index(selectedPoint);
    initPoints(selectedForm);
    if(selectedPoint < pointList->count()-1){
        pointList->setCurrentRow(selectedPoint+1);
    }else{
        pointList->setCurrentRow(pointList->count()-1);
    }
}

void ProblemManager::setAmountOfForm(int selectedForm, int amount)
{
    problem.set_amount_of_form(selectedForm,amount);
    absFormList->item(selectedForm)->setText(getAbsFormListItem(selectedForm));
}

AbstractForm* ProblemManager::getForm(int selectedForm){
    return problem.get_abstract_form_at_position(selectedForm);
}
