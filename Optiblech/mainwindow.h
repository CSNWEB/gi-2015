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

    void problemEmpty();

private slots:
    void on_solveButton_clicked();

    void on_selectInputButton_clicked();

    void on_pushButton_clicked();

    void on_absFormList_currentRowChanged(int currentRow);

    void on_saveSVG_clicked();

    void on_addFormButton_clicked();

    void on_delFormButton_clicked();

    void on_editFormButton_clicked();

    void on_delPointButton_clicked();

    void on_addPointButton_clicked();

    void on_editPointButton_clicked();

    void on_saveTXT_clicked();

    void on_pointAmount_valueChanged(int arg1);

    void on_pushButton_2_clicked();    

    void on_showCaseCheckBox_clicked(bool checked);

    void on_pointList_currentRowChanged(int currentRow);

    void on_toleranceSpinBox_valueChanged(double arg1);

    void on_helpButton_clicked();

    void on_planeWidth_editingFinished();

    void on_planeHeight_editingFinished();

private:
    Ui::MainWindow *ui;


    FormView *m_formview;

    FormView *m_resultview;

    QString m_currentPath;

    ProblemManager *pm;

    vector<QDialog *> editFormDialogs;

    BinPacking * bin_packing = 0;

    void invalidForm(bool invalid);

    void enableEditFormButton(bool enabled);
    void enableEditPointButtons(bool enabled);
    void enableSaveButtons(bool enabled);

};

#endif // MAINWINDOW_H
