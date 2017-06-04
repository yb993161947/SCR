
#include "./carm/DxCoordinateTranslator.h"
#include <Eigen/Eigen>
#include <Eigen/LU>
#include <Eigen/StdVector>

using namespace Eigen;

DxCoordinateTranslator::DxCoordinateTranslator()
{
  
}

DxCoordinateTranslator::~DxCoordinateTranslator()
{

}


DxFunctionResult DxCoordinateTranslator::TransformPointFromMarkerAToMarkerB( 
														  DxMarkerMatrixContainerModelPtr& pMarkerMatrixContainerModel, 
														  const QString& qsMarkerAName, const DxPoint& ptAPoint, 
														  const QString& qsMarkerBName, DxPoint& ptBPoint )
{
	DxLOG_FUNC_TRACE();

	Q_ASSERT(!pMarkerMatrixContainerModel.isNull());

	
	DxMatrix4x4 markerAMatrix = pMarkerMatrixContainerModel->GetMarkerMatrix(qsMarkerAName);
	DxMatrix4x4 markerBMatrix = pMarkerMatrixContainerModel->GetMarkerMatrix(qsMarkerBName);

	markerBMatrix.Invert( markerBMatrix );
	markerBMatrix = markerBMatrix.LeftMultiply4x4( markerAMatrix );
	markerBMatrix.MultiplyPoint( ptAPoint, ptBPoint );
	return DxFunctionResult::ReturnOK();
}

DxFunctionResult DxCoordinateTranslator::GetMatrixFromMarkerAToMarkerB( DxMarkerMatrixContainerModelPtr& pMarkerMatrixContainerModel, 
                                                      const QString& qsMarkerAName, const QString& qsMarkerBName, DxMatrix4x4& MarkerAToMarkerB )
{


    Q_ASSERT(!pMarkerMatrixContainerModel.isNull());

    DxMatrix4x4 markerAMatrix = pMarkerMatrixContainerModel->GetMarkerMatrix(qsMarkerAName);
    DxMatrix4x4 markerBMatrix = pMarkerMatrixContainerModel->GetMarkerMatrix(qsMarkerBName);

    markerBMatrix.Invert( markerBMatrix );
    markerBMatrix = markerBMatrix.LeftMultiply4x4( markerAMatrix );
    MarkerAToMarkerB = markerBMatrix;
    return DxFunctionResult::ReturnOK();
}
DxFunctionResult DxCoordinateTranslator::Get2DCoordinatesBy3DPoint( const QVector<double>&vecMartix, const DxPoint& stPoint3DInfo,
													   DxPoint& stPoint2DInfo,const DxPoint2D& stImageOffset )
{
	DxLOG_FUNC_TRACE();

	if (vecMartix.size() != 11)
	{
		return DxFunctionResult::ReturnError() ;
	}
	double dX = (vecMartix[0]*stPoint3DInfo.X() + vecMartix[1]*stPoint3DInfo.Y() + vecMartix[2]*stPoint3DInfo.Z() + vecMartix[3])/
		(vecMartix[4]*stPoint3DInfo.X() + vecMartix[5]*stPoint3DInfo.Y() + vecMartix[6]*stPoint3DInfo.Z() + 1);


	double dY = (vecMartix[7]*stPoint3DInfo.X() + vecMartix[8]*stPoint3DInfo.Y() + vecMartix[9]*stPoint3DInfo.Z() + vecMartix[10])/
		(vecMartix[4]*stPoint3DInfo.X() + vecMartix[5]*stPoint3DInfo.Y() + vecMartix[6]*stPoint3DInfo.Z() + 1);
	double dZ = 0;
	stPoint2DInfo.SetPoint( dX+stImageOffset.X(), dY+stImageOffset.Y(), dZ );
	return DxFunctionResult::ReturnOK();
}

