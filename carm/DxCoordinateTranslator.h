#ifndef DXCOORDINATETRANSLATOR_H
#define DXCOORDINATETRANSLATOR_H

#include "./carm//DxCoordinateTranslatorGlobal.h"
#include "Common/Models/DxTransformMatrixModel.h"
#include "Common/Utility/DxMatrix4x4.h"
#include "Common/Utility/DxImage.h"
#include "Common/Models/DxMarkerMatrixContainerModel.h"
class CoordinateTranslator_EXPORT DxCoordinateTranslator
{
public:
    DxCoordinateTranslator();
    ~DxCoordinateTranslator();

public:
	static DxFunctionResult TransformPointFromMarkerAToMarkerB( DxMarkerMatrixContainerModelPtr& pMarkerMatrixContainerModel, 
		const QString& qsMarkerAName, const DxPoint& ptAPoint, 
		const QString& qsMarkerBName, DxPoint& ptBPoint );
    static DxFunctionResult GetMatrixFromMarkerAToMarkerB( DxMarkerMatrixContainerModelPtr& pMarkerMatrixContainerModel, 
        const QString& qsMarkerAName, const QString& qsMarkerBName, DxMatrix4x4& MarkerAToMarkerB );
	static DxFunctionResult Get2DCoordinatesBy3DPoint(const QVector<double>&vecMartix ,const DxPoint& stPoint3DInfo,
		DxPoint& stPoint2DInfo,const DxPoint2D& stImageOffset = DxPoint2D(0.0,0.0));

	static DxFunctionResult  Get3DCoordinatesBy2DPoint(const QVector<double>&vecMartix ,
        const DxPoint& stPoint2DInfo,
        QVector<DxPoint>& vecCrossPointInfo,
        const DxPoint2D& stImageOffset = DxPoint2D(0.0,0.0));   
	static DxFunctionResult  Get3DLineParameter(const QVector<double>&vecMartix, const DxPoint& stPoint2DInfo, QVector<double>&vecLineParameter,const DxPoint2D& stImageOffset = DxPoint2D(0.0,0.0));
	static DxFunctionResult  CalculatorRelativePoint(const DxImagePtr& pImage, const DxImagePtr& pRelativeImage, const DxPoint& kImagePoint, 
		DxPoint& kRelativeImagePoint, QVector<DxPoint>& kLine);

 	static DxFunctionResult  Get3DCrossPoint(const QVector<double>&vecMartix1, const DxPoint& stPoint2DInfo1, const DxPoint2D&stImageOffset1,const QVector<double>&vecMartix2, 
 		const DxPoint& stPoint2DInfo2, const DxPoint2D&stImageOffset2,DxPoint& st3DCrossPoint);

    static DxFunctionResult  Coordinates2DCrossPoint(const QVector<DxPoint>& vecLinePoint1, const QVector<DxPoint>& vecLinePoint2, DxPoint& stCrossPoint);
    static DxFunctionResult  Coordinates3DCrossPoint(const QVector<DxPoint>& vecLinePoint1, const QVector<DxPoint>& vecLinePoint2, DxPoint& stCrossPoint);
    static DxFunctionResult  GetLinePlaneCrossPoint(const QVector<double> vecLineMartix1,
        const DxPoint& stPlanePoint1,
        const DxPoint& stPlanePoint2,
        const DxPoint2D&stImageOffset1,
        const QVector<double> vecLineMartix2,
        const DxPoint& stLinePoint,
        const DxPoint2D&stImageOffset2,
        DxPoint& stCrossPoint);
	static DxFunctionResult CalculateDistanceDoubleLine( QVector<DxPoint>& vecLinePoint1, QVector<DxPoint>& vecLinePoint2, double& kDistance);
	static DxFunctionResult CalculateAngleDoubleLine( QVector<DxPoint>& vecLinePoint1, QVector<DxPoint>& vecLinePoint2, double& kAngle );
    static DxFunctionResult LinePlaneCross(QVector<double> vecLineParameter,QVector<double>vecPlaneParameter,DxPoint& crossPoint);
    static DxFunctionResult PointToLineMinDisPt(DxPoint stPoint,DxPoint stLinePt1,DxPoint stLinePt2,DxPoint& stLineMinDisPt);
private:
	static DxPoint Cross(DxPoint a,DxPoint b);
	static double Dot(DxPoint a,DxPoint b);
	static double Length(DxPoint a);
};

typedef QSharedPointer<DxCoordinateTranslator> DxCoordinateTranslatorPtr;

#endif // DXCOORDINATETRANSLATOR_H