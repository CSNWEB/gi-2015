#ifndef FORMVIEW_H
#define FORMVIEW_H

#include <QGraphicsView>
#include <abstractForm.hpp>
#include <setting.hpp>


QT_BEGIN_NAMESPACE
class QWheelEvent;
class QPaintEvent;
class QFile;
QT_END_NAMESPACE

class FormView : public QGraphicsView
{
     Q_OBJECT

public:
    FormView(QWidget *parent = 0);
    void setContainer(QWidget * _container);
    void showForm(AbstractForm * form = 0);
    void showSetting(Setting  setting = 0);
    ~FormView();

protected:
    void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QGraphicsItem *m_svgItem;

    QImage m_image;

    QWidget * container;
};

#endif // FORMVIEW_H