DxFunctionResult DxCoordinateTranslator::Get3DCoordinatesBy2DPoint( const QVector<double>&vecMartix ,const DxPoint& stPoint2DInfo
                                                                   ,QVector<DxPoint>& vecCrossPointInfo, const DxPoint2D& stImageOffset )
{
	DxLOG_FUNC_TRACE();

	if (vecMartix.size() != 11)
	{
		return DxFunctionResult::ReturnError() ;
	}

	DxPoint stCrossPointz;
	DxPoint stCrossPointx;
	DxPoint stCrossPointy;
	QVector<double>vecLineParameter;
	vecLineParameter.clear();
    DxPoint stPoint2DInfoTmp;
    stPoint2DInfoTmp.SetX(stPoint2DInfo.X()-stImageOffset.X());
    stPoint2DInfoTmp.SetY(stPoint2DInfo.Y()-stImageOffset.Y());
    stPoint2DInfoTmp.SetZ(0.0);
	Get3DLineParameter(vecMartix,stPoint2DInfoTmp,vecLineParameter);

	stCrossPointz.SetX((vecLineParameter[7]*vecLineParameter[1]-vecLineParameter[3]*vecLineParameter[5])/
		(vecLineParameter[0]*vecLineParameter[5]-vecLineParameter[4]*vecLineParameter[1]));
	stCrossPointz.SetY(-(vecLineParameter[0]*stCrossPointz.X() + vecLineParameter[3])/vecLineParameter[1]);
	stCrossPointz.SetZ(0.0);

	stCrossPointy.SetX( (vecLineParameter[7]*vecLineParameter[2]-vecLineParameter[3]*vecLineParameter[6])/
		(vecLineParameter[0]*vecLineParameter[6]- vecLineParameter[4]*vecLineParameter[2]));
	stCrossPointy.SetY(0.0);
	stCrossPointy.SetZ(-(vecLineParameter[0]*stCrossPointy.X() + vecLineParameter[3])/vecLineParameter[2]);

	stCrossPointx.SetX(0);
	stCrossPointx.SetY((vecLineParameter[7]*vecLineParameter[2]-vecLineParameter[3]*vecLineParameter[6])/
		(vecLineParameter[6]*vecLineParameter[1]-vecLineParameter[5]*vecLineParameter[2]));
	stCrossPointx.SetZ(-(vecLineParameter[1]*stCrossPointx.Y() + vecLineParameter[3])/vecLineParameter[2]);
	vecCrossPointInfo.push_back(stCrossPointx);
	vecCrossPointInfo.push_back(stCrossPointy);
	vecCrossPointInfo.push_back(stCrossPointz);

	return DxFunctionResult::ReturnOK();
}

DxFunctionResult DxCoordinateTranslator::Get3DLineParameter( const QVector<double>&vecMartix, const DxPoint& stPoint2DInfo,
															QVector<double>&vecLineParameter ,const DxPoint2D& stImageOffset)
{
	DxLOG_FUNC_TRACE();

	if (vecMartix.size() != 11)
	{
		return DxFunctionResult::ReturnError() ;
	}
    DxPoint stPoint2DInfoTmp;
    stPoint2DInfoTmp.SetX(stPoint2DInfo.X()-stImageOffset.X());
    stPoint2DInfoTmp.SetY(stPoint2DInfo.Y()-stImageOffset.Y());
    stPoint2DInfoTmp.SetZ(0.0);

	vecLineParameter.clear();
	double dNum = 0;  
	dNum = vecMartix[4]*stPoint2DInfoTmp.X() -vecMartix[0];
	vecLineParameter.push_back(dNum);
	dNum = vecMartix[5]*stPoint2DInfoTmp.X() -vecMartix[1];
	vecLineParameter.push_back(dNum);
	dNum = vecMartix[6]*stPoint2DInfoTmp.X() -vecMartix[2];
	vecLineParameter.push_back(dNum);
	dNum = stPoint2DInfoTmp.X() -vecMartix[3];
	vecLineParameter.push_back(dNum);
	dNum = vecMartix[4]*stPoint2DInfoTmp.Y() -vecMartix[7];
	vecLineParameter.push_back(dNum);
	dNum = vecMartix[5]*stPoint2DInfoTmp.Y() -vecMartix[8];
	vecLineParameter.push_back(dNum);
	dNum = vecMartix[6]*stPoint2DInfoTmp.Y() -vecMartix[9];
	vecLineParameter.push_back(dNum);
	dNum = stPoint2DInfoTmp.Y() -vecMartix[10];
	vecLineParameter.push_back(dNum);

	return DxFunctionResult::ReturnOK();
}

