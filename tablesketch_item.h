#pragma once
#ifndef TABLESKETCH_ITEM_H
#define TABLESKETCH_ITEM_H
#include <QGraphicsItem>
#include<qpainter.h>
class TableSketch_Item : public QGraphicsItem {
	//Q_OBJECT

public:
	TableSketch_Item();
	TableSketch_Item(float ItemWidth,float ItemHeight,float Pos_X,float Pos_Y);
	~TableSketch_Item();
	void setWidth(float ItemWidth);
	void setHeight(float ItemHeight);
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	float width;
	float height;
private:
	
};

#endif // TABLESKETCH_ITEM_HPP