#include "./carm/DxSpatialMatching.h"
#include <math.h>
#include <Eigen/Eigen>
#include <Eigen/LU>
#include <Eigen/StdVector>
#include <valarray>
//#include "FTTCommon/CoordinateTranslator/DxCoordinateTranslator.h"
using namespace Eigen;
const double dErrorLimitAngle = 5;
const double dErrorLimitAngle1 = 1;
const double dDistanceLimitPercent1 =0.2;
const double dParallelErrorLimit = 0.0001;
const double dDistanceLimitPercent = 0.2;
const double dNearPointLimitError = 10;
DxPoint operator +(DxPoint a, DxPoint b)
{
    DxPoint c(0,0,0);
    c.SetX(a.X()+b.X());
    c.SetY(a.Y()+b.Y());
    c.SetZ(a.Z()+b.Z());
    return c;
};

DxPoint operator -(DxPoint a, DxPoint b)
{
    DxPoint c(0,0,0);
    c.SetX(a.X()-b.X());
    c.SetY(a.Y()-b.Y());
    c.SetZ(a.Z()-b.Z());
    return c;
}; 
DxPoint operator *(DxPoint a, double p)
{
    DxPoint c(0,0,0);
    c.SetX(a.X()*p);
    c.SetY(a.Y()*p);
    c.SetZ(a.Z()*p);
    return c;
};
DxPoint operator /(DxPoint a, double p)
{
    DxPoint c(0,0,0);
    c.SetX(a.X()/p);
    c.SetY(a.Y()/p);
    c.SetZ(a.Z()/p);
    return c;
};
double Dot(DxPoint a,DxPoint b){return a.X()*b.X() +a.Y()*b.Y() +a.Z()*b.Z();}
double Length(DxPoint a){ return sqrt(Dot(a,a));}

DxSpatialMatching::DxSpatialMatching(void)
{
    m_vecPointGroup.clear();
    m_bAllGroupDivid = false;
    m_dDisVariance = 0.0;
    m_nDicomWight = 1024;
    m_nDicomHeight = 1024;
}

DxSpatialMatching::~DxSpatialMatching(void)
{
}

bool DxSpatialMatching::PushAllPointInfo( 
    QVector<DxPoint>&vecPoint3DInfo,
    QVector<DxPoint>&vecPoint2DInfo)
{
    if ( 0 == vecPoint3DInfo.size() 
        || 0 == vecPoint2DInfo.size())
    {
        return false;
    }

	int n = 0;
    QVector<DxPoint> vecPyramidPoint3D;
    QVector<DxPoint> vecRankedPoint2D;
    QVector<DxPoint> vecCrossPointInfo;
    QVector<DxPoint> vecPointTemp;
    QVector<DxPoint> vecPyramidPoint2D;
    QVector<int> vec3DComparedNum;
    vecPyramidPoint2D.clear();
    vec3DComparedNum.clear();
    vecPointTemp.clear();
    vecRankedPoint2D.clear();
    vecPyramidPoint3D.clear();
    bool bSuccess = FindPyramidProjectionPoint3D(vecPoint3DInfo,vecPyramidPoint3D);
    bSuccess = Compare2DTo3DPoint(vecPyramidPoint3D,vecPoint3DInfo,vecPoint2DInfo);
    if (!bSuccess)
    {
        return false;
    }

    return true;
}
bool DxSpatialMatching::Compare2DTo3DPoint(const QVector<DxPoint>&vecPyramidPoint3D,const QVector<DxPoint>&vecPoint3DInfo,
							QVector<DxPoint>&vecPoint2DInfo)
{
    if (vecPoint2DInfo.size() <6 )
    {
        return false;
    }
    QVector<DxPoint> vecRankedPoint;
    QVector<DxPoint>vecCollinearPoint; 
    vecCollinearPoint.clear();
    vecRankedPoint.clear();
    vecRankedPoint = vecPoint2DInfo;

    int nCollinearTime = 0;
    int nGroupNum  = 0;
    int nMissGroup = -1;
    DxPoint stPyramidPointS2(0,0,0);
    bool bSuccess = RankedPointInfo(vecRankedPoint,nCollinearTime);

    for (int i = 0 ; i < vecRankedPoint.size();i++)
    {
        m_XspotPt[i] = vecRankedPoint[i];
    }
    for (int i = 0; i < vecRankedPoint.size(); i++)
    {
        vecRankedPoint[i].SetZ(0);
    }
    QVector<int> vecCompareInfo;
    vecCompareInfo.clear();
 	int nTOTAl= 0;
    QVector<int> vecCompareTo3DNum;
    vecCompareTo3DNum.clear();
    if (nCollinearTime > 0)
    {
        QVector<StandardLine_t> vecStandardLine;
        LineInfo_t stLineInfo;
        QVector<LineInfo_t> vecLineInfo;
        StandardLine_t stLine;
        QVector<DxPoint> vecCrossPoint;
        QVector<DxPoint> vecNoColinearCrossPoint; 
        vecCrossPoint.clear();
        vecNoColinearCrossPoint.clear();
        for ( int i = 0;i < 3*nCollinearTime;i = i+3)
        {
            vecCollinearPoint.push_back(vecRankedPoint[i]);
            vecCollinearPoint.push_back(vecRankedPoint[i+1]);
            vecCollinearPoint.push_back(vecRankedPoint[i+2]);
            FittingStraightLine(vecCollinearPoint,stLine);
            vecStandardLine.push_back(stLine);
            vecCollinearPoint.clear();
        }
        for ( int i = 3*nCollinearTime;i < vecRankedPoint.size();i++)
        {
            for( int j = i+1; j < vecRankedPoint.size();j++)
            {   
                stLineInfo.PointStart = vecRankedPoint[i];
                stLineInfo.PointEnd = vecRankedPoint[j];
                vecLineInfo.push_back(stLineInfo);
            }
        }
        PlaneIntersectionPoint(vecStandardLine,vecLineInfo,vecCrossPoint,vecNoColinearCrossPoint);
        bool bFindSuccess = false;
        bool bNear = false;
        if (vecCrossPoint.size() != 0)
        {
            FindCentroid(vecCrossPoint,stPyramidPointS2);
        }
        else
        {
            if (vecNoColinearCrossPoint.size() > 0)
            {
                bFindSuccess = FindPymaidPointS2ByOneStandardLine(vecRankedPoint, vecNoColinearCrossPoint, stPyramidPointS2);
                if (!bFindSuccess)
                {
                    return false;
                }
            }
        }
        Ranked2DPointInfo(vecRankedPoint,stPyramidPointS2,nCollinearTime);
        nGroupNum = (vecRankedPoint.size() - 3*nCollinearTime)/2 + nCollinearTime;
        if (nGroupNum == 4)
        {
            m_bAllGroupDivid = true;
        }
        
        int nGroupStart = 0;
        QVector<DxPoint> vecGroupPoint;
        for (int i = 0 ; i < nGroupNum;i++)
        {
            if ( i <nCollinearTime )
            {
                vecGroupPoint.push_back(vecRankedPoint[3*i]);
                vecGroupPoint.push_back(vecRankedPoint[3*i+1]);
                vecGroupPoint.push_back(vecRankedPoint[3*i+2]);
                m_vecPointGroup.push_back(vecGroupPoint);
                vecGroupPoint.clear();
            }
            else
            {
                nGroupStart = 3*nCollinearTime+ 2*(i-nCollinearTime);
                vecGroupPoint.push_back(vecRankedPoint[nGroupStart]);
                vecGroupPoint.push_back(vecRankedPoint[nGroupStart+1]);
                m_vecPointGroup.push_back(vecGroupPoint);
                vecGroupPoint.clear();
            }
        }
        
        if (nGroupNum  < 3)
        {
            return false;
        }

        m_dDisVariance = 999999.0;
        return FindTheRightCompare(vecPyramidPoint3D,vecPoint3DInfo,m_vecPointGroup,vecPoint2DInfo,nCollinearTime);
    }
    else
    {
        m_dDisVariance = 999999.0;
        return FindTheRightCompareByOnlyTwoPtGroup(vecPyramidPoint3D,vecPoint3DInfo, vecPoint2DInfo, vecRankedPoint);    
    }

    return false;
}

