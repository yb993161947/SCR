#ifndef NEEDLE_H
#define NEEDLE_H
#include "QGraphicsItem"

class needle : public QGraphicsItem
{
public:
    needle(QGraphicsItem *parent= 0 );
    ~needle();
    needle(float ItemWidth,float ItemHeight,float Pos_X,float Pos_Y);
    void setWidth(float ItemWidth);
    void setHeight(float ItemHeight);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    float width;
    float height;
};

#endif // NEEDLE_H
