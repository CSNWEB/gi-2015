#include "formview.h"

#include <QGraphicsRectItem>
#include <QGraphicsSvgItem>
#include <qmath.h>
#include <QTextStream>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPaintEvent>

#ifndef QT_NO_OPENGL
#include <QGLWidget>
#endif

#include <point.hpp>

FormView::FormView(QWidget *parent)
    :QGraphicsView(parent)
{
    setScene(new QGraphicsScene(this));
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);

    // Prepare background check-board pattern
    QPixmap tilePixmap(64, 64);
    tilePixmap.fill(Qt::white);
    QPainter tilePainter(&tilePixmap);
    QColor color(220, 220, 220);
    tilePainter.fillRect(0, 0, 32, 32, color);
    tilePainter.fillRect(32, 32, 32, 32, color);
    tilePainter.end();

    setBackgroundBrush(tilePixmap);

}

FormView::~FormView()
{

}

void FormView::setContainer(QWidget *_container)
{
    container = _container;
}




void FormView::showForm(AbstractForm * form)
{

    QGraphicsScene *s = scene();

    s->clear();
    resetTransform();

    if(form == 0){
        return;
    }
    if(form->get_number_of_points() <= 0) {
        return;
    }

    QPolygonF polygon;
    for(int i=0; i<form->get_number_of_points(); ++i){
        Point point = form->get_point_at_index(i);
        polygon.push_back(QPointF(point.get_x(), point.get_y()));
    }



    s->addPolygon(polygon, QPen(), QBrush(Qt::SolidPattern));

    QRectF bound = polygon.boundingRect();

    s->setSceneRect(bound);

    float realwidth = container->width() - 50;
    float width = bound.width();
    float realheight = container->height() - 50;
    float height = bound.height();

    float relw = 1;
    if(width > 0){
        relw =  realwidth / width;
    }

    float relh = 1;
    if(height > 0){
        relh = realheight / height;
    }

    float rel = relw;
    if(relh < relw){
        rel = relh;
    }

    scale(rel,rel);



}

void FormView::showSetting(Setting *setting)
{
    QGraphicsScene *s = scene();

    s->clear();
    resetTransform();


    int scale_fac = 10;
    int spacing = 20;
    int planeWidth = setting->get_problem()->get_plane_width()*scale_fac;
    int planeHeight = setting->get_problem()->get_plane_height()*scale_fac;
    QRectF bound;
    for (int i=0; i<setting->get_number_of_planes(); ++i)
    {
        int x_offset = i*(planeWidth+spacing)+(spacing/2);
        int y_offset = (spacing/2);
        QRectF plane(x_offset,y_offset,planeWidth, planeHeight);
        s->addRect(plane,QPen(), QBrush(QColor(188, 198, 204),Qt::SolidPattern));
        for (int j=0; j<setting->get_plane_at(i)->get_number_of_forms(); ++j)
        {
            QPolygonF polygon;
            vector<Point> points_of_current_form = (setting->get_plane_at(i))->get_form_at(j)->get_points();
            for (int k=0; k<points_of_current_form.size(); ++k){
                Point point = points_of_current_form[k];
                polygon.push_back(QPointF(point.get_x()*scale_fac, point.get_y()*scale_fac));
            }

            QGraphicsPolygonItem * polyitem = s->addPolygon(polygon, QPen(), QBrush(Qt::SolidPattern));
            polyitem->setPos(x_offset, y_offset);
            bound = polygon.boundingRect();
        }
    }


    float realwidth = container->width() - 50;
    float width = setting->get_number_of_planes()*(planeWidth+spacing);
    float realheight = container->height() - 50;
    float height = planeHeight+spacing;
    s->setSceneRect(0,0,width,height);

    float relw = 1;
    if(width > 0){
        relw =  realwidth / width;
    }

    float relh = 1;
    if(height > 0){
        relh = realheight / height;
    }

    float rel = relw;
    if(relh < relw){
        rel = relh;
    }

    scale(rel,rel);

}



void FormView::wheelEvent(QWheelEvent *event)
{
    qreal factor = qPow(1.2, event->delta() / 240.0);
    scale(factor, factor);
    event->accept();
}

void FormView::paintEvent(QPaintEvent *event)
{
        QGraphicsView::paintEvent(event);
}
