#pragma once
#ifndef IMAGESCENE_Tibia_lat_HPP
#define IMAGESCENE_Tibia_lat_HPP
#include "ImageScene.h"
class imageScene_Tibia_lat : public ImageScene {
	
    Q_OBJECT
public:
    imageScene_Tibia_lat(QObject * parent = 0);
    ~imageScene_Tibia_lat();
    QGraphicsLineItem *Line1_4;//45直线
    QGraphicsLineItem *Line1_2;//12直线
    QGraphicsLineItem *Line1_2cross;//12直线垂线
    QGraphicsLineItem *Line5_6;//56直线
    QGraphicsLineItem *Line2_3;//23直线   
    //QGraphicsLineItem *Marker_Tip;//一二直线

    QGraphicsLineItem *subline1;//等比例辅助线直线
    QGraphicsLineItem *subline2;//等比例辅助线直线

protected:
	void show_otherItem();

private:
	float distance_DotToLine(QPointF linePoint1, QPointF linePoint2, QPointF dot);
signals:
    void dotsHasSelected1(float);
};

#endif // IMAGESCENE_Tibia_lat_HPP
