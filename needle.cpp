#include "needle.h"
#include "qpainter.h"
#include "QGraphicsLineItem"
#include "qbrush.h"
needle::needle(QGraphicsItem *parent):QGraphicsItem(parent),
	width(10),height(100),pen(QPen(Qt::cyan, 1))
{
//    width = 10;
//    height = 1000;
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
    return QRectF(0 - pen.width() / 2 - width/2, -500 - pen.width()/2 , width/2 + pen.width() / 2, height + pen.width() / 2 +10);
}

void needle::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    QRect ur = widget->geometry();//得到组件尺寸
    QPixmap pix(ur.size());//以此为参数创建一个位图变量
    pix.fill();
    painter->setBackgroundMode(Qt::TransparentMode);
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(pen);

    painter->drawLine(QPoint( 0, 0), QPoint( -width/2 , width/2));
    painter->drawLine(QPoint( 0, 0), QPoint( width/2 , width/2));
    painter->drawLine(QPoint(-width/2 , width/2), QPoint( -width/2 , height));
    painter->drawLine(QPoint(width / 2, width / 2), QPoint(width / 2, height));
    painter->setBrush(QColor(150, 150, 80, 150));
    painter->drawRect(QRect(-width / 2, width / 2, width, height - width / 2));
    QPoint pt[3] = { QPoint(-width / 2, width / 2) , QPoint(0,0) , QPoint(width / 2 ,width / 2) };
    painter->drawPolygon(pt, 3);

    painter->setPen(QPen(Qt::magenta, 2, Qt::SolidLine));
    painter->drawLine(QPoint(0,height+10),QPoint(0,-500));

}

void needle::setLine(QPointF pt1, QPointF pt2)
{
    setPos(pt1);
    float norm = sqrtf((pt1 - pt2).x() * (pt1 - pt2).x() + (pt1 - pt2).y() * (pt1 - pt2).y());
    setHeight(norm);
    float angle =  acosf((pt2 - pt1).y()/ norm);
    this->setTransform(QTransform().translate(0,-height/2).
                       rotate(angle * 180 / 3.141592653).translate(0,height/2));
}

void needle::setLine(float pt1_x, float pt1_y, float pt2_x, float pt2_y)
{
    
    float norm = sqrtf((pt1_x -pt2_x) * (pt1_x -pt2_x) + (pt1_y - pt2_y) * (pt1_y - pt2_y));
    setHeight(norm);
    float angle =  atanf((pt1_y - pt2_y)/(pt1_x - pt2_x));

    if(((pt1_y - pt2_y) > 0 && (pt1_x - pt2_x) > 0) || ((pt1_y - pt2_y) < 0 && (pt1_x - pt2_x) > 0))
    {
        angle += 3.141592653;
    }
    angle -= 3.141592653 / 2;
    this->setTransform(QTransform().rotate(angle * 180 / 3.141592653));
    setPos(QPointF(pt1_x, pt1_y));
}

void needle::setPen(QPen pen1)
{
	pen = pen1;
}
