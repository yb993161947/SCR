#pragma once
#ifndef IMAGESCENE_Tibia_ap_HPP
#define IMAGESCENE_Tibia_ap_HPP
#include "ImageScene.h"
class imageScene_Tibia_ap : public ImageScene {
	
Q_OBJECT
public:
    imageScene_Tibia_ap(QObject * parent = 0);
    ~imageScene_Tibia_ap();

    QGraphicsLineItem *Line3_4;//四五直线
    QGraphicsLineItem *Line1_2;//一二直线
    QGraphicsLineItem *subline1;//等比例辅助线直线
    //QGraphicsLineItem *Marker_Tip;//一二直线
    QGraphicsLineItem *subline2;//等比例辅助线直线
protected:
	void show_otherItem();

private:
	float distance_DotToLine(QPointF linePoint1, QPointF linePoint2, QPointF dot);
    QLineF offsetLine(QPointF linePoint1, QPointF linePoint2,float distance);
    float radioB4toB3;

public slots:
    void showsubline1(float radio);
};

#endif // IMAGESCENE_Tibia_ap_HPP
