#include "formview.h"

#include <QGraphicsRectItem>
#include <QGraphicsSvgItem>
#include <qmath.h>
#include <QTextStream>

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



/*void FormView:drawBackground(QPainter *p, const QRectF &)
{
    p->save();
    p->resetTransform();
    p->drawTiledPixmap(viewport()->rect(), backgroundBrush().texture());
    p->restore();
}*/




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

    //s->addItem(m_svgItem);

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


    //s->setSceneRect(m_outlineItem->boundingRect().adjusted(-1, -1, 1, 1));
}



