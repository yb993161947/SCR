#include "tablesketch_item.h"

TableSketch_Item::TableSketch_Item(){
    width = 1;
    height = 1;
}

TableSketch_Item::TableSketch_Item(float ItemWidth, float ItemHeight, float Pos_X, float Pos_Y)
{
	width = ItemWidth;
	height = ItemHeight;
	setPos(Pos_X, Pos_Y);
}

TableSketch_Item::~TableSketch_Item() {
	
}

void TableSketch_Item::setWidth(float ItemWidth)
{
	width = ItemWidth;
	update();
}

void TableSketch_Item::setHeight(float ItemHeight)
{
	height = ItemHeight;
	update();
}

QRectF TableSketch_Item::boundingRect() const
{
	return QRectF(0, 0, width, height);
	//return QRectF(0 - penWidth / 2, 0 - penWidth / 2, width + penWidth / 2, height + penWidth / 2);
}

void TableSketch_Item::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setPen(QPen(Qt::blue,1,Qt::DashLine));
    for (size_t i = 1; i < 4; i++)
    {
        //水平线
        painter->drawLine(QPoint(i * width / 4, 0), QPoint(i * width / 4, height));
        //垂直线
        painter->drawLine(QPoint(0, i * height / 4), QPoint(width, i * height / 4));
    }
    painter->setPen(QPen(Qt::green, 3));
    painter->drawLine(QPoint(0, 0), QPoint(0, height));
    painter->drawLine(QPoint(width, 0), QPoint(width, height));
    painter->drawLine(QPoint(0, 0), QPoint(width, 0));
    painter->drawLine(QPoint(0, height), QPoint(width, height));

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap));
    painter->drawEllipse(width * (0.75 - 0.07), height * 0.25- width * 0.07, width * 0.14 , width * 0.14);

}
