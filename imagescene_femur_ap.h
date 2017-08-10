#pragma once
#ifndef IMAGESCENE_FEMUR_AP_HPP
#define IMAGESCENE_FEMUR_AP_HPP
#include "ImageScene.h"
#include "tablesketch_item.h"
class imageScene_Femur_AP : public ImageScene {
	
    Q_OBJECT
public:
    imageScene_Femur_AP(QObject * parent = 0);
    ~imageScene_Femur_AP();

    QGraphicsLineItem *Line4_5;//四五直线
    QGraphicsLineItem *Line1_2;//一二直线
    QGraphicsLineItem *subline1;//等比例辅助线直线
    QGraphicsLineItem *subline2;//等比例辅助线直线
    //QGraphicsLineItem *Marker_Tip;//探针直线

	float distance_DotToLine(QPointF linePoint1, QPointF linePoint2, QPointF dot);
	void show_otherItem();
	
private:
	
    QLineF offsetLine(QPointF linePoint1, QPointF linePoint2,float distance);
    float radioA4toA3;
    float radioA5toA3;
public slots:
    void showsubline1(float radio);
    void showsubline2(float radio);

};


#endif // IMAGESCENE_FEMUR_AP_HPP