DxFunctionResult DxCoordinateTranslator::CalculatorRelativePoint(const DxImagePtr& pImage, const DxImagePtr& pRelativeImage,  
																 const DxPoint& kImagePoint, DxPoint& kRelativeImagePoint, QVector<DxPoint>& kLine)
{
	DxLOG_FUNC_TRACE();
	Q_ASSERT(!pImage.isNull());
	Q_ASSERT(!pRelativeImage.isNull());

	kLine.clear();
	QVector<double> vecMatrix;
    DxPoint2D ImageOffset;
	pImage->GetXspotMatrix( vecMatrix ,ImageOffset);
	QVector<DxPoint> vec3D;
	DxCoordinateTranslator::Get3DCoordinatesBy2DPoint(vecMatrix, kImagePoint,vec3D,ImageOffset);
	if ( vec3D.size() != 3 )
	{
		return DxFunctionResult::ReturnError();
	}
	QVector<double> vecRelativeMatrix;
    DxPoint2D RelativeImageOffset;
	pRelativeImage->GetXspotMatrix( vecRelativeMatrix,RelativeImageOffset );
	DxPoint kImagePoint0;
	DxPoint kStartPoint((vec3D[0].X() + vec3D[2].X())/2.0, 
		(vec3D[0].Y() + vec3D[2].Y())/2.0, (vec3D[0].Z() + vec3D[2].Z())/2.0);
	DxCoordinateTranslator::Get2DCoordinatesBy3DPoint(vecRelativeMatrix, kStartPoint, kImagePoint0,RelativeImageOffset);
	kLine.push_back(kImagePoint0);
	DxPoint kImagePoint1;
	DxPoint kEndPoint((vec3D[1].X() + vec3D[2].X())/2.0, 
		(vec3D[1].Y() + vec3D[2].Y())/2.0, (vec3D[1].Z() + vec3D[2].Z())/2.0);

	DxCoordinateTranslator::Get2DCoordinatesBy3DPoint(vecRelativeMatrix, kEndPoint, kImagePoint1,RelativeImageOffset);
	kLine.push_back(kImagePoint1);
	
	double x = (kRelativeImagePoint.Y() - kImagePoint0.Y()) * (kImagePoint1.X() - kImagePoint0.X()) / (kImagePoint1.Y() - kImagePoint0.Y()) + kImagePoint0.X();
	kRelativeImagePoint.SetX(x);

	return DxFunctionResult::ReturnOK();
}

