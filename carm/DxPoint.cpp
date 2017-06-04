#include <QXmlStreamReader>

#include "DxMath.h"
#include "DxPoint.h"
#include <QStringlist>

// DXXMLDEFINE_H
#include <QString>


/****for xml nodes names***/

//DxProject
const QString kProjectVersionNumber("version1.0.0");

const QString kProjectXml_Project("Project");
const QString kProjectXml_ProjectID("ProjectID");
const QString kProjectXml_ProjectName("ProjectName");
const QString kProjectXml_ProjectVersionNumber("ProjectVersionNumber");
const QString kProjectXml_ProjectDescription("ProjectDescription");
const QString kProjectXml_PrimaryContrast("PrimaryContrast");
const QString kProjectXml_ReferenceContrast("ReferenceContrast");
const QString kProjectXml_ContrastInfoList("ContrastInfoList");
const QString kProjectXml_SkeletonInfoList("SkeletonInfoList");

//DxContrastInfo
const QString kContrastInfoXml_ContrastInfo("ContrastInfo");
const QString kContrastInfoXml_ContrastID("ContrastID");
const QString kContrastInfoXml_IsAnalyzedInProject("IsAnalyzedInProject");
const QString kContrastInfoXml_SeriesUid("SeriesUid");
const QString kContrastInfoXml_ContrastName("ContrastName");
const QString kContrastInfoXml_ContrastDescription("ContrastDescription");
const QString kContrastInfoXml_ImageList("ImageList");

//DxImageInfo
const QString kImageInfoXml_ImagePath("ImagePath");

//DxSkeletonInfo
const QString kSkeletonInfoXml_SkeletonInfo("SkeletonInfo");
const QString kSkeletonInfoXml_SkeletonID("SkeletonID");
const QString kSkeletonInfoXml_SkeletonName("SkeletonName");
const QString kSkeletonInfoXml_SkeletonDescription("SkeletonDescription");
const QString kSkeletonInfoXml_SkeletonInfoComment("SkeletonInfoComment");
const QString kSkeletonInfoXml_SkeletonContourInfo("SkeletonContourInfo");
const QString kSkeletonInfoXml_SegmentInfoList("SegmentInfoList");

//DxPoint
const QString kPointXml_Point("Point");

//SegmentInfo
const QString kSegmentInfoXml_SegmentInfo("SegmentInfo");
const QString kSegmentInfoXml_SegmentID("SegmentID");
const QString kSegmentInfoXml_SegmentName("SegmentName");
const QString kSegmentInfoXml_SegmentDescription("SegmentDescription");
const QString kSegmentInfoXml_SegmentInfoComment("SegmentInfoComment");
const QString kSegmentInfoXml_Endpoint("Endpoint");
const QString kSegmentInfoXml_EndpointStart("Start");
const QString kSegmentInfoXml_EndpointEnd("End");
const QString kSegmentInfoXml_ContrastRegistrationInfoList("ContrastRegistrationInfoList");
const QString kSegmentInfoXml_CenterlineInfo("CenterlineInfo");
const QString kSegmentInfoXml_ReferencePoint("ReferencePoint");
const QString kSegmentInfoXml_LumenInfoList("LumenInfoList");
const QString kSegmentInfoXml_WallInfoList("WallInfoList");
const QString kSegmentInfoXml_SliceInfoList("SliceInfoList");
const QString kSegmentInfoXml_SliceSpacing("SliceSpacing");
const QString kSegmentInfoXml_SliceThickness("SliceThickness");

//DxContrastRegistrationInfo
const QString kContrastRegInfoXml_ContrastRegInfo("ContrastRegistrationInfo");
const QString kContrastRegInfoXml_ContrastID("ContrastID");
const QString kContrastRegInfoXml_RegistrationMatrix("RegistrationMatrix");
const QString kContrastRegInfoXml_RegistrationPointMatrix("PointRegistrationMatrix");
const QString kContrastRegInfoXml_SlicePanList("SlicePanList");
const QString kContrastRegInfoXml_SlicePan("SlicePan");
const QString kContrastRegInfoXml_ReferPointsList("ReferPointsList");
const QString kContrastRegInfoXml_RegisterPointsList("RegisterPointsList");
const QString kContrastRegInfoXml_RegisterCenterPointsList("RegisterCenterPointsList");
const QString kContrastRegInfoXml_ReferCenterPointsList("ReferCenterPointsList");
const QString kContrastRegInfoXml_RegistrationPoint("RegistrationPoint");


