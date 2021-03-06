#include <QtGui>
#include "PolyDot.h"

PolyDot::PolyDot():QGraphicsItem(),dispRect(false),dispLabel(true)
{
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
    acceptHoverEvents();
}

QPointF PolyDot::center(){
    return QPointF(pos().x() - boundingRect().width()/2,pos().y() -boundingRect().height()/2);
}

QRectF PolyDot::boundingRect() const
{
    return QRectF(-20, -20, 20, 20);
}

QRectF PolyDot::markerRect() const
{
    return QRectF(-20, -20, 20, 20);
}

void PolyDot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::white);
    painter->drawEllipse(-12,-12,5,5);
    if(dispRect){
        painter->setPen(Qt::white);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(markerRect());
    }

    if(dispLabel){
        QString label;
        QString y;
        label.setNum(center().x());
        label += ",";
        y.setNum(center().y());
        label += y;
        painter->drawText(QPointF(0,0),label);
    }
}

void PolyDot::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    setCursor(Qt::ClosedHandCursor);
}

void PolyDot::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    setPos(this->pos() +event->pos());
    scene()->update();
    emit dotMoved();
}

void PolyDot::mouseReleaseEvent(QGraphicsSceneMouseEvent *){
    setCursor(Qt::OpenHandCursor);
    scene()->update();
    emit dotMoved();
}

void PolyDot::hoverEnterEvent(QGraphicsSceneHoverEvent *event){    
    Q_UNUSED(event)
    setCursor(Qt::OpenHandCursor);
    dispRect=true;
    scene()->update();
}

void PolyDot::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    Q_UNUSED(event)
    dispRect=false;
    scene()->update();
}

void PolyDot::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    Q_UNUSED(event)
    scene()->update();
}