DxFunctionResult DxCoordinateTranslator::Get3DCrossPoint(const QVector<double>&vecMartix1,
										const DxPoint& stPoint2DInfo1,
                                        const DxPoint2D&stImageOffset1,
										const QVector<double>&vecMartix2,                                        
										const DxPoint& stPoint2DInfo2,
                                        const DxPoint2D&stImageOffset2,
										DxPoint& st3DCrossPoint)
{
	if ((vecMartix1.size() != 11)&&(vecMartix2.size() != 11))
	{
		return DxFunctionResult::ReturnError() ;
	} 
	QVector<DxPoint>stLinePoint1;
	QVector<DxPoint>stLinePoint2;
	stLinePoint1.clear();
	stLinePoint2.clear();
	DxFunctionResult Result;
    DxPoint stPoint2DInfoTmp1;
    DxPoint stPoint2DInfoTmp2;
    stPoint2DInfoTmp1.SetX(stPoint2DInfo1.X()-stImageOffset1.X());
    stPoint2DInfoTmp1.SetY(stPoint2DInfo1.Y()-stImageOffset1.Y());
    stPoint2DInfoTmp1.SetZ(0.0);
    stPoint2DInfoTmp2.SetX(stPoint2DInfo2.X()-stImageOffset2.X());
    stPoint2DInfoTmp2.SetY(stPoint2DInfo2.Y()-stImageOffset2.Y());
    stPoint2DInfoTmp2.SetZ(0.0);
	Result = Get3DCoordinatesBy2DPoint(vecMartix1,stPoint2DInfoTmp1,stLinePoint1);
	if (Result.IsError())
	{
		return DxFunctionResult::ReturnError() ;
	}
	Result = Get3DCoordinatesBy2DPoint(vecMartix2,stPoint2DInfoTmp2,stLinePoint2);
	if (Result.IsError())
	{
		return DxFunctionResult::ReturnError() ;
	}

	Result = Coordinates3DCrossPoint(stLinePoint1,stLinePoint2,st3DCrossPoint);
	if (Result.IsError())
	{
		return DxFunctionResult::ReturnError() ;
	}

	return DxFunctionResult::ReturnOK();
}

DxFunctionResult DxCoordinateTranslator::Coordinates3DCrossPoint(const QVector<DxPoint>& vecLinePoint1,
												const QVector<DxPoint>& vecLinePoint2,
												DxPoint& stCrossPoint)
{

// 	if ((vecLinePoint1.size() != 3)&&(vecLinePoint2.size() != 3))
// 	{
// 		return DxFunctionResult::ReturnError() ;
// 	} 

	DxPoint stVector1;
	stVector1.SetX( vecLinePoint1[0].X() - vecLinePoint1[1].X() );
	stVector1.SetY( vecLinePoint1[0].Y() - vecLinePoint1[1].Y() );
	stVector1.SetZ( vecLinePoint1[0].Z() - vecLinePoint1[1].Z() );
	DxPoint stVector2;
	stVector2.SetX( vecLinePoint2[0].X() - vecLinePoint2[1].X() );
	stVector2.SetY( vecLinePoint2[0].Y() - vecLinePoint2[1].Y() );
	stVector2.SetZ( vecLinePoint2[0].Z() - vecLinePoint2[1].Z() );

	DxPoint stVectorN = Cross(stVector1, stVector2);
	DxPoint ab;
	ab.SetX( vecLinePoint1[0].X() - vecLinePoint2[0].X() );
	ab.SetY( vecLinePoint1[0].Y() - vecLinePoint2[0].Y() );
	ab.SetZ( vecLinePoint1[0].Z() - vecLinePoint2[0].Z() );

	double dMinDistance = Dot(stVectorN,ab)/Length(stVectorN);
// 	if (dMinDistance != 0)
// 	{
// 		return DxFunctionResult::ReturnError() ;
// 	}
	DxPoint p1 = vecLinePoint1[0] ;
	DxPoint p2 = vecLinePoint2[0];
	DxPoint stVector3;
	stVector3.SetX( vecLinePoint1[1].X() - vecLinePoint1[0].X() );
	stVector3.SetY( vecLinePoint1[1].Y() - vecLinePoint1[0].Y() );
	stVector3.SetZ( vecLinePoint1[1].Z() - vecLinePoint1[0].Z() );
	DxPoint stVector4;
	stVector4.SetX( vecLinePoint2[1].X() - vecLinePoint2[0].X() );
	stVector4.SetY( vecLinePoint2[1].Y() - vecLinePoint2[0].Y() );
	stVector4.SetZ( vecLinePoint2[1].Z() - vecLinePoint2[0].Z() );
	DxPoint stPoint1;
	DxPoint stPoint2;

	DxPoint tempPoint;
	tempPoint.SetX( p2.X() - p1.X() );
	tempPoint.SetY( p2.Y() - p1.Y() );
	tempPoint.SetZ( p2.Z() - p1.Z() );
	double t1;
	double t2;
	t1 = Dot((Cross(tempPoint,stVector4)),Cross(stVector3,stVector4));
	t2 = Dot((Cross(tempPoint,stVector3)),Cross(stVector3,stVector4));

	double dd = Length((Cross(stVector3,stVector4)));
	t1/=dd*dd;
	t2/=dd*dd;

	stVector3.SetX(stVector3.X() * t1);
	stVector3.SetY(stVector3.Y() * t1);
	stVector3.SetZ(stVector3.Z() * t1);
	stPoint1.SetX(p1.X() + stVector3.X());
	stPoint1.SetY(p1.Y() + stVector3.Y());
	stPoint1.SetZ(p1.Z() + stVector3.Z());

	stVector4.SetX(stVector4.X() * t2);
	stVector4.SetY(stVector4.Y() * t2);
	stVector4.SetZ(stVector4.Z() * t2);
	stPoint2.SetX(p2.X() + stVector4.X());
	stPoint2.SetY(p2.Y() + stVector4.Y());
	stPoint2.SetZ(p2.Z() + stVector4.Z());

	stCrossPoint.SetX((stPoint1.X() + stPoint2.X())/2);
	stCrossPoint.SetY((stPoint1.Y() + stPoint2.Y())/2);
	stCrossPoint.SetZ((stPoint1.Z() + stPoint2.Z())/2);

	return DxFunctionResult::ReturnOK();
}

