#ifndef PROBLEMMANAGER_H
#define PROBLEMMANAGER_H

#include "problem.hpp"
#include "abstractForm.hpp"
#include "inputHandler.hpp"
#include <QString>
#include <QListWidget>
#include <QPushButton>
#include <QSizeF>
#include <QSet>
#include "point.hpp"
#include "binPacking.hpp"

#include "formview.h"

class ProblemManager : public QObject
{
    Q_OBJECT

signals:
    void problemEmpty();

public:
    ProblemManager(FormView * m_formview);
    ~ProblemManager();

    void setUiElements(QListWidget* absFormList, QListWidget* m_pointList, QPushButton* solveButton);
    void initAbsFormList();
    int initPoints(int selectedForm);
    QSizeF loadFromFile(QString fileName);
    Problem  getProblem();
    Problem * getShowedProblem();


    void setPlaneWidth(float width);
    void setPlaneHeight(float height);
    void addForm(QString name);
    void renameForm(int selectedForm, QString name);
    void delForm(int selectedForm);

    void setAmountOfForm(int selectedForm, int amount);

    void addPointToForm(int selectedForm, float x, float y);
    void editPointOfForm(int selectedForm, int selectedPoint, float x, float y);
    void delPointOfForm(int selectedForm, int selectedPoint);
    void movePointUp(int selectedForm, int selectedPoint);
    void movePointDown(int selectedForm, int selectedPoint);

    BinPacking getBinPacking(){return BinPacking(problem);}

    /*!
     * Checks if the form is valid and fits on the current plane size
     * afterwards it updates the entry in the absFormList
     *
     * @param selectedForm      index of the currently selected form that should be updated
     */
    void updateForm(int selectedForm, bool show = true);

    AbstractForm* getForm(int selectedForm);


private:
    Problem problem;

    //Because problem mutates the forms, we need another one for storing the showed and saved data
    Problem m_showedProblem;
    QListWidget* m_absFormList;
    QListWidget* m_pointList;
    QPushButton * m_solveButton;
    FormView * m_formview;
    QSet<int> m_invalidForms;

    QString getAbsFormListItem(int i);
    QString getPointListItem(int form, int point);

    void setSolvableState(bool solvable);


};

#endif // PROBLEMMANAGER_H
