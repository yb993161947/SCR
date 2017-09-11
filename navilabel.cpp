#include "navilabel.h"
#include "qdebug.h"
NaviLabel::NaviLabel(QWidget *parent):QLabel(parent)
{
    P1 = QPointF(-1,-1);
    P2 = QPointF(-1,-1);
 //   setGeometry(0,0,500,500);



}

NaviLabel::~NaviLabel()
{

}

void NaviLabel::Input_points(Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4)
{
    Vector3d x,y,z;
    x<<1,0,0;
    y<<0,1,0;
    z<<0,0,1;
    Vector3d vecA;
    vecA<<p2(0)-p1(0),p2(1)-p1(1),p2(2)-p1(2);
    double angle_1,angle_2,cos1,sin1,cos2,sin2;

    if(vecA.dot(x)==0&&vecA.dot(y)==0&&vecA.dot(z)<0)
        angle_1=0,angle_2=0;
    else if(vecA.dot(y)==0)
    {
        angle_1=0,angle_2=Angle(vecA,z);
    }
   else if(vecA.dot(x)==0)
    {
        angle_1=Angle(vecA,z),angle_2=0;
    }
    else
    {
        Vector3d vecB=vecA-Project_line(vecA,x);
        double angle_1=Angle(vecB,z);
        int dir1=(x.dot(vecB.cross(z))<=0?-1:1);
        angle_1*=dir1;


        double modB=sqrt(vecB(0)*vecB(0)+vecB(1)*vecB(1)+vecB(2)*vecB(2));
        Vector3d vecC=z*modB+Project_line(vecA,x);
        double angle_2=Angle(vecC,z);
        double dir2=(y.dot(vecC.cross(z))<=0?-1:1);
        angle_2*=dir2;
    }

    cos1=(double )cos(angle_1);
    sin1=(double )sin(angle_1);
    cos2=(double) cos(angle_2);
    sin2=(double) sin(angle_2);




    Matrix4d rotation1;
             rotation1 <<1,0,0,0,
                        0,cos1,-sin1,0,
                        0,sin1,cos1,0,
                        0,0,0,1;
    Matrix4d rotation2;
             rotation2<<cos2,0,sin2,0,
                        0,1,0,0,
                        -sin2,0,cos2,0,
                        0,0,0,1;
    Matrix4d translation1;
             translation1<<1,0,0,-p1(0),
                           0,1,0,-p1(1),
                           0,0,1,-p1(2),
                           0,0,0,1;
    Vector4d three;
             three<<p3(0),p3(1),p3(2),1;
    Vector4d four;
    four << p4(0),p4(1),p4(2),1;
    Vector4d tp3=translation1*rotation1*rotation2*three;
    Vector4d tp4=translation1*rotation1*rotation2*four;

    P1.setX(tp3(0)+ori);
    P1.setY(tp3(1)+ori);
    P2.setX(tp4(0)+ori);
    P2.setY(tp4(1)+ori);



 }

void NaviLabel::initPix(QString path)
{
     update();
     //this->setPixmap(*pix);
     //this->setGeometry(0,0,size,size);
     //this->setFixedSize(size,size);
}

double NaviLabel::Angle(Vector3d d1,Vector3d d2)
{
    double kousai=(d1(0)*d2(0)+d1(1)*d2(1)+d1(2)*d2(2))/sqrt(d1(0)*d1(0)+d1(1)*d1(1)+d1(2)*d1(2))/sqrt(d2(0)*d2(0)+d2(1)*d2(1)+d2(2)*d2(2));
    return (double) acos(kousai);
}
Vector3d NaviLabel::Project_line(Vector3d f1, Vector3d f2)
{

    Vector3d f3=f2/sqrt(f2(0)*f2(0)+f2(1)*f2(1)+f2(2)*f2(2))*(sqrt(f1(0)*f1(0)+f1(1)*f1(1)+f1(2)*f1(2))*(double) cos(Angle(f1,f2)));
    return f3;
}

void NaviLabel::setparameters(double origin, double size, double radius)
{
    ori=origin,siz=size,rad=radius;


}


void NaviLabel::setpicture(QPixmap &pix1)
{
    pix = pix1.scaled(siz,siz);
   //this->setGeometry(0,0,siz,siz);

}

void NaviLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    if(pix.isNull())
        return;

    if(P1 != QPointF(-1,-1) && P2 != QPointF(-1,-1))
    {
        QPainter painter(this);
        setGeometry(0,0,siz,siz);
        //pix->scaled(siz,siz);
        //painter.begin(pix);

        painter.drawPixmap(0,0,pix);
        painter.drawLine(QPoint(0,0),QPoint(150,150));

        if((P1.x()<ori+rad)&&(P1.x()>ori-rad)&&(P1.y()<ori+rad)&&(P1.y()>ori-rad)&&(P2.x()<ori+rad)&&(P2.x()>ori-rad)&&(P2.y()<ori+rad)&&(P2.y()>ori-rad))
        {
            painter.setPen(QPen(Qt::green,5));
            painter.drawLine(P1,P2);
        }
        else if(((P1.x()-ori)*(P1.x()-ori)+(P1.y()-ori)*(P1.y()-ori)<ori*ori)||((P2.x()-ori)*(P2.x()-ori)+(P2.y()-ori)*(P2.y()-ori)<ori*ori))
        {
            painter.setPen(QPen(Qt::red,5));
            painter.drawLine(P1,P2);
        }
        else
        {

            painter.setPen(QPen(Qt::magenta,3,Qt::DashLine));
            painter.drawLine(QPoint(ori,ori),QPoint(((P1.x()+P2.x())/2),((P1.y()+P2.y())/2)));
        }


        painter.end();

    }

}