DxPoint DxCoordinateTranslator::Cross(DxPoint a,DxPoint b)
{
	DxPoint stVectorCross;
	stVectorCross.SetX( a.Y()*b.Z()-a.Z()*b.Y());
	stVectorCross.SetY( a.Z()*b.X()-a.X()*b.Z());
	stVectorCross.SetZ( a.X()*b.Y()-a.Y()*b.X());
	return stVectorCross;
}

double DxCoordinateTranslator::Dot(DxPoint a,DxPoint b)
{
	return a.X()*b.X() +a.Y()*b.Y() +a.Z()*b.Z();
}

double DxCoordinateTranslator::Length(DxPoint a)
{
	return sqrt(Dot(a,a));
} 

DxFunctionResult DxCoordinateTranslator::Coordinates2DCrossPoint(const QVector<DxPoint>& vecLinePoint1,
                                                const QVector<DxPoint>& vecLinePoint2,
                                                DxPoint& stCrossPoint)
{

    if ((vecLinePoint1.size() != 2)&&(vecLinePoint2.size() != 2))
    {
        return DxFunctionResult::ReturnError();
    } 

    DxPoint stVector1(vecLinePoint1[0].X() - vecLinePoint1[1].X(), vecLinePoint1[0].Y() - vecLinePoint1[1].Y(), vecLinePoint1[0].Z() - vecLinePoint1[1].Z());
    DxPoint stVector2(vecLinePoint2[0].X() - vecLinePoint2[1].X(), vecLinePoint2[0].Y() - vecLinePoint2[1].Y(), vecLinePoint2[0].Z() - vecLinePoint2[1].Z());
    DxPoint stVectorN = Cross(stVector1,stVector2);
    DxPoint ab(vecLinePoint1[0].X() - vecLinePoint2[0].X(), vecLinePoint1[0].Y() - vecLinePoint2[0].Y(), vecLinePoint1[0].Z() - vecLinePoint2[0].Z());
    double dMinDistance = Dot(stVectorN,ab)/Length(stVectorN);
    if (dMinDistance != 0)
    {
        return DxFunctionResult::ReturnError();
    }
    DxPoint p1 = vecLinePoint1[0];
    DxPoint p2 = vecLinePoint2[0];
    DxPoint stVector3(vecLinePoint1[1].X() - vecLinePoint1[0].X(), vecLinePoint1[1].Y() - vecLinePoint1[0].Y(), vecLinePoint1[1].Z() - vecLinePoint1[0].Z());
    DxPoint stVector4(vecLinePoint2[1].X() - vecLinePoint2[0].X(), vecLinePoint2[1].Y() - vecLinePoint2[0].Y(), vecLinePoint2[1].Z() - vecLinePoint2[0].Z());
    DxPoint stPoint1;
    DxPoint stPoint2;
    double t1;
    double t2;

    DxPoint pTemp(p2.X() - p1.X(), p2.Y() - p1.Y(), p2.Z() - p1.Z());
    t1 = Dot((Cross(pTemp,stVector4)),Cross(stVector3,stVector4));
    t2 = Dot((Cross(pTemp,stVector3)),Cross(stVector3,stVector4));

    double dd = Length((Cross(stVector3,stVector4)));
    t1/=dd*dd;
    t2/=dd*dd;
    stVector3.SetX(stVector3.X()*t1);
    stVector3.SetY(stVector3.Y()*t1);
    stVector3.SetZ(stVector3.Z()*t1);
    stVector4.SetX(stVector4.X()*t2);
    stVector4.SetY(stVector4.Y()*t2);
    stVector4.SetZ(stVector4.Z()*t2);

    stPoint1.SetX(p1.X() + stVector3.X());
    stPoint1.SetY(p1.Y() + stVector3.Y());
    stPoint1.SetZ(p1.Z() + stVector3.Z());
    stPoint2.SetX(p2.X() + stVector4.X());
    stPoint2.SetY(p2.Y() + stVector4.Y());
    stPoint2.SetZ(p2.Z() + stVector4.Z());

    stCrossPoint.SetX((stPoint1.X() + stPoint2.X())/2);
    stCrossPoint.SetY((stPoint1.Y() + stPoint2.Y())/2);
    stCrossPoint.SetZ((stPoint1.Z() + stPoint2.Z())/2);

    return DxFunctionResult::ReturnOK();
}