//DxSliceInfo
const QString kSliceInfoXml_SliceInfo("SliceInfo");
const QString kSliceInfoXml_SliceInfoType("SliceInfoType");
const QString kSliceInfoXml_SliceInfoComment("SliceInfoComment");
const QString kSliceInfoXml_SliceInfoImageQuality("ImageQuality");
const QString kSliceInfoXml_SliceCenter("SliceCenter");
const QString kSliceInfoXml_SliceNormal("SliceNormal");
const QString kSliceInfoXml_PlaqueInfoList("PlaqueInfoList");


//DxPlaqueInfo
const QString kPlaqueInfoXml_PlaqueInfo("PlaqueInfo");
const QString kPlaqueInfoXml_PlaqueType("PlaqueType");
const QString kPlaqueInfoXml_PlaqueContourInfo("PlaqueContourInfo");

const QString kLumenInfoXml_LumenContourInfo("LumenContourInfo");
const QString kWallInfoXml_WallContourInfo("WallContourInfo");

//Result
const QString kResultNode_Item("Item");
const QString kResultNode_Item_Name("name");
const QString kResultNode_Item_Value("value");
const QString kResultNode_Item_Type("type");
const QString kResultNode_Item_Function("function");
const QString kResultNode_Group("Group");
const QString kResultNode_Group_Name("name");
const QString kResultNode_Group_Items("items");
const QString kResultNode_Group_LoopFunction("loop_func");
const QString kResultNode_Group_Table("table");

const QString kResultNode_Result_Root("result");
const QString kResultNode_Result_Template("template");

const QString kResultNode_Result_Loop("Loop");
// DXXMLDEFINE_H



DxPoint::DxPoint():DxArray<double,3>()
{
    //DxLOG_FUNC_TRACE();
}

DxPoint::DxPoint(double x,double y,double z):
    DxArray<double,3>()
{
    //DxLOG_FUNC_TRACE();
    m_array[0]=x;
    m_array[1]=y;
    m_array[2]=z;
}

DxPoint::DxPoint( double *point, int length )
    :DxArray<double,3>(point, length)
{
    //DxLOG_FUNC_TRACE();
}

DxPoint::DxPoint( const DxPoint &other )
    :DxArray<double,3>(other)
{
    //DxLOG_FUNC_TRACE();
}

DxPoint::~DxPoint()
{
    //DxLOG_FUNC_TRACE();
}

double DxPoint::X()  const
{
    //DxLOG_FUNC_TRACE();
    return m_array[0];
}

double DxPoint::Y() const
{
    //DxLOG_FUNC_TRACE();
    return m_array[1];
}

double DxPoint::Z() const
{
    //DxLOG_FUNC_TRACE();
    return m_array[2];
}

void DxPoint::SetX( double x )
{
    //DxLOG_FUNC_TRACE();
    m_array[0]=x;
}

void DxPoint::SetY( double y )
{
    //DxLOG_FUNC_TRACE();
    m_array[1]=y;
}

void DxPoint::SetZ( double z )
{
    //DxLOG_FUNC_TRACE();
    m_array[2]=z;
}

void DxPoint::SetPoint( double x,double y,double z )
{
    //DxLOG_FUNC_TRACE();
    m_array[0]=x;
    m_array[1]=y;
    m_array[2]=z;
}

bool DxPoint::operator==( const DxPoint &other ) const
{
    //DxLOG_FUNC_TRACE();
    if (DxMath::DoubleNotEqual(m_array[0],other.m_array[0]))
    {
        return false;
    }
    else if (DxMath::DoubleNotEqual(m_array[1],other.m_array[1]))
    {
        return false;
    }
    else if (abs(DxMath::DoubleNotEqual(m_array[2],other.m_array[2])))
    {
        return false;
    }

    return true;
}

bool DxPoint::operator!=( const DxPoint &other ) const
{
    //DxLOG_FUNC_TRACE();
    return !operator==(other);
}

DxPoint &DxPoint::operator=( const DxPoint &other )
{
    //DxLOG_FUNC_TRACE();
    DxArray::operator=(other);
    return *this;
}

QString DxPoint::ToString( char sperator/*='\\'*/, int nPrecisionCount /*= 2*/ ) const
{
    //DxLOG_FUNC_TRACE();
    QStringList ls;
    ls << QString::number(X(), 'f', nPrecisionCount) 
       << QString::number(Y(), 'f', nPrecisionCount)
       << QString::number(Z(), 'f', nPrecisionCount);
    return ls.join(sperator);
}

QString DxPoint::ToXmlString()
{
    //DxLOG_FUNC_TRACE();
    QString xmlString;
    xmlString = QString::number(X()).append(",")
        .append(QString::number(Y())).append(",")
        .append(QString::number(Z()));
    return xmlString;
}

