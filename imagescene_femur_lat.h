#pragma once
#ifndef IMAGESCENE_FEMUR_LAT_HPP
#define IMAGESCENE_FEMUR_LAT_HPP
#include "ImageScene.h"
#include "tablesketch_item.h"
class imageScene_Femur_Lat : public ImageScene {
  Q_OBJECT

public:
	imageScene_Femur_Lat(QObject * parent = 0);
	~imageScene_Femur_Lat();

	TableSketch_Item *tablesketch;//四方格
    QGraphicsLineItem *Line4_5;//四五直线
    QGraphicsLineItem *Line1_2;//一二直线
    //QGraphicsLineItem *Marker_Tip;//一二直线
    QGraphicsLineItem *subline1;//等比例辅助线直线
    QGraphicsLineItem *subline2;//等比例辅助线直线

protected:
    void show_otherItem();//paint函数中的虚函数

private:
	float distance_DotToLine(QPointF linePoint1, QPointF linePoint2, QPointF dot);


signals:
    void dotsHasSelected1(float);
    void dotsHasSelected2(float);


};

#endif // IMAGESCENE_FEMUR_LAT_HPP
