#ifndef PROBLEMMANAGER_H
#define PROBLEMMANAGER_H

#include <problem.hpp>
#include <abstractForm.hpp>
#include <inputHandler.hpp>
#include <QString>
#include <QListWidget>
#include <QSizeF>
#include <point.hpp>

class ProblemManager
{
public:
    ProblemManager();
    ~ProblemManager();

    void setLists(QListWidget* absFormList, QListWidget* pointList);
    void initAbsFormList();
    int initPoints(int selectedForm);
    QSizeF loadFromFile(QString fileName);
    Problem* getProblem();

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

    AbstractForm* getForm(int selectedForm);


private:
    Problem problem;
    QListWidget* absFormList;
    QListWidget* pointList;

    QString getAbsFormListItem(int i);
    QString getPointListItem(int form, int point);
};

#endif // PROBLEMMANAGER_H
