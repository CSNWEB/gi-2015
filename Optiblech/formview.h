#ifndef FORMVIEW_H
#define FORMVIEW_H

#include <QGraphicsView>
#include <abstractForm.hpp>

class FormView : public QGraphicsView
{
     Q_OBJECT

public:
    FormView(QWidget *parent = 0);
    void setContainer(QWidget * _container);
    void showForm(AbstractForm * form = 0);
    ~FormView();

private:
    QGraphicsItem *m_svgItem;

    QImage m_image;

    QWidget * container;
};

#endif // FORMVIEW_H
