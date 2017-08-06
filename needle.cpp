#include "needle.h"
#include "qpainter.h"
#include "QGraphicsLineItem"
needle::needle(QGraphicsItem *parent):QGraphicsItem(parent)
{
    width = 10;
    height = 1000;
}

needle::needle(float ItemWidth, float ItemHeight, float Pos_X, float Pos_Y)
{
    width = ItemWidth;
    height = ItemHeight;
    setPos(Pos_X, Pos_Y);
}


needle::~needle() {

}

void needle::setWidth(float ItemWidth)
{
    width = ItemWidth;
    update();
}

void needle::setHeight(float ItemHeight)
{
    height = ItemHeight;
    update();
}

QRectF needle::boundingRect() const
{
    return QRectF(0, 0, width, height);
    //return QRectF(0 - penWidth / 2, 0 - penWidth / 2, width + penWidth / 2, height + penWidth / 2);
}

void needle::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(Qt::cyan,1,Qt::DashLine));

    painter->drawLine(QPoint( 0, 0), QPoint( 0 , -width/2));

    painter->drawLine(QPoint( 0, 0), QPoint( 0 , width/2));

    painter->drawLine(QPoint( 0 , -width/2), QPoint( 0 , height));

    painter->drawLine(QPoint( 0 , width/2), QPoint( width/2 , height));
}

void needle::setLine(QPointF pt1, QPointF pt2)
{
    setPos(pt1);
    float norm = sqrtf((pt1 - pt2).x() * (pt1 - pt2).x() + (pt1 - pt2).y() * (pt1 - pt2).y());
    setHeight(norm);
    float angle =  acosf((pt1 - pt2).y()/ norm);
    this->setTransform(QTransform().rotate(angle));




}
