#ifndef DXCONTROLPOINT_H
#define DXCONTROLPOINT_H

#include "DxArray.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class  DxPoint:public DxArray<double,3>
{
public:
    DxPoint();
    DxPoint(double x,double y,double z);
    DxPoint(double *point,int length);
    DxPoint(const DxPoint &other);
    ~DxPoint();

public:
    DxPoint &operator=(const DxPoint &other);
    bool operator==(const DxPoint &other) const;
    bool operator!=(const DxPoint &other) const;

public:
    double X() const;
    double Y() const;
    double Z() const;

    void SetX(double x);
    void SetY(double y);
    void SetZ(double z);

    void SetPoint(double x,double y,double z);

    QString ToString(char sperator='\\', int nPrecisionCount = 2) const;
    void ToXmlString(QXmlStreamWriter &streamWriter) const;
    QString ToXmlString();
    void FromXmlString(const QString &strXMLText,char sperator=',');
    void FromXml(QXmlStreamReader &streamReader,char sperator=',');

    bool ApproximateEqual(double x, double y, double z, double precision);
    bool ApproximateEqual(const DxPoint& ptOther, double precision);

    static const bool IsEqual(const DxPoint &pt1, const DxPoint &pt2);

	DxPoint Scale(const double &rhs);
	DxPoint Cross(const DxPoint &rhs);
	double Dot(const DxPoint &rhs);
	double Length();
	DxPoint Add(const DxPoint &rhs);
	DxPoint Sub(const DxPoint &rhs);
	DxPoint Multiply(const double &rhs);
	DxPoint Normalize();
};

typedef QSharedPointer<DxPoint> DxPointPtr;

#endif
