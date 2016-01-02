#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <problem.hpp>
#include <setting.hpp>

class SvgView;
class ProblemManager;

QT_BEGIN_NAMESPACE
class QAction;
class QGraphicsView;
class QGraphicsScene;
class QGraphicsRectItem;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_solveButton_clicked();

    void on_selectInputButton_clicked();

    void on_pushButton_clicked();

    void on_absFormList_currentRowChanged(int currentRow);

    void on_saveSVG_clicked();

    void on_planeWidth_valueChanged(double arg1);

    void on_planeHeight_valueChanged(double arg1);

    void on_addFormButton_clicked();

    void on_delFormButton_clicked();

    void on_editFormButton_clicked();

    void on_pointUpButton_clicked();

    void on_pointDownButton_clicked();

    void on_delPointButton_clicked();

    void on_addPointButton_clicked();

    void on_editPointButton_clicked();

    void on_saveTXT_clicked();

private:
    Ui::MainWindow *ui;

    SvgView *m_view;

    QString m_currentPath;

    ProblemManager *pm;

    vector<QDialog> editFormDialogs;

    Setting setting;

};

#endif // MAINWINDOW_H
