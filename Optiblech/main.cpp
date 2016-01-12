#include "mainwindow.h"
#include <QApplication>

#include <QFontDatabase>
#include <QFont>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QString fontPath = ":/fonts/Roboto-Regular.ttf";
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    if(fontId != -1){
        QFont font("Roboto");
        w.setFont(font);
    }
    qDebug() << fontId;

    w.show();


    return a.exec();
}