DxFunctionResult DxCoordinateTranslator::GetLinePlaneCrossPoint(const QVector<double> vecLineMartix1,
                                               const DxPoint& stPlanePoint1,
                                               const DxPoint& stPlanePoint2,
                                               const DxPoint2D&stImageOffset1,
                                               const QVector<double> vecLineMartix2,
                                               const DxPoint& stLinePoint,
                                               const DxPoint2D&stImageOffset2,
                                               DxPoint& stCrossPoint)
{
    if ((vecLineMartix1.size() != 11)&&(vecLineMartix2.size() != 11))
    {
        return DxFunctionResult::ReturnError();
    }

    QVector<double> vecLineParameter1;
    QVector<double> vecLineParameter2;
    QVector<double> vecLineParameter3;
    vecLineParameter1.clear();
    vecLineParameter2.clear();
    vecLineParameter3.clear();
    DxPoint stPlanePointTmp1;
    DxPoint stPlanePointTmp2;
    DxPoint stLinePointTmp;
    stPlanePointTmp1.SetX(stPlanePoint1.X()-stImageOffset1.X());
    stPlanePointTmp1.SetY(stPlanePoint1.Y()-stImageOffset1.Y());
    stPlanePointTmp1.SetZ(0.0);
    stPlanePointTmp2.SetX(stPlanePoint2.X()-stImageOffset1.X());
    stPlanePointTmp2.SetY(stPlanePoint2.Y()-stImageOffset1.Y());
    stPlanePointTmp2.SetZ(0.0);
    stLinePointTmp.SetX(stLinePoint.X()-stImageOffset2.X());
    stLinePointTmp.SetY(stLinePoint.Y()-stImageOffset2.Y());
    stLinePointTmp.SetZ(0.0);
    
    DxPoint stPoint1;
    DxPoint stPoint2;
    DxPoint stPoint3;
    DxPoint stPoint4;
    Get3DLineParameter(vecLineMartix1,stPlanePointTmp1,vecLineParameter1);
    Get3DLineParameter(vecLineMartix1,stPlanePointTmp2,vecLineParameter2);
    Get3DLineParameter(vecLineMartix2,stLinePointTmp,vecLineParameter3);

    stPoint1.SetX( (vecLineParameter1[7]*vecLineParameter1[1]-vecLineParameter1[3]*vecLineParameter1[5])/
        (vecLineParameter1[0]*vecLineParameter1[5]-vecLineParameter1[4]*vecLineParameter1[1]) );
    stPoint1.SetY( -(vecLineParameter1[0]*stPoint1.X() + vecLineParameter1[3])/vecLineParameter1[1] );
    stPoint1.SetZ( 0 );

    stPoint2.SetX( (vecLineParameter1[7]*vecLineParameter1[2]-vecLineParameter1[3]*vecLineParameter1[6])/
        (vecLineParameter1[0]*vecLineParameter1[6]- vecLineParameter1[4]*vecLineParameter1[2]) );
    stPoint2.SetY( 0 );
    stPoint2.SetZ( -(vecLineParameter1[0]*stPoint2.X() + vecLineParameter1[3])/vecLineParameter1[2] );

	stPoint3.SetX( (vecLineParameter2[7]*vecLineParameter2[1]-vecLineParameter2[3]*vecLineParameter2[5])/
		(vecLineParameter2[0]*vecLineParameter2[5]-vecLineParameter2[4]*vecLineParameter2[1]) );
	stPoint3.SetY( -(vecLineParameter2[0]*stPoint3.X() + vecLineParameter2[3])/vecLineParameter2[1] );
	stPoint3.SetZ( 0 );

	stPoint4.SetX( (vecLineParameter2[7]*vecLineParameter2[2]-vecLineParameter2[3]*vecLineParameter2[6])/
		(vecLineParameter2[0]*vecLineParameter2[6]- vecLineParameter2[4]*vecLineParameter2[2]) );
	stPoint4.SetY( 0 );
	stPoint4.SetZ( -(vecLineParameter2[0]*stPoint4.X() + vecLineParameter2[3])/vecLineParameter2[2] );

    DxPoint stVector1;

    stVector1.SetX( stPoint1.X() - stPoint2.X());
    stVector1.SetY( stPoint1.Y() - stPoint2.Y());
    stVector1.SetZ( stPoint1.Z() - stPoint2.Z());

    DxPoint stVector2;
    stVector2.SetX( stPoint3.X() - stPoint4.X());
    stVector2.SetY( stPoint3.Y() - stPoint4.Y());
    stVector2.SetZ( stPoint3.Z() - stPoint4.Z());

    DxPoint stCrossVector =  Cross(stVector1,stVector2);
    double dParaD = -(stPoint1.X()*stCrossVector.X()+stPoint1.Y()*stCrossVector.Y()+stPoint1.Z()*stCrossVector.Z());

    MatrixXd XTemp = MatrixXd(3, 4);
    MatrixXd X= MatrixXd(3, 3);

    VectorXd imgx = VectorXd(3);
    VectorXd wx = VectorXd(3);

    XTemp.row(0) << stCrossVector.X(),stCrossVector.Y(),stCrossVector.Z(),-dParaD;
    XTemp.row(1) << vecLineParameter3[0],vecLineParameter3[1],vecLineParameter3[2],-vecLineParameter3[3];
    XTemp.row(2) << vecLineParameter3[4],vecLineParameter3[5],vecLineParameter3[6],-vecLineParameter3[7];

    X << XTemp.col(0),
        XTemp.col(1),
        XTemp.col(2);

    imgx = XTemp.col(3);

    wx = X.colPivHouseholderQr().solve(imgx);

    stCrossPoint.SetX( wx[0] );
    stCrossPoint.SetY( wx[1] );
    stCrossPoint.SetZ( wx[2] );

    return DxFunctionResult::ReturnOK();
}

