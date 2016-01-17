#include "problemmanager.h"


ProblemManager::ProblemManager(FormView * formview) :
    problem(0, 0, vector<AbstractForm>(), vector<int>(), vector<string>()),
    m_showedProblem(0, 0, vector<AbstractForm>(), vector<int>(), vector<string>()),
    m_formview(formview)
{

}

ProblemManager::~ProblemManager()
{    
    delete m_absFormList;
    delete m_pointList;
}

void ProblemManager::setUiElements(QListWidget* absFormList, QListWidget* pointList, QPushButton * solveButton){
    this->m_absFormList = absFormList;
    this->m_pointList = pointList;
    this->m_solveButton = solveButton;
}


QSizeF ProblemManager::loadFromFile(QString fileName){
    InputHandler ih;
    ih.get_input(fileName.toLatin1().data());

    problem = ih.create_problem();
    m_showedProblem = ih.create_problem();

    initAbsFormList();
    return QSizeF(problem.get_plane_width(), problem.get_plane_height());
}


void ProblemManager::initAbsFormList()
{
    m_absFormList->clear();
    m_invalidForms.clear();
    for(int i = 0; i < problem.get_number_of_different_forms(); ++i){
        m_absFormList->addItem(getAbsFormListItem(i));
        updateForm(i, false);
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
    Point point = m_showedProblem.get_abstract_form_at_position(form)->get_point_at_index(i);
    QString item = QString::number(point.get_x()) + ", " + QString::number(point.get_y());
    return item;
}

int ProblemManager::initPoints(int selectedForm)
{
    m_pointList->clear();
    AbstractForm * form = m_showedProblem.get_abstract_form_at_position(selectedForm);

    for(int i=0; i< form->get_number_of_points(); ++i){        
        QString item = getPointListItem(selectedForm, i);
        m_pointList->addItem(item);
    }

   return problem.get_number_of_form_needed(selectedForm);
}

Problem* ProblemManager::getProblem(){
    return &problem;
}

void ProblemManager::setPlaneWidth(float width){
    problem.set_plane_width(width);
    m_showedProblem.set_plane_width(width);
    int row = m_absFormList->currentRow();
    initAbsFormList();
    m_absFormList->setCurrentRow(row);
}

void ProblemManager::setPlaneHeight(float height){
    problem.set_plane_height(height);
    m_showedProblem.set_plane_height(height);
    int row = m_absFormList->currentRow();
    initAbsFormList();
    m_absFormList->setCurrentRow(row);
}

void ProblemManager::addForm(QString name){
    AbstractForm form;
    problem.add_abstract_form(name.toUtf8().constData(), form);
    m_showedProblem.add_abstract_form(name.toUtf8().constData(), form);
    int row = problem.get_number_of_different_forms()-1;
    m_absFormList->addItem(getAbsFormListItem(row));
    m_absFormList->setCurrentRow(row);
    updateForm(row);
}

void ProblemManager::renameForm(int selectedForm, QString name){
    problem.rename_abstract_form(selectedForm,name.toUtf8().data());
    m_showedProblem.rename_abstract_form(selectedForm,name.toUtf8().data());
    QString item = getAbsFormListItem(selectedForm);
    m_absFormList->item(selectedForm)->setText(item);
}

void ProblemManager::delForm(int selectedForm){
    problem.erase_abstract_form(selectedForm);
    m_showedProblem.erase_abstract_form(selectedForm);
    m_invalidForms.remove(selectedForm);
    if(m_invalidForms.isEmpty()){
        setSolvableState(true);
    }
    initAbsFormList();
    if(selectedForm >= m_absFormList->count()){
        selectedForm = m_absFormList->count()-1;
    }
    if(problem.get_number_of_different_forms() == 0){
        emit problemEmpty();
    }
    m_absFormList->setCurrentRow(selectedForm);

}

void ProblemManager::addPointToForm(int selectedForm, float x, float y)
{
    problem.get_abstract_form_at_position(selectedForm)->add_point_to_form(x,y);
    m_showedProblem.get_abstract_form_at_position(selectedForm)->add_point_to_form(x,y);
    int row = problem.get_abstract_form_at_position(selectedForm)->get_number_of_points()-1;
    m_pointList->addItem(getPointListItem(selectedForm,row));
    m_pointList->setCurrentRow(row);
    updateForm(selectedForm);
}

void ProblemManager::editPointOfForm(int selectedForm, int selectedPoint, float x, float y)
{
    problem.get_abstract_form_at_position(selectedForm)->set_xy_of_point(selectedPoint, x, y);
    m_showedProblem.get_abstract_form_at_position(selectedForm)->set_xy_of_point(selectedPoint, x, y);
    m_pointList->item(selectedPoint)->setText(getPointListItem(selectedForm, selectedPoint));
    updateForm(selectedForm);
}

void ProblemManager::delPointOfForm(int selectedForm, int selectedPoint)
{    
    problem.get_abstract_form_at_position(selectedForm)->erase_point_at_index(selectedPoint);
    m_showedProblem.get_abstract_form_at_position(selectedForm)->erase_point_at_index(selectedPoint);
    initPoints(selectedForm);
    if(selectedPoint >= m_pointList->count()){
        selectedPoint = m_pointList->count()-1;
    }
    m_pointList->setCurrentRow(selectedPoint);
    updateForm(selectedForm);
}

void ProblemManager::movePointUp(int selectedForm, int selectedPoint){
    problem.get_abstract_form_at_position(selectedForm)->move_up_point_at_index(selectedPoint);
    m_showedProblem.get_abstract_form_at_position(selectedForm)->move_up_point_at_index(selectedPoint);
    initPoints(selectedForm);
    if(selectedPoint > 0){
        m_pointList->setCurrentRow(selectedPoint-1);
    }else{
        m_pointList->setCurrentRow(0);
    }
    updateForm(selectedForm);
}

void ProblemManager::movePointDown(int selectedForm, int selectedPoint){
    problem.get_abstract_form_at_position(selectedForm)->move_down_point_at_index(selectedPoint);
    m_showedProblem.get_abstract_form_at_position(selectedForm)->move_down_point_at_index(selectedPoint);
    initPoints(selectedForm);
    if(selectedPoint < m_pointList->count()-1){
        m_pointList->setCurrentRow(selectedPoint+1);
    }else{
        m_pointList->setCurrentRow(m_pointList->count()-1);
    }
    updateForm(selectedForm);
}

void ProblemManager::setAmountOfForm(int selectedForm, int amount)
{
    problem.set_amount_of_form(selectedForm,amount);
    m_showedProblem.set_amount_of_form(selectedForm,amount);
    m_absFormList->item(selectedForm)->setText(getAbsFormListItem(selectedForm));
}

AbstractForm* ProblemManager::getForm(int selectedForm){
    return m_showedProblem.get_abstract_form_at_position(selectedForm);
}

void ProblemManager::updateForm(int selectedForm, bool show){

    AbstractForm * form = problem.get_abstract_form_at_position(selectedForm);
    problem.check_if_solveable();
    QString error = "";
    if(form->get_number_of_points() < 3){
        error += " !to few points!";

    }
    else if(form->overlaps_itself()){
        error += " !overlaps itself!";

    }
    else if(problem.is_to_large(selectedForm)){
        error += " !to large!";
    }else{
        if(show){
            m_formview->showForm(form);
        }
        m_pointList->setStyleSheet("QListWidget {border:2px solid green;}");
        m_invalidForms.remove(selectedForm);
        if(m_invalidForms.isEmpty()){
            setSolvableState(true);
        }
    }
    if(!error.isEmpty()){
        m_formview->clear();
        m_pointList->setStyleSheet("QListWidget {border:2px solid red;}");
        m_invalidForms.insert(selectedForm);
        setSolvableState(false);
    }
    m_absFormList->item(selectedForm)->setText(getAbsFormListItem(selectedForm) + error);

}


Problem * ProblemManager::getShowedProblem()
{
    return &m_showedProblem;
}

void ProblemManager::setSolvableState(bool solvable)
{
    QString text;
    QString color;
    bool enabled;
    if(problem.get_number_of_different_forms() == 0){
        text = "You can't proceed - problem empty";
        enabled = false;
    } else{
        if(solvable){
            text = "Run solver";
            enabled = true;
        }else{
            text = "You can't proceed - problem invalid";
            enabled = false;
        }
    }
    m_solveButton->setText(text);
    if(enabled){
        m_solveButton->setStyleSheet("QPushButton {background-color: #008000;border-color: #008000;}QPushButton:hover {background-color: #006700;border-color: #004d00;}QPushButton:pressed {background-color: #004d00;border-color: #003400;}");
    }else{
        m_solveButton->setStyleSheet("QPushButton {background-color: #ff0000;border-color: #ff0000;}");
    }
    m_solveButton->setEnabled(enabled);
}


