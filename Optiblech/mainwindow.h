#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class SvgView;

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

    void on_selectOutputButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    SvgView *m_view;

    QString m_currentPath;
};

#endif // MAINWINDOW_H