DxFunctionResult DxCoordinateTranslator::CalculateDistanceDoubleLine( QVector<DxPoint>& vecLinePoint1,  QVector<DxPoint>& vecLinePoint2, double& kDistance )
{
	if ((vecLinePoint1.size() != 2)&&(vecLinePoint2.size() != 2))
	{
		return DxFunctionResult::ReturnError();
	} 

	DxPoint kVector1 = vecLinePoint1[1].Sub(vecLinePoint1[0]);
	DxPoint kVector2 = vecLinePoint2[1].Sub(vecLinePoint2[0]);
	DxPoint stVectorN = Cross(kVector1,kVector2);
	DxPoint ab = vecLinePoint1[1].Sub(vecLinePoint2[1]);
	kDistance = stVectorN.Dot(ab)/stVectorN.Length();

	return DxFunctionResult::ReturnOK();
}

DxFunctionResult DxCoordinateTranslator::CalculateAngleDoubleLine( QVector<DxPoint>& vecLinePoint1,  QVector<DxPoint>& vecLinePoint2, double& kAngle )
{
	if ((vecLinePoint1.size() != 2)&&(vecLinePoint2.size() != 2))
	{
		return DxFunctionResult::ReturnError();
	} 

	DxPoint kVector1 = vecLinePoint1[1].Sub(vecLinePoint1[0]);
	DxPoint kVector2 = vecLinePoint2[1].Sub(vecLinePoint2[0]);
	double dAcosValue = kVector1.Dot(kVector2) / (kVector1.Length() * kVector2.Length());
	if( dAcosValue > 0.9999999 )
	{
		dAcosValue = 0.9999999;
	}
	else if( dAcosValue < -0.9999999 )
	{
		dAcosValue = -0.9999999;
	}

	kAngle = acos(dAcosValue);
	return DxFunctionResult::ReturnOK();
}

