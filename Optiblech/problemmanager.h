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
    Problem getProblem();


private:
    Problem problem;
    QListWidget* absFormList;
    QListWidget* pointList;
};

#endif // PROBLEMMANAGER_H