bool DxSpatialMatching::FindTheRightCompareByOnlyTwoPtGroup(
    QVector<DxPoint> vecPyramidPoint3D,
    const QVector<DxPoint>& vecPoint3DInfo,
    const QVector<DxPoint>& vecPoint2DInfo,
    const QVector<DxPoint>& vecRankedPoint
){
    QVector<QVector<DxPoint>> vecHasFourLineGroup;
    QVector<QVector<DxPoint>> vecHasThreeLineGroup;
    vecHasFourLineGroup.clear();
    vecHasThreeLineGroup.clear();

    bool bGroup = false; 
    for (int nLine1Pt1Index = 0; nLine1Pt1Index < vecRankedPoint.size() - 6; nLine1Pt1Index++)
    {
        for (int nLine1Pt2Index = nLine1Pt1Index+1; nLine1Pt2Index < vecRankedPoint.size(); nLine1Pt2Index++)
        {
            bGroup = false;
            for (int nLine2Pt1Index = nLine1Pt1Index+1; nLine2Pt1Index < vecRankedPoint.size(); nLine2Pt1Index++)
            {
                if (bGroup) break;
                if (nLine2Pt1Index == nLine1Pt2Index)
                {
                    continue;
                }
                for (int nLine2Pt2Index = nLine2Pt1Index+1; nLine2Pt2Index < vecRankedPoint.size(); nLine2Pt2Index++)
                {
                    if (bGroup) break;
                    if (nLine2Pt2Index == nLine1Pt1Index || nLine2Pt2Index == nLine1Pt2Index )
                    {
                        continue;
                    }

                    QVector<DxPoint> vecLeftPoint;
                    vecLeftPoint.clear();
                    for (int nLeftIndex = 0; nLeftIndex < vecRankedPoint.size(); nLeftIndex++)
                    {
                        if ( nLeftIndex <= nLine1Pt1Index || nLeftIndex == nLine1Pt2Index ||
                            nLeftIndex == nLine2Pt1Index || nLeftIndex == nLine2Pt2Index )
                        {
                            continue;
                        }
                        vecLeftPoint.push_back(vecRankedPoint[nLeftIndex]);
                    }

                    QVector<DxPoint> vecCrossPoint;
                    vecCrossPoint.clear();
                    QVector<LineInfo_t> vecLineInfo;
                    vecLineInfo.clear();
                    LineInfo_t stLineInfo;
                    stLineInfo.PointStart = vecRankedPoint[nLine1Pt1Index];
                    stLineInfo.PointEnd = vecRankedPoint[nLine1Pt2Index];
                    vecLineInfo.push_back(stLineInfo);
                    stLineInfo.PointStart =vecRankedPoint[nLine2Pt1Index];
                    stLineInfo.PointEnd =vecRankedPoint[nLine2Pt2Index];
                    vecLineInfo.push_back(stLineInfo);
                    IntersectionPoint(vecLineInfo,vecCrossPoint);

                    QVector<DxPoint> vecGroup;
                    vecGroup.clear();
                    vecGroup.push_back(vecRankedPoint[nLine1Pt1Index]);
                    vecGroup.push_back(vecRankedPoint[nLine1Pt2Index]);
                    vecGroup.push_back(vecRankedPoint[nLine2Pt1Index]);
                    vecGroup.push_back(vecRankedPoint[nLine2Pt2Index]);
                    int nLineNum = 0; 
                    double dDisVariance = 0.0;
                    CheckCrossPtIsS2(vecCrossPoint[0], vecLeftPoint, vecGroup, nLineNum, dDisVariance);

                    if(nLineNum == 2)
                    {
                        vecHasFourLineGroup.push_back(vecGroup);
                        bGroup = true;
                        break;
                    }
                    else if (nLineNum == 1)
                    {
                        vecHasThreeLineGroup.push_back(vecGroup);
                        bGroup = true;
                        break;
                    }

                }
            }
        }
    }

    QVector<QVector<DxPoint>> vecAllGroup;
    vecAllGroup.clear();
    if (vecHasFourLineGroup.size() > 0 )
    {
        for (int j = 0; j < vecHasFourLineGroup.size(); j ++)
        {
            for (int i = 0; i < vecHasFourLineGroup[j].size(); i += 2)
            {
                QVector<DxPoint> vecGroup;
                vecGroup.clear();
                vecGroup.push_back(vecHasFourLineGroup[j][i]);
                vecGroup.push_back(vecHasFourLineGroup[j][i+1]);

                vecAllGroup.push_back(vecGroup);
            }
            if (!FindTheRightCompare(vecPyramidPoint3D,vecPoint3DInfo,vecAllGroup,vecPoint2DInfo,0))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    else
    {
        for (int j = 0; j < vecHasThreeLineGroup.size(); j ++)
        {
            for (int i = 0; i < vecHasThreeLineGroup[j].size(); i += 2)
            {
                QVector<DxPoint> vecGroup;
                vecGroup.clear();
                vecGroup.push_back(vecHasThreeLineGroup[j][i]);
                vecGroup.push_back(vecHasThreeLineGroup[j][i+1]);

                vecAllGroup.push_back(vecGroup);
            }
            if (!FindTheRightCompare(vecPyramidPoint3D,vecPoint3DInfo,vecAllGroup,vecPoint2DInfo, 0 ))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return false;  
}

bool DxSpatialMatching::CalculateTheMatrix(const QVector<DxPoint>&vecPoint3DInfo,
                                           const QVector<DxPoint>&vecPoint2DInfo,
                                           const QVector<int>& vec3DComparedNum)
{
    m_vecMartix.clear();
    QVector<DxPoint> vecPointTemp;
    vecPointTemp.clear();
    int nCount = vecPoint2DInfo.size();
    nCount *=2;
    MatrixXd XTemp = MatrixXd(nCount, 12);
    MatrixXd X= MatrixXd(nCount, 11);

    VectorXd imgx = VectorXd(nCount);
    VectorXd wx = VectorXd(11);
    int nNum = 0;
    for ( int i = 0 ; i  < vec3DComparedNum.size();i++)
    {
        nNum = vec3DComparedNum[i];
        vecPointTemp.push_back(vecPoint3DInfo[nNum]);
    }
    nCount = 0;
    for ( int i = 0; i < vecPoint2DInfo.size(); i++) {
        XTemp.row(nCount) << vecPointTemp[i].X(),vecPointTemp[i].Y(),vecPointTemp[i].Z(),1,-vecPointTemp[i].X()*vecPoint2DInfo[i].X(),
            -vecPointTemp[i].Y()*vecPoint2DInfo[i].X(),-vecPointTemp[i].Z()*vecPoint2DInfo[i].X(),0,0,0,0,vecPoint2DInfo[i].X();
        nCount++;
        XTemp.row(nCount) << 0,0,0,0,-vecPointTemp[i].X()*vecPoint2DInfo[i].Y(),-vecPointTemp[i].Y()*vecPoint2DInfo[i].Y(),-vecPointTemp[i].Z()*vecPoint2DInfo[i].Y(),
            vecPointTemp[i].X(),vecPointTemp[i].Y(),vecPointTemp[i].Z(),1,vecPoint2DInfo[i].Y();
        nCount++;
    }
    X << XTemp.col(0),
        XTemp.col(1),
        XTemp.col(2),
        XTemp.col(3),
        XTemp.col(4),
        XTemp.col(5),
        XTemp.col(6),
        XTemp.col(7),
        XTemp.col(8),
        XTemp.col(9),
        XTemp.col(10);

    imgx = XTemp.col(11);

    wx = X.colPivHouseholderQr().solve(imgx);
    
    for (unsigned int i = 0;i<11;i++)
    {
        m_vecMartix.push_back(wx[i]);
    }
    return true;
}
void DxSpatialMatching::Ranked2DPointInfo(QVector<DxPoint>&vecPointInfo,
                                          const DxPoint& stPyramidPointS2,const int&nCollinearTime)
{
    QVector<DxPoint>vecPointInfoTemp;
    QVector<DxPoint>vecNoCollinearPoint;
    QVector<DxPoint>vecDividPoint;
    vecDividPoint.clear();
    vecNoCollinearPoint.clear();
    vecPointInfoTemp.clear();
    for (  int i =0 ; i< vecPointInfo.size();i++)
    {   
        if (i < 3*nCollinearTime)
        {
            vecPointInfoTemp.push_back(vecPointInfo[i]);
        }
        else
        {
            vecNoCollinearPoint.push_back(vecPointInfo[i]);
        }
    }
    RankedPointDirection(vecPointInfoTemp,stPyramidPointS2);
    DivideGroupByS2(stPyramidPointS2,vecNoCollinearPoint,vecDividPoint);
    for(int j = 0 ; j < vecDividPoint.size();j++)
    {
        vecPointInfoTemp.push_back(vecDividPoint[j]);
    }
    vecPointInfo = vecPointInfoTemp;
    return;
}

void DxSpatialMatching::RankedPointDirection(QVector<DxPoint>& vecPointInfo,const DxPoint& stCrossPoint)
{
    QVector<DxPoint> vecPointDirection;
    vecPointDirection.clear();
    double fMaxDistance = 0;
    double fMinDistance = 0;
    for ( int i = 0;i < vecPointInfo.size();i = i + 3)
    {
        double fDis1 = TwoPointDistance(vecPointInfo[i],stCrossPoint);
        double fDis2 = TwoPointDistance(vecPointInfo[i+1],stCrossPoint);
        double fDis3 = TwoPointDistance(vecPointInfo[i+2],stCrossPoint);
        fMaxDistance = ((fDis1>fDis2)&&(fDis1>fDis3))?fDis1:((fDis2>fDis1)&&(fDis2>fDis3))?fDis2:fDis3;
        fMinDistance = ((fDis1<fDis2)&&(fDis1<fDis3))?fDis1:((fDis2<fDis1)&&(fDis2<fDis3))?fDis2:fDis3;

        if (fDis1 == fMinDistance)
        {
            vecPointDirection.push_back(vecPointInfo[i]);
            if (fMaxDistance == fDis2)
            {
                vecPointDirection.push_back(vecPointInfo[i+2]);
                vecPointDirection.push_back(vecPointInfo[i+1]);
            }
            else
            {
                vecPointDirection.push_back(vecPointInfo[i+1]);
                vecPointDirection.push_back(vecPointInfo[i+2]);
            }
        }
        else if (fDis2 == fMinDistance)
        {
            vecPointDirection.push_back(vecPointInfo[i+1]);
            if (fMaxDistance == fDis1)
            {
                vecPointDirection.push_back(vecPointInfo[i+2]);
                vecPointDirection.push_back(vecPointInfo[i]);
            }
            else
            {
                vecPointDirection.push_back(vecPointInfo[i]);
                vecPointDirection.push_back(vecPointInfo[i+2]);
            }
        }
        else
        {
            vecPointDirection.push_back(vecPointInfo[i+2]);
            if (fMaxDistance == fDis2)
            {
                vecPointDirection.push_back(vecPointInfo[i]);
                vecPointDirection.push_back(vecPointInfo[i+1]);
            }
            else
            {
                vecPointDirection.push_back(vecPointInfo[i+1]);
                vecPointDirection.push_back(vecPointInfo[i]);
            }
        }
    }
    vecPointInfo = vecPointDirection;
    return;
}

void DxSpatialMatching::PlaneIntersectionPoint(const QVector<StandardLine_t>& vecStandardLine,
                                               const QVector<LineInfo_t>& vecLineInfo,
                                               QVector<DxPoint>& vecCrossPoint,
                                               QVector<DxPoint>& vecNoColinearCrossPoint)
{

    double dSlope = 0;
    double dIntercept = 0; 
    double dCrossPoint_x = 0;
    double dCrossPoint_y = 0; 
    //     int n = 0;
    DxPoint stCrossPoint(0,0,0);
    QVector<DxPoint> vecPoint;
    DxPoint stcenPoint;
    bool bIsParaller = false;

    for ( int i = 0;i < vecStandardLine.size(); i++ )
    {
        for ( int j = i+1;j < vecStandardLine.size(); j++)
        {
            //x = (k1-k2)/(b2-b1)
            stCrossPoint.SetX((vecStandardLine[i].dIntercept - vecStandardLine[j].dIntercept)/
                (vecStandardLine[j].dSlope -vecStandardLine[i].dSlope));
            //y = k1x +b
            stCrossPoint.SetY(stCrossPoint.X()*vecStandardLine[i].dSlope + vecStandardLine[i].dIntercept);
            vecCrossPoint.push_back(stCrossPoint);
        }
    }

    for ( int i = 0;i < vecLineInfo.size(); i++ )
    {
        for ( int j = 0;j < vecStandardLine.size(); j++)
        {

            dSlope = (vecLineInfo[i].PointStart.Y() - vecLineInfo[i].PointEnd.Y())/
                (vecLineInfo[i].PointStart.X() - vecLineInfo[i].PointEnd.X());
            dIntercept = -dSlope*vecLineInfo[i].PointStart.X() + vecLineInfo[i].PointStart.Y();
            if (fabs(dSlope -vecStandardLine[j].dSlope) < dParallelErrorLimit)
            {
                continue;
            }
            stCrossPoint.SetX((vecStandardLine[j].dIntercept - dIntercept)/
                (dSlope -vecStandardLine[j].dSlope ));
            //y = k1x +b
            stCrossPoint.SetY(stCrossPoint.X()*vecStandardLine[j].dSlope + vecStandardLine[j].dIntercept);
            vecPoint.clear();
            vecPoint.push_back(vecLineInfo[i].PointStart);
            vecPoint.push_back(vecLineInfo[i].PointEnd);
            vecPoint.push_back(stCrossPoint);
            FindMidPoint(vecPoint,stcenPoint);
            if (!DxPoint::IsEqual(stCrossPoint,stcenPoint))
            {
                vecNoColinearCrossPoint.push_back(stCrossPoint);
            }    
        }
    }
    return ;  
}

void DxSpatialMatching::FittingStraightLine(const QVector<DxPoint>&vecPointInfo,StandardLine_t& stLine)
{
    unsigned int nTotalPoint = vecPointInfo.size();
    valarray<double> data_x(nTotalPoint); 
    valarray<double> data_y(nTotalPoint); 
    double A =0.0; 
    double B =0.0; 
    double C =0.0; 
    double D =0.0; 
    double dTmp =0; 
    for (unsigned int i = 0;i<nTotalPoint;i++)
    {
        data_x[i] = vecPointInfo[i].X();
        data_y[i] = vecPointInfo[i].Y();
    }
    A = (data_x*data_x).sum(); 
    B = data_x.sum(); 
    C = (data_x*data_y).sum(); 
    D = data_y.sum(); 

    if(dTmp=(A*data_x.size()-B*B)) 
    { 
        stLine.dSlope = (C*data_x.size()-B*D)/dTmp; 
        stLine.dIntercept = (A*D-C*B)/dTmp; 
    } 
    else 
    { 
        stLine.dSlope=1; 
        stLine.dIntercept=0; 
    } 

}

// bool DxSpatialMatching::RankedPointInfo(QVector<DxPoint>& vecPointInfo,int& ncollinearTime)
// {
// 
//     unsigned int nTotalPoint = vecPointInfo.size();
//     QVector<DxPoint> vecRankedPoint;
//     QVector<DxPoint>  vecCollinearPoint;
//     QVector<DxPoint>  vecCollinearPointTemp;
//     QVector<DxPoint>  vecPointInfoTemp;
//     vecCollinearPoint.clear();
//     vecCollinearPointTemp.clear();
//     vecPointInfoTemp.clear();
//     vecRankedPoint.clear();
//     vecPointInfoTemp = vecPointInfo;
//     bool bFlag = false;
//     bool bFormS1Line = false;
//     while(vecPointInfoTemp.size() > 0)
//     {
//         FindThreePointCollineation(vecPointInfoTemp,vecCollinearPoint,vecPointInfoTemp[0]);
//         if (vecCollinearPoint.size() >= 3)
//         {
//             for ( int i = 0 ; i < vecCollinearPoint.size();i=i+3)
//             {
//                 vecCollinearPointTemp.push_back(vecCollinearPoint[i]);
//                 vecCollinearPointTemp.push_back(vecCollinearPoint[i+1]);
//                 vecCollinearPointTemp.push_back(vecCollinearPoint[i+2]);
//                 bFormS1Line = IsThreePointFormS1Line(vecCollinearPointTemp);
//                 if (bFormS1Line)
//                 {   
//                     ncollinearTime++;
//                     vecRankedPoint.push_back(vecCollinearPointTemp[0]);
//                     vecRankedPoint.push_back(vecCollinearPointTemp[1]);
//                     vecRankedPoint.push_back(vecCollinearPointTemp[2]);
//                     vecCollinearPoint.clear(); 
//                     for ( int i = 0; i < vecPointInfoTemp.size();i++)
//                     {
//                         if ((vecPointInfoTemp[i] != vecCollinearPointTemp[0])&&
//                             (vecPointInfoTemp[i] != vecCollinearPointTemp[1])&&
//                             (vecPointInfoTemp[i] != vecCollinearPointTemp[2]))
//                         {
//                             vecCollinearPoint.push_back(vecPointInfoTemp[i]);
//                         }
//                     }
//                     vecPointInfoTemp = vecCollinearPoint;
//                     vecCollinearPoint.clear();
//                     vecCollinearPointTemp.clear();
//                     break;
//                 }
//                 vecCollinearPointTemp.clear();
//             }
//             if (!bFormS1Line)
//             {
//                 vecCollinearPoint.clear(); 
//                 for ( int nTemp = 1; nTemp < vecPointInfoTemp.size(); nTemp++)
//                 {
//                     vecCollinearPoint.push_back(vecPointInfoTemp[nTemp]); 
//                 }
//                 vecPointInfoTemp = vecCollinearPoint;
//                 vecCollinearPoint.clear();
//             }
//         }
//         else
//         {
//             vecCollinearPoint.clear(); 
//             for ( int nTemp = 1; nTemp < vecPointInfoTemp.size(); nTemp++)
//             {
//                 vecCollinearPoint.push_back(vecPointInfoTemp[nTemp]); 
//             }
//             vecPointInfoTemp = vecCollinearPoint;
//             vecCollinearPoint.clear();
//         }
//     }
//     if (ncollinearTime != 0)
//     {
//         for ( int i = 0; i < vecPointInfo.size();i++)
//         {
//             bFlag = CheckPointInfoExistInVector(vecPointInfo[i],vecRankedPoint);
//             if (!bFlag)
//             {
//                 vecRankedPoint.push_back(vecPointInfo[i]);
//             }
//         }
//         
//         vecPointInfo = vecRankedPoint;
//         if((nTotalPoint == 6) &&(ncollinearTime >0))
//         {
//             return false;
//         }
//         if((nTotalPoint == 7) &&(ncollinearTime >1))
//         {
//             return false;
//         }
// 
//         return true;
//     }  
// 
//     return true;
// }


bool DxSpatialMatching::RankedPointInfo(QVector<DxPoint>& vecPointInfo,int& ncollinearTime)
{

	if (vecPointInfo.size() < 3)
	{
		return false;
	}

	QVector<DxPoint> vecRankedPoint;
	QVector<DxPoint>  vecCollinearPoint;
	QVector<DxPoint>  vecGroupPoint;
	QVector<DxPoint>  vecPointInfoTemp;
	vecCollinearPoint.clear();
	vecGroupPoint.clear();
	vecPointInfoTemp.clear();
	vecRankedPoint.clear();

	int nMaxGroupNum = 0;
	int nGroupNum = 0;

	FindThreePointCollineation(vecPointInfo,vecCollinearPoint,vecPointInfo[0]);
	if (vecCollinearPoint.size() >= 3)
	{
		
		for ( int i = 0 ; i < vecCollinearPoint.size();i=i+3)
		{
			vecGroupPoint.clear();
			vecPointInfoTemp.clear();
			ncollinearTime = 0;

			ncollinearTime++;
			vecGroupPoint.push_back(vecCollinearPoint[i]);
			vecGroupPoint.push_back(vecCollinearPoint[i+1]);
			vecGroupPoint.push_back(vecCollinearPoint[i+2]);

			for ( int i = 0; i < vecPointInfo.size();i++)
			{
				if ((vecPointInfo[i] != vecGroupPoint[0])&&
					(vecPointInfo[i] != vecGroupPoint[1])&&
					(vecPointInfo[i] != vecGroupPoint[2]))
				{
					vecPointInfoTemp.push_back(vecPointInfo[i]);
				}
			}
			
			RankedPointInfo(vecPointInfoTemp, nGroupNum);
			ncollinearTime += nGroupNum;

			if (ncollinearTime > nMaxGroupNum)
			{
				nMaxGroupNum = ncollinearTime;
				for (int j = 0; j < vecPointInfoTemp.size(); j++)
				{
					vecGroupPoint.push_back(vecPointInfoTemp[j]);
				}
				vecPointInfo = vecGroupPoint;
			}
		}
	}
	else
	{
		ncollinearTime = 0;
		for ( int nTemp = 1; nTemp < vecPointInfo.size(); nTemp++)
		{
			vecPointInfoTemp.push_back(vecPointInfo[nTemp]); 
		}
		RankedPointInfo(vecPointInfoTemp, nGroupNum);
		vecPointInfoTemp.push_back(vecPointInfo[0]);
		ncollinearTime += nGroupNum;

		if (ncollinearTime > nMaxGroupNum)
		{
			vecPointInfo = vecPointInfoTemp;
		}
	}
}


bool DxSpatialMatching::CheckPointInfoExistInVector(const DxPoint& stPointInfo,const QVector<DxPoint>& vecPointInfo)
{
    for ( int i = 0;i<vecPointInfo.size();i++)
    {
        if (stPointInfo == vecPointInfo[i])
        { 
            return true;      
        }
    }
    return false;    
}
bool DxSpatialMatching::IsThreePointFormS1Line(const QVector<DxPoint>&vecPointInfo)
{
    DxPoint stMidPoint(0,0,0);
    QVector<double> vecDistance;
    vecDistance.clear();
    double dDis = 0;
    FindMidPoint(vecPointInfo,stMidPoint);
    for ( int i = 0;i<vecPointInfo.size();i++)
    {
        if (vecPointInfo[i] != stMidPoint)
        {
            dDis = TwoPointDistance(vecPointInfo[i],stMidPoint);
            vecDistance.push_back(dDis);
        }              
    }

    if ((fabs((vecDistance[0]/vecDistance[1])- 1)< 0.3))
    {
        return true;
    }

    return false;
}
void DxSpatialMatching::FindMidPoint(const QVector<DxPoint>& vecPointInfo,DxPoint& Point)
{

    DxPoint MidPoint;
    double fTwoPointDistance1 = TwoPointDistance(vecPointInfo[0],vecPointInfo[1]);
    double fTwoPointDistance2 = TwoPointDistance(vecPointInfo[0],vecPointInfo[2]);
    double fTwoPointDistance3 = TwoPointDistance(vecPointInfo[1],vecPointInfo[2]);

    if ((fTwoPointDistance1 > fTwoPointDistance2)&&
        (fTwoPointDistance1 > fTwoPointDistance3))
    {

        MidPoint = vecPointInfo[2];
    }
    else if (fTwoPointDistance2 > fTwoPointDistance3)
    {
        MidPoint = vecPointInfo[1];
    }
    else
    {
        MidPoint = vecPointInfo[0];
    }
    Point = MidPoint;
}
double DxSpatialMatching::TwoPointDistance(const DxPoint& Point1, const DxPoint& Point2)
{

 return sqrt((Point1.X() -Point2.X())*(Point1.X() -Point2.X()) +
        (Point1.Y() -Point2.Y())*(Point1.Y() -Point2.Y()) 
        /*+(Point1.Z() -Point2.Z())*(Point1.Z() -Point2.Z())*/) ;
}
void DxSpatialMatching::FindThreePointCollineation(QVector<DxPoint>&vecPointInfo,
                                                 QVector<DxPoint>&vecCollinearPoint,
                                                 const DxPoint& stCurrentPoint)
{

    QVector<DxPoint> vecPointInfoTemp;
    vecPointInfoTemp.clear();
    bool bCollinear =false;

    for ( int i = 1; i < vecPointInfo.size(); i++)
    {
        for ( int j = i + 1 ; j < vecPointInfo.size();j++)
        {
            vecPointInfoTemp.push_back(stCurrentPoint);
            vecPointInfoTemp.push_back(vecPointInfo[i]);
            vecPointInfoTemp.push_back(vecPointInfo[j]);
            bCollinear = CheckThreePointInOneLine(vecPointInfoTemp);
            if (bCollinear)
            {
				bool bFormS1Line = IsThreePointFormS1Line(vecPointInfoTemp);
				if (bFormS1Line)
				{
					vecCollinearPoint.push_back(stCurrentPoint);
					vecCollinearPoint.push_back(vecPointInfo[i]);
					vecCollinearPoint.push_back(vecPointInfo[j]);
				}
            }
            vecPointInfoTemp.clear();
        }
    }
    return;
}
bool DxSpatialMatching::CheckThreePointInOneLine(QVector<DxPoint>& vecThreePointInfo)
{
    if (vecThreePointInfo.size() != 3)
    {
        return false;
    }
    DxPoint ProjectionPt(0,0,0);
    GetProjectionPtOfPointToLine( 
        vecThreePointInfo[2], vecThreePointInfo[0], vecThreePointInfo[1], ProjectionPt);
    double dDis = ProjectionPt.Sub(vecThreePointInfo[2]).Length();
    if (dDis < 10)
    {
        return true;
    }
    return false;
}
bool DxSpatialMatching::FindPyramidProjectionPoint3D(  QVector<DxPoint>& vec3DPointInfo,QVector<DxPoint>& vecPyramidPoint3D)
{
    if (vec3DPointInfo.size() != 12)
    {
        return false;
    }
    QVector<LineInfo_t> vecLineInfo;
    QVector<DxPoint> vecCrossPoint;
    LineInfo_t stLineInfo;
    LineInfo_t stLine1;
    LineInfo_t stLine2;
    LineInfo_t stLine3;
    LineInfo_t stLine4;
    LineInfo_t stLine5;
    LineInfo_t stLine6;
    vecLineInfo.clear();
    vecCrossPoint.clear();
    for ( int i = 0;i < vec3DPointInfo.size();i = i + 3)
    {
        stLineInfo.PointStart = vec3DPointInfo[i+1];
        stLineInfo.PointEnd = vec3DPointInfo[i+2];
        vecLineInfo.push_back(stLineInfo);
    }
    IntersectionPoint(vecLineInfo,vecCrossPoint);
    //qiu zhong xin
    DxPoint stPyramidPoint3D(0,0,0);
    FindCentroid(vecCrossPoint,stPyramidPoint3D);
    //S1 Cross Point
    vecPyramidPoint3D.push_back(stPyramidPoint3D);
    vecLineInfo.clear();
    vecCrossPoint.clear();
    stLine1.PointStart = vec3DPointInfo[3];
    stLine2.PointStart = vec3DPointInfo[4];
    stLine3.PointStart = vec3DPointInfo[5];
    stLine4.PointStart = vec3DPointInfo[6];
    stLine5.PointStart = vec3DPointInfo[7];
    stLine6.PointStart = vec3DPointInfo[8];
    stLine1.PointEnd = vec3DPointInfo[0];
    stLine2.PointEnd = vec3DPointInfo[1];
    stLine3.PointEnd = vec3DPointInfo[2];
    stLine4.PointEnd = vec3DPointInfo[9];
    stLine5.PointEnd = vec3DPointInfo[10];
    stLine6.PointEnd = vec3DPointInfo[11];
    vecLineInfo.push_back(stLine1);
    vecLineInfo.push_back(stLine2);
    vecLineInfo.push_back(stLine3);
    vecLineInfo.push_back(stLine4);
    vecLineInfo.push_back(stLine5);
    vecLineInfo.push_back(stLine6);
    IntersectionPoint(vecLineInfo,vecCrossPoint);
    FindCentroid(vecCrossPoint,stPyramidPoint3D);
    vecPyramidPoint3D.push_back(stPyramidPoint3D);
    // S3 Cross Point
    vecLineInfo.clear();
    vecCrossPoint.clear();
    stLine1.PointStart = vec3DPointInfo[0];
    stLine2.PointStart = vec3DPointInfo[1];
    stLine3.PointStart = vec3DPointInfo[2];
    stLine4.PointStart = vec3DPointInfo[3];
    stLine5.PointStart = vec3DPointInfo[4];
    stLine6.PointStart = vec3DPointInfo[5];
    stLine1.PointEnd = vec3DPointInfo[9];
    stLine2.PointEnd = vec3DPointInfo[10];
    stLine3.PointEnd = vec3DPointInfo[11];
    stLine4.PointEnd = vec3DPointInfo[6];
    stLine5.PointEnd = vec3DPointInfo[7];
    stLine6.PointEnd = vec3DPointInfo[8];
    vecLineInfo.push_back(stLine1);
    vecLineInfo.push_back(stLine2);
    vecLineInfo.push_back(stLine3);
    vecLineInfo.push_back(stLine4);
    vecLineInfo.push_back(stLine5);
    vecLineInfo.push_back(stLine6);
    IntersectionPoint(vecLineInfo,vecCrossPoint);
    FindCentroid(vecCrossPoint,stPyramidPoint3D);
    vecPyramidPoint3D.push_back(stPyramidPoint3D);
    //S4 Point
    vecLineInfo.clear();
    vecCrossPoint.clear();
    vecLineInfo.clear();
    vecCrossPoint.clear();
    stLine1.PointStart = vec3DPointInfo[0];
    stLine2.PointStart = vec3DPointInfo[1];
    stLine3.PointStart = vec3DPointInfo[2];
    stLine1.PointEnd = vec3DPointInfo[6];
    stLine2.PointEnd = vec3DPointInfo[7];
    stLine3.PointEnd = vec3DPointInfo[8];
    vecLineInfo.push_back(stLine1);
    vecLineInfo.push_back(stLine2);
    vecLineInfo.push_back(stLine3);
    IntersectionPoint(vecLineInfo,vecCrossPoint);
    FindCentroid(vecCrossPoint,stPyramidPoint3D);
    vecPyramidPoint3D.push_back(stPyramidPoint3D);

    //S5 Point
    vecLineInfo.clear();
    vecCrossPoint.clear();
    vecLineInfo.clear();
    vecCrossPoint.clear();
    stLine1.PointStart = vec3DPointInfo[3];
    stLine2.PointStart = vec3DPointInfo[5];
    stLine1.PointEnd = vec3DPointInfo[9];
    stLine2.PointEnd = vec3DPointInfo[11];
    vecLineInfo.push_back(stLine1);
    vecLineInfo.push_back(stLine2);
    IntersectionPoint(vecLineInfo,vecCrossPoint);
    FindCentroid(vecCrossPoint,stPyramidPoint3D);
    vecPyramidPoint3D.push_back(stPyramidPoint3D);
    //S6 Point
    vecLineInfo.clear();
    vecCrossPoint.clear();
    vecLineInfo.clear();
    vecCrossPoint.clear();
    stLine1.PointStart = vec3DPointInfo[5];
    stLine2.PointStart = vec3DPointInfo[8];
    stLine1.PointEnd = vec3DPointInfo[0];
    stLine2.PointEnd = vec3DPointInfo[9];
    vecLineInfo.push_back(stLine1);
    vecLineInfo.push_back(stLine2);
    IntersectionPoint(vecLineInfo,vecCrossPoint);
    FindCentroid(vecCrossPoint,stPyramidPoint3D);
    vecPyramidPoint3D.push_back(stPyramidPoint3D);
    //S7 Point
    vecLineInfo.clear();
    vecCrossPoint.clear();
    vecLineInfo.clear();
    vecCrossPoint.clear();
    stLine1.PointStart = vec3DPointInfo[2];
    stLine2.PointStart = vec3DPointInfo[5];
    stLine1.PointEnd = vec3DPointInfo[9];
    stLine2.PointEnd = vec3DPointInfo[6];
    vecLineInfo.push_back(stLine1);
    vecLineInfo.push_back(stLine2);
    IntersectionPoint(vecLineInfo,vecCrossPoint);
    FindCentroid(vecCrossPoint,stPyramidPoint3D);
    vecPyramidPoint3D.push_back(stPyramidPoint3D);

//     if (vecPyramidPoint3D.size() != 3)
//     {
//         return false;
//     }

    return true;
}

void DxSpatialMatching::IntersectionPoint(const QVector<LineInfo_t>& vecLineInfo,QVector<DxPoint>& vecCrossPoint)
{
    DxPoint stCrossPoint;
    for ( int i = 0; i < vecLineInfo.size();i++)
    {
        for ( int j = i + 1; j < vecLineInfo.size();j++)
        {
            DxPoint stVector1 = vecLineInfo[i].PointStart-vecLineInfo[i].PointEnd;
            DxPoint stVector2 = vecLineInfo[j].PointStart-vecLineInfo[j].PointEnd;
            DxPoint stVectorN = Cross(stVector1,stVector2);
            double dAngle = acos(Dot(stVector1,stVector2)/(stVector1.Length()*stVector2.Length()));
            dAngle = dAngle*180/3.1415926;
            if ((fabs(dAngle) < 0.001)||(fabs(fabs(dAngle)-180)<0.001))
            {
                continue;
            }
            DxPoint ab =(vecLineInfo[i].PointStart - vecLineInfo[j].PointStart);
            double fMinDistance = Dot(stVectorN,ab)/Length(stVectorN);
            DxPoint p1 = vecLineInfo[i].PointStart;
            DxPoint p2 = vecLineInfo[j].PointStart;
            DxPoint stVector3 = vecLineInfo[i].PointEnd-vecLineInfo[i].PointStart;
            DxPoint stVector4 = vecLineInfo[j].PointEnd-vecLineInfo[j].PointStart;
            DxPoint stPoint1;
            DxPoint stPoint2;
            double t1;
            double t2;

            t1 = Dot((Cross(p2-p1,stVector4)),Cross(stVector3,stVector4));
            t2 = Dot((Cross(p2-p1,stVector3)),Cross(stVector3,stVector4));

            double dd = Length((Cross(stVector3,stVector4)));
            t1/=dd*dd;
            t2/=dd*dd;
            stPoint1 = (p1 +(stVector3)*t1);
            stPoint2 = (p2 +(stVector4)*t2);

            stCrossPoint = (stPoint1+stPoint2 )/2;    
            vecCrossPoint.push_back(stCrossPoint);
        }
    }
    return;
}
DxPoint DxSpatialMatching::Cross(DxPoint a,DxPoint b)
{
    DxPoint stVectorCross;
    stVectorCross.SetX(a.Y()*b.Z()-a.Z()*b.Y());
    stVectorCross.SetY(a.Z()*b.X()-a.X()*b.Z());
    stVectorCross.SetZ(a.X()*b.Y()-a.Y()*b.X());

    return stVectorCross;
}

void DxSpatialMatching::FindCentroid( const QVector<DxPoint>& vecCrossPoint,DxPoint& stCentroidPoint)
{
    unsigned int nTotalPointNum = vecCrossPoint.size();
    stCentroidPoint.SetX(0);
    stCentroidPoint.SetY(0);
    stCentroidPoint.SetZ(0);
    for ( int i = 0 ; i < vecCrossPoint.size();i++)
    {
        stCentroidPoint = stCentroidPoint.Add(vecCrossPoint[i]);
    }
    stCentroidPoint = stCentroidPoint/nTotalPointNum;

    return ;
}
QVector<double>& DxSpatialMatching::GetxSpotMatrix()
{
    return m_vecMartix;
}
QVector<double>& DxSpatialMatching::GetxSpotMatrixByHand()
{
	return m_vecMartix;
}
QMap<int,DxPoint>& DxSpatialMatching::GetxSpotPointMap()
{

//     m_XspotPt.clear();
//     QVector<DxPoint> vecPointInfo;
//     vecPointInfo.clear();
//     for (int i = 0 ;i < m_vecSuccessPoint.size();i++)
//     {
//         for (int j = 0 ; j < m_vec2DPushPoint.size();j++)
//         {
//             if ((DxMath::DoubleEqual(m_vecSuccessPoint[i].X(), m_vec2DPushPoint[j].X()))&&
//                 (DxMath::DoubleEqual(m_vecSuccessPoint[i].Y(), m_vec2DPushPoint[j].Y())))
//             {
//                 vecPointInfo.push_back(m_vec2DPushPoint[j]);
//                 m_mapXspotOrgOrder.remove(j);
//             }
//         }
//     }
//     if (vecPointInfo.size() == m_vecSuccessPoint.size())
//     {
//         m_vecSuccessPoint = vecPointInfo;
//     }
//     for (int i = 0 ;i < m_vecSuccessCompare.size();i++)
//     {
//         m_XspotPt.insert(m_vecSuccessCompare[i],m_vecSuccessPoint[i]);
//     }
//     if (!m_bAllGroupDivid)
//     {
//         QMap<int, DxPoint>::iterator it = m_mapXspotOrgOrder.begin();
//         for ( ; it != m_mapXspotOrgOrder.end(); ++it ) 
//         {
//             for (int k = 0 ; k < 12;k++)
//             {
//                 if (m_XspotPt.find(k)== m_XspotPt.end())
//                 {
//                     m_XspotPt.insert(k,it.value());
//                     break;
//                 }
//             }
//         }
//     }
    if (m_XspotPtRightCompare.size() < 6)
    {
        return m_XspotPt;
    }
    return m_XspotPtRightCompare;
}

void DxSpatialMatching::GetxSpotPointGroupInfo(QVector<QVector<DxPoint>>& vecGroupPoint)
{
    vecGroupPoint = m_vecPointGroup;
}

bool DxSpatialMatching::FindPymaidPointS2ByOneStandardLine( 
    QVector<DxPoint>& vecRankedPoint, QVector<DxPoint>& vecCrossInfo, DxPoint& stPyramidPointS2)
{ 
    QVector<DxPoint> vecLeftPoint;
    vecLeftPoint.clear();
    for (int i = 3; i < vecRankedPoint.size();i++)
    {
        vecLeftPoint.push_back(vecRankedPoint[i]);
    }

    int nMaxLineNum = 0;
    double dMinDisVariance = 1000;
    for ( int i = 0; i < vecCrossInfo.size();i++)
    {
        int nLineNum = 0;
        double dDisVariance = 0.0;
        QVector<DxPoint> vecGroupPoint;
        vecGroupPoint.clear();
        DivideGroupByS2( vecCrossInfo[i], vecLeftPoint, vecGroupPoint);
        nLineNum = vecGroupPoint.size()/2;
        DxPoint ProjectionPt(0,0,0);
        for (int j = 0; j < vecGroupPoint.size(); j+=2)
        {
            GetProjectionPtOfPointToLine(vecGroupPoint[j+1], vecCrossInfo[i], vecGroupPoint[j], ProjectionPt);
            double dDis = ProjectionPt.Sub(vecGroupPoint[j+1]).Length();
            dDisVariance += dDis*dDis;
        }

        if (nLineNum > 1 && (nLineNum > nMaxLineNum || (nLineNum == nMaxLineNum && dDisVariance < dMinDisVariance)))
        {
            stPyramidPointS2 = vecCrossInfo[i];
            nMaxLineNum = nLineNum;
            dMinDisVariance = dDisVariance;
        }
    }

    if (nMaxLineNum <= 1)
    {
        return false;
    }

    return true;
}

void DxSpatialMatching::GetProjectionPtOfPointToLine( 
    DxPoint Point, DxPoint LinePt1, DxPoint LinePt2, DxPoint& ProjectionPt)
{
    DxPoint LineDir = LinePt1.Sub(LinePt2).Normalize();
    double d = (Point.Dot(LineDir) - LinePt1.Dot(LineDir))/(LineDir.Dot(LineDir));
    ProjectionPt = LinePt1.Add(LineDir.Multiply(d));
}

void DxSpatialMatching::CheckCrossPtIsS2(
    DxPoint crosspt, 
    QVector<DxPoint> vecLeftPoint, 
    QVector<DxPoint>& vecGroup, 
    int& nLineNum, 
    double &dDisVariance)
{
    if (vecLeftPoint.size() <= 1)
    {
        return ;
    }

    QVector<DxPoint> vecLinePt;
    vecLinePt.clear();
    vecLinePt.push_back(vecLeftPoint[0]);
    for (int j = 1; j < vecLeftPoint.size(); j++)
    {
        DxPoint ProjectionPt(0,0,0);
        GetProjectionPtOfPointToLine( 
            vecLeftPoint[j], crosspt, vecLeftPoint[0], ProjectionPt);
        double dDis = ProjectionPt.Sub(vecLeftPoint[j]).Length();
        if (dDis < 10)
        {
            vecLinePt.push_back(vecLeftPoint[j]);
            vecGroup.push_back(vecLinePt[0]);
            vecGroup.push_back(vecLinePt[1]);
            nLineNum++;
            dDisVariance += dDis*dDis;
            break;
        }
    }

    //从vecLeftPoint中除去vecLeftPoint里有的点
    QVector<DxPoint> vecAfterRemoveLeftPt;
    vecAfterRemoveLeftPt.clear();
    for (int m = 0; m < vecLeftPoint.size(); m++)
    {
        bool same = false;
        for (int k = 0; k < vecLinePt.size(); k++)
        {
            if (vecLinePt[k] == vecLeftPoint[m])
            {
                same = true;
                break;
            }
        }
        if (!same)
        {
            vecAfterRemoveLeftPt.push_back(vecLeftPoint[m]);
        }
    }

    CheckCrossPtIsS2(crosspt, vecAfterRemoveLeftPt, vecGroup, nLineNum, dDisVariance);
}

void DxSpatialMatching::DivideGroupByS2(
    DxPoint ptS2, QVector<DxPoint> vecLeftPoint, QVector<DxPoint>& vecGroupPoint)
{
    if (vecLeftPoint.size() <= 1)
    {
        return ;
    }

    QVector<DxPoint> vecLinePt;
    vecLinePt.clear();
    vecLinePt.push_back(vecLeftPoint[0]);
    for (int j = 1; j < vecLeftPoint.size(); j++)
    {
        DxPoint ProjectionPt(0,0,0);
        GetProjectionPtOfPointToLine( 
            vecLeftPoint[j], ptS2, vecLeftPoint[0], ProjectionPt);
        double dDis = ProjectionPt.Sub(vecLeftPoint[j]).Length();
        if (dDis < 10)
        {
            vecLinePt.push_back(vecLeftPoint[j]);
            if (TwoPointDistance(vecLeftPoint[0],ptS2) >TwoPointDistance(vecLeftPoint[j],ptS2) )
            {
                vecGroupPoint.push_back(vecLeftPoint[j]);
                vecGroupPoint.push_back(vecLeftPoint[0]);
            }
            else
            {
                vecGroupPoint.push_back(vecLeftPoint[0]);
                vecGroupPoint.push_back(vecLeftPoint[j]);
            }
            break;
        }
    }

    //从vecLeftPoint中除去vecLeftPoint里有的点
    QVector<DxPoint> vecAfterRemoveLeftPt;
    vecAfterRemoveLeftPt.clear();
    for (int m = 0; m < vecLeftPoint.size(); m++)
    {
        bool same = false;
        for (int k = 0; k < vecLinePt.size(); k++)
        {
            if (vecLinePt[k] == vecLeftPoint[m])
            {
                same = true;
                break;
            }
        }
        if (!same)
        {
            vecAfterRemoveLeftPt.push_back(vecLeftPoint[m]);
        }
    }

    DivideGroupByS2(ptS2, vecAfterRemoveLeftPt, vecGroupPoint);
}

bool DxSpatialMatching::FindTheRightCompare(QVector<DxPoint> vecPyramidPoint3D,QVector<DxPoint> vecPoint3D,QVector<QVector<DxPoint>> vecGroupPoint,QVector<DxPoint> vecAllPt2D,int nCollearTime)
{
    QVector<int> vecCompareNum;
    vecCompareNum.clear();
    QVector<DxPoint> vecRay2DPt;
    vecRay2DPt.clear();

    QVector<DxPoint> vecCalMatrixPoint;
    vecCalMatrixPoint.clear();
    for ( int i = 0; i < vecGroupPoint.size(); i++)
    {
        for (int j = 0 ; j < vecGroupPoint[i].size();j++)
        {
            vecCalMatrixPoint.push_back(vecGroupPoint[i][j]);
        }
    }

    QVector<int> vecLeftGroupIndex;
    vecLeftGroupIndex.clear();
    for (int i = 0; i < 4; i++)
    {
        vecLeftGroupIndex.push_back(i);
    }

    QVector<int> vecCurrentCompareNum;
    vecCurrentCompareNum.clear();
    QVector<QVector<int>> vecAllCompareNum;
    vecAllCompareNum.clear();

    TryAllSituationOfRank(
        nCollearTime, 
        vecGroupPoint.size(),
        vecLeftGroupIndex,
        vecCurrentCompareNum,
        vecAllCompareNum);

//     double dpixVal = 0.;
//     for (int i = 0; i< vecAllPt2D.size();i++)
//     {
//         dpixVal += GetAveragePixelValueInRange(nPixel,vecAllPt2D[i].X(),vecAllPt2D[i].Y(),3);
//     }
//     double dAvrPixelofAllpt = dpixVal/vecAllPt2D.size();

    for (int i = 0; i < vecAllCompareNum.size(); i++)
    {
        DxPoint stRayPt(0,0,0);
        QVector<DxPoint> vecRay2DPT;
        QMap<int, DxPoint> mapXspotRank;
        bool bBlackPt = true;
        mapXspotRank.clear();
        vecRay2DPT.clear();
        CalculateTheMatrix(vecPoint3D, vecCalMatrixPoint, vecAllCompareNum[i]);
        double dVariance = 0;
        for (int k = 0 ; k< vecPoint3D.size();k++)
        {
            Get2DCoordinatesBy3DPoint(m_vecMartix,vecPoint3D[k],stRayPt);
// 			double dpixVal1InSameGroup, dpixVal2InSameGroup;
//          double dpixValCurpt = GetAveragePixelValueInRange(nPixel,stRayPt.X(),stRayPt.Y(),3);

// 			if (k % 3 == 0)
// 			{
// 				DxPoint stRayPt1(0,0,0);
// 				Get2DCoordinatesBy3DPoint(m_vecMartix,vecPoint3D[k+1],stRayPt1);
// 				dpixVal1InSameGroup = GetAveragePixelValueInRange(nPixel,stRayPt.X(),stRayPt.Y(),3);
// 
// 				DxPoint stRayPt2(0,0,0);
// 				Get2DCoordinatesBy3DPoint(m_vecMartix,vecPoint3D[k+2],stRayPt2);
// 				dpixVal2InSameGroup = GetAveragePixelValueInRange(nPixel,stRayPt.X(),stRayPt.Y(),3);
// 			}
// 			else if (k % 3 == 1)
// 			{
// 				DxPoint stRayPt1(0,0,0);
// 				Get2DCoordinatesBy3DPoint(m_vecMartix,vecPoint3D[k-1],stRayPt1);
// 				dpixVal1InSameGroup = GetAveragePixelValueInRange(nPixel,stRayPt.X(),stRayPt.Y(),3);
// 
// 				DxPoint stRayPt2(0,0,0);
// 				Get2DCoordinatesBy3DPoint(m_vecMartix,vecPoint3D[k+2],stRayPt2);
// 				dpixVal2InSameGroup = GetAveragePixelValueInRange(nPixel,stRayPt.X(),stRayPt.Y(),3);
// 			}
// 			else if (k % 3 == 2)
// 			{
// 				DxPoint stRayPt1(0,0,0);
// 				Get2DCoordinatesBy3DPoint(m_vecMartix,vecPoint3D[k-2],stRayPt1);
// 				dpixVal1InSameGroup = GetAveragePixelValueInRange(nPixel,stRayPt.X(),stRayPt.Y(),3);
// 
// 				DxPoint stRayPt2(0,0,0);
// 				Get2DCoordinatesBy3DPoint(m_vecMartix,vecPoint3D[k-1],stRayPt2);
// 				dpixVal2InSameGroup = GetAveragePixelValueInRange(nPixel,stRayPt.X(),stRayPt.Y(),3);
// 			}
// 			if (((dpixVal1InSameGroup+dpixVal2InSameGroup)/2 - dpixValCurpt)/nMaxPixelValue > 0.2)
//             {
//                 bBlackPt =false;
//                 break;
//             }
			
//             if ((dAvrPixelofAllpt - dpixValCurpt)/nMaxPixelValue > 0.2)
//             {
//                 bBlackPt =false;
//                 break;
//             }
            vecRay2DPT.push_back(stRayPt);
            double dDis = FindExistPointInfoInVector(stRayPt,vecAllPt2D,mapXspotRank,k);
            dVariance+= dDis*dDis;
        }
//         if (!bBlackPt)
//         {
//             continue;
//         }
        QVector<DxPoint> vecRayPyramidPt;
        vecRayPyramidPt.clear();
        DxPoint stRayPtS1(0,0,0);
        DxPoint stRayPtS2(0,0,0);
        DxPoint stRayPtS3(0,0,0);
        DxPoint stRayPtS4(0,0,0);
        DxPoint stRayPtS5(0,0,0);
        DxPoint stRayPtS6(0,0,0);
        DxPoint stRayPtS7(0,0,0);
        Get2DCoordinatesBy3DPoint(m_vecMartix,vecPyramidPoint3D[0],stRayPtS2);
        Get2DCoordinatesBy3DPoint(m_vecMartix,vecPyramidPoint3D[1],stRayPtS1);
        Get2DCoordinatesBy3DPoint(m_vecMartix,vecPyramidPoint3D[2],stRayPtS3);
        Get2DCoordinatesBy3DPoint(m_vecMartix,vecPyramidPoint3D[3],stRayPtS4);
        Get2DCoordinatesBy3DPoint(m_vecMartix,vecPyramidPoint3D[4],stRayPtS5);
        Get2DCoordinatesBy3DPoint(m_vecMartix,vecPyramidPoint3D[5],stRayPtS6);
        Get2DCoordinatesBy3DPoint(m_vecMartix,vecPyramidPoint3D[6],stRayPtS7);
        vecRayPyramidPt.push_back(stRayPtS2);
        vecRayPyramidPt.push_back(stRayPtS1);
        vecRayPyramidPt.push_back(stRayPtS3);
        QVector<LineInfo_t> vecLineInfo;
        vecLineInfo.clear();
        QVector<DxPoint> vecCrossPoint;
        vecCrossPoint.clear();

        LineInfo_t stLineInfo;
        stLineInfo.PointStart =vecRay2DPT[0];
        stLineInfo.PointEnd =vecRay2DPT[6];
        vecLineInfo.push_back(stLineInfo);
        stLineInfo.PointStart =vecRay2DPT[2];
        stLineInfo.PointEnd =vecRay2DPT[8];
        vecLineInfo.push_back(stLineInfo);
        IntersectionPoint(vecLineInfo,vecCrossPoint);
        double dd = stRayPtS4.Sub(stRayPtS1).Normalize().Dot(stRayPtS4.Sub(stRayPtS3).Normalize());
        double d1 = stRayPtS4.Sub(stRayPtS1).Length();
        double d2 = stRayPtS4.Sub(stRayPtS3).Length();

        //S4
        vecLineInfo.clear();
        vecCrossPoint.clear();
        stLineInfo.PointStart =vecRay2DPT[0];
        stLineInfo.PointEnd =vecRay2DPT[6];
        vecLineInfo.push_back(stLineInfo);
        stLineInfo.PointStart =vecRay2DPT[2];
        stLineInfo.PointEnd =vecRay2DPT[8];
        vecLineInfo.push_back(stLineInfo);
        IntersectionPoint(vecLineInfo,vecCrossPoint);
        DxPoint stS4(vecCrossPoint[0].X(),0,0);
        stS4 = vecCrossPoint[0];
        double aa = stS4.Sub(stRayPtS1).Normalize().Dot(stS4.Sub(stRayPtS3).Normalize());
        double a1 = stS4.Sub(stRayPtS1).Length();
        double a2 = stS4.Sub(stRayPtS3).Length();

        //S5
        vecLineInfo.clear();
        vecCrossPoint.clear();
        stLineInfo.PointStart =vecRay2DPT[3];
        stLineInfo.PointEnd =vecRay2DPT[9];
        vecLineInfo.push_back(stLineInfo);
        stLineInfo.PointStart =vecRay2DPT[5];
        stLineInfo.PointEnd =vecRay2DPT[11];
        vecLineInfo.push_back(stLineInfo);
        IntersectionPoint(vecLineInfo,vecCrossPoint);
        DxPoint stS5(0,0,0);
        stS5 = vecCrossPoint[0];

        //S6
        vecLineInfo.clear();
        vecCrossPoint.clear();
        stLineInfo.PointStart =vecRay2DPT[5];
        stLineInfo.PointEnd =vecRay2DPT[0];
        vecLineInfo.push_back(stLineInfo);
        stLineInfo.PointStart =vecRay2DPT[8];
        stLineInfo.PointEnd =vecRay2DPT[9];
        vecLineInfo.push_back(stLineInfo);
        IntersectionPoint(vecLineInfo,vecCrossPoint);
        DxPoint stS6(0,0,0);
        stS6 = vecCrossPoint[0];

        //S7
        vecLineInfo.clear();
        vecCrossPoint.clear();
        stLineInfo.PointStart =vecRay2DPT[2];
        stLineInfo.PointEnd =vecRay2DPT[9];
        vecLineInfo.push_back(stLineInfo);
        stLineInfo.PointStart =vecRay2DPT[5];
        stLineInfo.PointEnd =vecRay2DPT[6];
        vecLineInfo.push_back(stLineInfo);
        IntersectionPoint(vecLineInfo,vecCrossPoint);
        DxPoint stS7(0,0,0);
        stS7 = vecCrossPoint[0];


        if (mapXspotRank.size() == vecAllPt2D.size())
        {
            int i = 0;
        }
        //if (!CheckTheLightPointInXspot(vecRay2DPT,vecRayPyramidPt))
        //{
        //    continue;
        //}

        if ( mapXspotRank.size() > m_XspotPtRightCompare.size() || 
            (mapXspotRank.size() == m_XspotPtRightCompare.size() && m_dDisVariance > dVariance))
        {
            if ((stRayPtS1.Sub(vecRay2DPT[0]).Length() < stRayPtS1.Sub(vecRay2DPT[3]).Length()&&
                (stRayPtS1.Sub(vecRay2DPT[0]).Normalize().Dot(stRayPtS1.Sub(vecRay2DPT[3]).Normalize())) > 0.99) && 
                (stRayPtS1.Sub(vecRay2DPT[11]).Length() < stRayPtS1.Sub(vecRay2DPT[8]).Length()&&
                (stRayPtS1.Sub(vecRay2DPT[11]).Normalize().Dot(stRayPtS1.Sub(vecRay2DPT[8]).Normalize())) > 0.99) &&
                (stRayPtS3.Sub(vecRay2DPT[8]).Length() < stRayPtS3.Sub(vecRay2DPT[5]).Length()&&
                (stRayPtS3.Sub(vecRay2DPT[8]).Normalize().Dot(stRayPtS3.Sub(vecRay2DPT[5]).Normalize())) > 0.99) &&
                (stRayPtS3.Sub(vecRay2DPT[9]).Length() < stRayPtS3.Sub(vecRay2DPT[0]).Length()&&
                (stRayPtS3.Sub(vecRay2DPT[9]).Normalize().Dot(stRayPtS3.Sub(vecRay2DPT[0]).Normalize())) > 0.99) && 
                (stRayPtS1.Sub(stRayPtS5).Normalize().Dot(stRayPtS5.Sub(stRayPtS3).Normalize())  > 0.99  &&
                (stRayPtS1.Sub(stRayPtS3).Length() > stRayPtS3.Sub(stRayPtS5).Length()))&&
                (stRayPtS1.Sub(stRayPtS6).Normalize().Dot(stRayPtS6.Sub(stRayPtS2).Normalize()) > 0.99  &&
                (stRayPtS1.Sub(stRayPtS2).Length() > stRayPtS2.Sub(stRayPtS6).Length()))&&
                (stRayPtS2.Sub(stRayPtS7).Normalize().Dot(stRayPtS7.Sub(stRayPtS3).Normalize()) > 0.99  &&
                (stRayPtS2.Sub(stRayPtS3).Length() > stRayPtS3.Sub(stRayPtS7).Length()))/*&&
                (stRayPtS4.Sub(stRayPtS1).Length() > stRayPtS4.Sub(stRayPtS3).Length() && 
                (stRayPtS4.Sub(stRayPtS1).Normalize().Dot(stRayPtS4.Sub(stRayPtS3).Normalize())> 0.99))*/)

//                 (stRayPtS4.Sub(vecRay2DPT[6]).Length() < stRayPtS4.Sub(vecRay2DPT[0]).Length() &&
//                 (stRayPtS4.Sub(vecRay2DPT[6]).Normalize().Dot(stRayPtS4.Sub(vecRay2DPT[0]).Normalize())) > 0.99) && 
//                 (stRayPtS4.Sub(stRayPtS1).Length() > stRayPtS4.Sub(stRayPtS3).Length() && 
//                 (stRayPtS4.Sub(stRayPtS1).Normalize().Dot(stRayPtS4.Sub(stRayPtS3).Normalize())> 0.99)))
            {
                m_XspotPtRightCompare = mapXspotRank;
                m_dDisVariance = dVariance;
            }
        }
    }
    if (m_XspotPtRightCompare.size() <6)
    {
        return false;
    }
    QVector<DxPoint> vecComparePt;
    vecComparePt.clear();
    vecCompareNum.clear();
    QMap<int,DxPoint>::iterator it = m_XspotPtRightCompare.begin();
    for ( ; it != m_XspotPtRightCompare.end();it++ )
    {
        vecCompareNum.push_back(it.key());
        vecComparePt.push_back(it.value());
    }
    CalculateTheMatrix(vecPoint3D,vecComparePt,vecCompareNum);
    return true;
}

double DxSpatialMatching::FindExistPointInfoInVector(DxPoint stPointInfo,const QVector<DxPoint>& vecPointInfo,QMap<int,DxPoint>&mapXspotRank,int nRankNum)
{
    for ( int i = 0;i<vecPointInfo.size();i++)
    {
        double dDis = TwoPointDistance(stPointInfo,vecPointInfo[i]);
        if ( dDis < 10)
        { 
            mapXspotRank.insert(nRankNum,vecPointInfo[i]);
            return dDis;
        }
    }  
    return 0;
}
//找到所有可能的对应情况
void DxSpatialMatching::TryAllSituationOfRank(
    int nCollearTime, 
    int nTotalGroupNum,
    QVector<int> vecLeftGroupIndex,
    QVector<int> vecCurrentCompareNum,
    QVector<QVector<int>>& vecAllCompareNum)
{
    for (int i = 0; i < vecLeftGroupIndex.size(); i++)
    {
        QVector<int> vecTmpLeftGroupIndex;
        vecTmpLeftGroupIndex.clear();
        int nSelectGroupIndex = -1;
        for (int j = 0; j < vecLeftGroupIndex.size();j++)
        {
            if(i != j)
            {
                vecTmpLeftGroupIndex.push_back(vecLeftGroupIndex[j]);
            }
            else
            {
                nSelectGroupIndex = vecLeftGroupIndex[j];
            }
        }

        if ( 4 - vecLeftGroupIndex.size() < nCollearTime)
        {
            QVector<int> vecTmpCurrentCompareNum = vecCurrentCompareNum;
            vecTmpCurrentCompareNum.push_back(3*vecLeftGroupIndex[i]);
            vecTmpCurrentCompareNum.push_back(3*vecLeftGroupIndex[i]+1);
            vecTmpCurrentCompareNum.push_back(3*vecLeftGroupIndex[i]+2);

            if (vecTmpLeftGroupIndex.size() == 4 - nTotalGroupNum)
            {
                vecAllCompareNum.push_back(vecTmpCurrentCompareNum);
            }
            else
            {
                TryAllSituationOfRank(
                    nCollearTime, nTotalGroupNum, vecTmpLeftGroupIndex, vecTmpCurrentCompareNum, vecAllCompareNum);
            }
        }
        else
        {
            for ( int j = 0; j < 3; j++)
            {
                QVector<int> vecTmpCurrentCompareNum = vecCurrentCompareNum;
                if (j%3 != 0)
                {
                   vecTmpCurrentCompareNum.push_back(3*nSelectGroupIndex);
                }
                if (j%3 != 1)
                {
                    vecTmpCurrentCompareNum.push_back(3*nSelectGroupIndex+1);
                }
                if (j%3 != 2)
                {
                    vecTmpCurrentCompareNum.push_back(3*nSelectGroupIndex+2);
                }

                if (vecTmpLeftGroupIndex.size() == 4 - nTotalGroupNum)
                {
                    vecAllCompareNum.push_back(vecTmpCurrentCompareNum);
                }
                else
                {
                    TryAllSituationOfRank(
                        nCollearTime, nTotalGroupNum, vecTmpLeftGroupIndex, vecTmpCurrentCompareNum, vecAllCompareNum);
                }
            }
        }
    }
}

//bool DxSpatialMatching::CheckTheLightPointInXspot( QVector<DxPoint>vecGroupPoint, QVector<DxPoint> vecRaypymidPt)
//{
//    double dMaxDistance = 0;
//    double dDistanceTmp = 0;
//    double dCerterToS2Dis = 0;
//    DxPoint stLightPoint;
//    DxPoint stCentriodPoint;
//    DxPoint stLightPointInXport;
//    FindCentroid(vecGroupPoint,stCentriodPoint);
//    QVector<DxPoint> vecpymidPt2D;
//    FindPyramidProjectionPoint3D(vecGroupPoint,vecpymidPt2D);
//    for (int i = 0; i < 3; i++)
//    {
////         DxPoint stPt;
////         stPt.SetX(vecRaypymidPt[i].X() +500);
////         stPt.SetY(vecRaypymidPt[i].Y() +500);
////         double dDis1 = TwoPointDistance(stPt,vecRaypymidPt[i]);
////         double dDis2 = TwoPointDistance(stPt,vecpymidPt2D[i]);
////         if (fabs(dDis1/dDis2 -1) >0.1)
////         {
////             return false;
////         }
//        DxPoint stVector1 = vecRaypymidPt[i] - vecGroupPoint[8];
//        DxPoint stVector2 = vecpymidPt2D[i]- vecGroupPoint[8];
//        double dAngle = acos(Dot(stVector1,stVector2)/(stVector1.Length()*stVector2.Length()));
//        dAngle = dAngle*180/3.1415926;
//        if ((fabs(dAngle) > 5))
//        {
//            return false;
//        }
//
//    }
//    DxCoordinateTranslator::Get3DCrossPoint(m_vecMartix,vecGroupPoint.first(),DxPoint2D(0,0),m_vecMartix,vecGroupPoint.last(),DxPoint2D(0,0),stLightPoint);
//    m_matrixToXspot.MultiplyPoint( stLightPoint, stLightPointInXport );
//    for ( int i = 0; i< vecGroupPoint.size();i++ )
//    {
//        dDistanceTmp = TwoPointDistance(stCentriodPoint,vecGroupPoint[i]);
//
//        if (dDistanceTmp > dMaxDistance)
//        {
//            dMaxDistance = dDistanceTmp;
//        }
//    }
//    dCerterToS2Dis = TwoPointDistance(stCentriodPoint,vecRaypymidPt[0]);
//    if (dMaxDistance > dCerterToS2Dis)
//    {
//        // 交点S2在中间
//        DxPoint stVec1 = vecGroupPoint[0].Sub(stCentriodPoint); 
//        DxPoint stVec2 = vecGroupPoint[3].Sub(stCentriodPoint);
//
//        if (fabs(stLightPointInXport.Length()) > 1500 || fabs(stLightPointInXport.Length()) < 100)
//        {
//            return false;
//        }
//
////         if (stLightPointInXport.Z() < 0)
////         {
////             if (stVec1.Cross(stVec2).Z() < 0)
////             {
////                 return false;
////             }
////             
////         }
////         else
////         {
////             if (stVec1.Cross(stVec2).Z() > 0)
////             {
////                 return false;
////             }
//// 
////         }
//    }
//    else
//    {
//        //交点S2在外面
////         if ((vecGroupPoint[3].Sub(vecGroupPoint[6]).Length() >vecGroupPoint[3].Sub(vecGroupPoint[0]).Length())||
////             (vecGroupPoint[4].Sub(vecGroupPoint[7]).Length() >vecGroupPoint[4].Sub(vecGroupPoint[1]).Length())||
////             (vecGroupPoint[5].Sub(vecGroupPoint[8]).Length() >vecGroupPoint[5].Sub(vecGroupPoint[2]).Length()))
//        if (TwoPointDistance(stCentriodPoint,vecRaypymidPt[1]) <TwoPointDistance(stCentriodPoint,vecRaypymidPt[2]) )
//        {
//            return false;
//        }
//    }
//
//    return true;
//}

void DxSpatialMatching::SetDicomSize(int nWight , int nHeight)
{
   if (nWight < 0 || nHeight < 0)
   {
       return;
   }
   m_nDicomWight = nWight;
   m_nDicomHeight = nHeight;
}

bool DxSpatialMatching::Get2DCoordinatesBy3DPoint(const QVector<double>&vecMartix, const DxPoint& stPoint3DInfo,
	DxPoint& stPoint2DInfo)
{


	if (vecMartix.size() != 11)
	{
		return false;
	}
	double dX = (vecMartix[0] * stPoint3DInfo.X() + vecMartix[1] * stPoint3DInfo.Y() + vecMartix[2] * stPoint3DInfo.Z() + vecMartix[3]) /
		(vecMartix[4] * stPoint3DInfo.X() + vecMartix[5] * stPoint3DInfo.Y() + vecMartix[6] * stPoint3DInfo.Z() + 1);


	double dY = (vecMartix[7] * stPoint3DInfo.X() + vecMartix[8] * stPoint3DInfo.Y() + vecMartix[9] * stPoint3DInfo.Z() + vecMartix[10]) /
		(vecMartix[4] * stPoint3DInfo.X() + vecMartix[5] * stPoint3DInfo.Y() + vecMartix[6] * stPoint3DInfo.Z() + 1);
	double dZ = 0;
	stPoint2DInfo.SetPoint(dX, dY, dZ);
	return true;
}