DxFunctionResult DxCoordinateTranslator::LinePlaneCross(QVector<double> vecLineParameter,QVector<double>vecPlaneParameter,DxPoint& crossPoint)
{


    MatrixXd XTemp = MatrixXd(3, 4);
    MatrixXd X= MatrixXd(3, 3);

    VectorXd imgx = VectorXd(3);
    VectorXd wx = VectorXd(3);

    XTemp.row(0) << vecPlaneParameter[0],vecPlaneParameter[1],vecPlaneParameter[2],-vecPlaneParameter[3];
    XTemp.row(1) << vecLineParameter[0],vecLineParameter[1],vecLineParameter[2],-vecLineParameter[3];
    XTemp.row(2) << vecLineParameter[4],vecLineParameter[5],vecLineParameter[6],-vecLineParameter[7];

    X << XTemp.col(0),
        XTemp.col(1),
        XTemp.col(2);

    imgx = XTemp.col(3);

    wx = X.colPivHouseholderQr().solve(imgx);

    crossPoint.SetX( wx[0] );
    crossPoint.SetY( wx[1] );
    crossPoint.SetZ( wx[2] );

    return DxFunctionResult::ReturnOK();
}

DxFunctionResult DxCoordinateTranslator::PointToLineMinDisPt(DxPoint stPoint,DxPoint stLinePt1,DxPoint stLinePt2,DxPoint& stLineMinDisPt)
{
    DxPoint stLineVt = stLinePt2.Sub(stLinePt1);
    DxPoint stvt = stPoint.Sub(stLinePt1);
    double d = stLineVt.Dot(stvt)/(stLineVt.Length()*stLineVt.Length());
    stLineMinDisPt = stLinePt1.Add(stLineVt.Multiply(d ));
    return DxFunctionResult::ReturnOK();
}