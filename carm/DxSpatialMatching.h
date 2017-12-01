#ifndef DxSpatialMatching_H
#define DxSpatialMatching_H
#pragma once
#include <QVector>
#include <math.h>
#include <QMap>
#include ".\carm\DxPoint.h"
//#include "Common/Utility/DxMatrix4x4.h"
using namespace std;


typedef struct StandardLine
{
    double dSlope;
    double dIntercept;
}StandardLine_t;

typedef struct LineInfo
{
    DxPoint PointStart;
    DxPoint PointEnd;
}LineInfo_t;

class DxSpatialMatching
{

private:
    QVector<DxPoint> m_stPointInfo;

public:
    DxSpatialMatching(void);
    ~DxSpatialMatching(void);

      bool PushAllPointInfo( QVector<DxPoint>&vecPoint3DInfo,QVector<DxPoint>&vecPoint2DInfo);

    QVector<double>& GetxSpotMatrix();
    QVector<double>& GetxSpotMatrixByHand();//2
    QMap<int,DxPoint>& DxSpatialMatching::GetxSpotPointMap();
    bool CalculateTheMatrix(const QVector<DxPoint>&vecPoint3DInfo,
        const QVector<DxPoint>& vecPoint2DInfo,
        const QVector<int>& vec3DComparedNum);//1,3D????????
    void  GetxSpotPointGroupInfo(QVector<QVector<DxPoint>>& vecGroupPoint);
    void SetDicomSize(int nWight , int nHeight);
    bool Get2DCoordinatesBy3DPoint(const QVector<double>& vecMartix, const DxPoint & stPoint3DInfo, DxPoint & stPoint2DInfo);
private:
    bool FindPyramidProjectionPoint3D(  QVector<DxPoint>& vec3DPointInfo,
        QVector<DxPoint>& vecPyramidPoint3D);
     void PlaneIntersectionPoint(const QVector<StandardLine_t>& vecStandardLine,
        const QVector<LineInfo_t>& vecLineInfo,
        QVector<DxPoint>& vecCrossPoint,
        QVector<DxPoint>& vecNoColinearCrossPoint);
    void IntersectionPoint( const QVector<LineInfo_t>& vecLineInfo,QVector<DxPoint>&vecCrossPoint);
    DxPoint Cross(DxPoint a,DxPoint b);
    void FindCentroid( const QVector<DxPoint>& vecCrossPoint,DxPoint& stCentroidPoint);
    double TwoPointDistance(const DxPoint& Point1, const DxPoint& Point2);
    void FindMidPoint(const QVector<DxPoint>& vecPointInfo,DxPoint& Point);
    bool IsThreePointFormS1Line(const QVector<DxPoint>&vecPointInfo);
    bool RankedPointInfo(QVector<DxPoint>& vecPointInfo,int& ncollinearTime);
    bool CheckPointInfoExistInVector(const DxPoint& stPointInfo,const QVector<DxPoint>& vecPointInfo);
    void FindThreePointCollineation(QVector<DxPoint>&vecPointInfo,QVector<DxPoint>&vecCollinearPoint,const DxPoint& stCurrentPoint);
     void RankedPointDirection(QVector<DxPoint>& vecPointInfo,const DxPoint& stCrossPoint);
    void Ranked2DPointInfo(QVector<DxPoint>&vecPointInfo,
        const DxPoint& stPyramidPointS2,const int&nCollinearTime);
     void FittingStraightLine(const QVector<DxPoint>& vecPointInfo,StandardLine_t& stLine);
     bool FindPymaidPointS2ByOneStandardLine( QVector<DxPoint>& vecRankedPoint, QVector<DxPoint>& vecCrossInfo, DxPoint& stPyramidPointS2);
     void GetProjectionPtOfPointToLine( DxPoint Point, DxPoint LinePt1, DxPoint LinePt2, DxPoint& ProjectionPt);
     bool CheckThreePointInOneLine(QVector<DxPoint>& vecThreePointInfo);
     void CheckCrossPtIsS2(
         DxPoint crosspt,
         QVector<DxPoint> vecLeftPoint,
         QVector<DxPoint>& vecGroup,
         int& nLineNum,
         double &dDisVariance);
     void DivideGroupByS2(DxPoint ptS2, QVector<DxPoint> vecLeftPoint, QVector<DxPoint>& vecGroupPoint);
     void TryAllSituationOfRank(
         int nCollearTime,
         int nTotalGroupNum,
         QVector<int> vecLeftGroupIndex,
         QVector<int> vecCurrentCompareNum,
         QVector<QVector<int>>& vecAllCompareNum);
    bool Compare2DTo3DPoint(const QVector<DxPoint>&vecPyramidPoint3D,const QVector<DxPoint>&vecPoint3DInfo,
        QVector<DxPoint>&vecPoint2DInfo);
    bool CheckPointDirction(const QVector<LineInfo_t>&vecLineInfo,const DxPoint&stPyramidPoint);
    bool DxSpatialMatching::ComparePyramidPoint3DTo2D(const QVector<DxPoint>&vecPyramidPoint3D,
        const QVector<DxPoint>&vecPyramidPoint2D,const DxPoint& stMarkerPoint);
    bool DxSpatialMatching::FindAllGroup( QVector<DxPoint>vecDividePoint,
        QVector<DxPoint>vecUnDividePoint,
        QVector<QVector<DxPoint>>&vecPoint2DInfo);
    bool FindTheRightCompare(QVector<DxPoint> vecPyramidPoint3D,
        QVector<DxPoint> vecPoint3D,QVector<QVector<DxPoint>> vecGroupPoint,QVector<DxPoint> vecAllPt2D,int nCollearTime);
    double FindExistPointInfoInVector( DxPoint stPointInfo,const QVector<DxPoint>& vecPointInfo,QMap<int,DxPoint>&mapXspotRank,int nRankNum);
 //   bool CheckTheLightPointInXspot( QVector<DxPoint>vecGroupPoint, QVector<DxPoint> vecRaypymidPt);
    bool FindTheRightCompareByOnlyTwoPtGroup(
        QVector<DxPoint> vecPyramidPoint3D,
        const QVector<DxPoint>& vecPoint3DInfo,
        const QVector<DxPoint>& vecPoint2DInfo,
        const QVector<DxPoint>& vecRankedPoint);

private:
    QVector<double> m_vecMartix;
    QMap<int,DxPoint> m_XspotPt;
    QVector<QVector<DxPoint>> m_vecPointGroup;
    QMap<int,DxPoint> m_XspotPtRightCompare;
    bool m_bAllGroupDivid;
//	DxMatrix4x4 m_matrixToXspot;
    double m_dDisVariance;
    int m_nDicomWight;
    int m_nDicomHeight;
};
#endif
