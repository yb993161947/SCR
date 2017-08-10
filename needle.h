#ifndef NEEDLE_H
#define NEEDLE_H
#include "QGraphicsItem"
#include <QPen>
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

    void setLine(QPointF pt1,QPointF pt2);
    void setLine(float pt1_x,float pt1_y,float pt2_x,float pt2_y);
	void setPen(QPen pen1);
private:
    float width;
    float height;
	QPen  pen;
};

#endif // NEEDLE_H