void DxPoint::ToXmlString(QXmlStreamWriter &streamWriter) const
{
    //DxLOG_FUNC_TRACE();
    QString xmlString;
    xmlString = QString::number(X()).append(",")
        .append(QString::number(Y())).append(",")
        .append(QString::number(Z()));
    streamWriter.writeTextElement(kPointXml_Point, xmlString);
}


void DxPoint::FromXmlString( const QString &strXMLText,char sperator/*=','*/ )
{
    //DxLOG_FUNC_TRACE();
    QStringList pointList = strXMLText.split(sperator);
    Q_ASSERT(pointList.size() == 3);
    SetPoint(pointList[0].toDouble(),pointList[1].toDouble(),pointList[2].toDouble());
}

void DxPoint::FromXml( QXmlStreamReader &streamReader,char sperator/*=','*/ )
{
    QXmlStreamReader::TokenType resultType = streamReader.tokenType();
    QString tempName = streamReader.name().toString();
    while( (streamReader.isStartElement() || tempName != kPointXml_Point)&&
        resultType != QXmlStreamReader::Invalid )
    {
        if(streamReader.isStartElement())
        {
            FromXmlString(streamReader.readElementText(),sperator);
            break;
        }
        resultType = streamReader.readNext();
        tempName = streamReader.name().toString();
    }
}

bool DxPoint::ApproximateEqual( double x, double y, double z, double precision )
{
    //DxLOG_FUNC_TRACE();
    Q_ASSERT(precision > 0.0);
    if (fabs(x - X()) < precision &&
        fabs(y - Y()) < precision &&
        fabs(z - Z()) < precision)
    {
        return true;
    }
    return false;
}

bool DxPoint::ApproximateEqual( const DxPoint& ptOther, double precision )
{
    //DxLOG_FUNC_TRACE();
    return ApproximateEqual(ptOther.X(), ptOther.Y(), ptOther.Z(), precision);
}

const bool DxPoint::IsEqual( const DxPoint &pt1, const DxPoint &pt2 )
{
    //DxLOG_FUNC_TRACE();
    return (DxMath::DoubleEqual(pt1.X(), pt2.X()) &&
            DxMath::DoubleEqual(pt1.Y(), pt2.Y()) &&
            DxMath::DoubleEqual(pt1.Z(), pt2.Z()));
}

DxPoint DxPoint::Scale(const double &rhs)
{
	DxPoint VectorResult(0.0, 0.0, 0.0);

	VectorResult.SetX(m_array[0] * rhs);
	VectorResult.SetY(m_array[1] * rhs);
	VectorResult.SetZ(m_array[2] * rhs);

	return VectorResult;
}

DxPoint DxPoint::Cross(const DxPoint &rhs)
{
	DxPoint VectorResult(0.0, 0.0, 0.0);

	VectorResult.SetX(m_array[1] * rhs.Z() - m_array[2] * rhs.Y());
	VectorResult.SetY(m_array[2] * rhs.X() - m_array[0] * rhs.Z());
	VectorResult.SetZ(m_array[0] * rhs.Y() - m_array[1] * rhs.X());

	return VectorResult;
}

double DxPoint::Dot(const DxPoint &rhs){
	return m_array[0]*rhs.X() + m_array[1]*rhs.Y() + m_array[2]*rhs.Z();
}

double DxPoint::Length()
{
	return sqrt(m_array[0]*m_array[0] + m_array[1]*m_array[1] + m_array[2]*m_array[2]);
}

DxPoint DxPoint::Add(const DxPoint &rhs)
{
	DxPoint VectorResult(0.0, 0.0, 0.0);

	VectorResult.SetX(m_array[0] + rhs.X());
	VectorResult.SetY(m_array[1] + rhs.Y());
	VectorResult.SetZ(m_array[2] + rhs.Z());

	return VectorResult;
}

DxPoint DxPoint::Sub(const DxPoint &rhs)
{
	DxPoint VectorResult(0.0, 0.0, 0.0);

	VectorResult.SetX(m_array[0] - rhs.X());
	VectorResult.SetY(m_array[1] - rhs.Y());
	VectorResult.SetZ(m_array[2] - rhs.Z());

	return VectorResult;
}

DxPoint DxPoint::Multiply(const double &rhs)
{
	DxPoint VectorResult(0.0, 0.0, 0.0);

	VectorResult.SetX(m_array[0] * rhs);
	VectorResult.SetY(m_array[1] * rhs);
	VectorResult.SetZ(m_array[2] * rhs);

	return VectorResult;
}

DxPoint DxPoint::Normalize()
{
	DxPoint VectorResult(0.0, 0.0, 0.0);

	VectorResult.SetX(m_array[0] / Length());
	VectorResult.SetY(m_array[1] / Length());
	VectorResult.SetZ(m_array[2] / Length());

	return VectorResult;
}

