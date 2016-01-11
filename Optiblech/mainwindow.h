#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <problem.hpp>
#include <setting.hpp>
#include <binPacking.hpp>

class SvgView;
class ProblemManager;
class FormView;

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

public slots:
    void updateResultView();

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

    void on_pointAmount_valueChanged(int arg1);

    void on_pushButton_2_clicked();    

    void on_toleranceSpinBox_valueChanged(int arg1);

    void on_showCaseCheckBox_clicked(bool checked);       

private:
    Ui::MainWindow *ui;

    SvgView *m_view;

    FormView *m_formview;

    FormView *m_resultview;

    QString m_currentPath;

    ProblemManager *pm;

    vector<QDialog> editFormDialogs;

    Setting setting;

    BinPacking bin_packing;


};

#endif // MAINWINDOW_H
