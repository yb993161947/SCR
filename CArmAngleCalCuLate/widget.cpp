#include "widget.h"
#include "ui_CArmwidget.h"
#include <QPixmap>
#include <QFileDialog>
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QIcon>
#include <QtCore/qmath.h>
#include <QMatrix4x4>
const int SQUARE_LENGTH=52;
const int ENLARGE_SCALE = 10;
const int WIDTH_OPENPICTURE = 600,HEIGHT_OPENPICTURE = 600;
const int X_OPENPITURE = 60,Y_OPENPICTURE = 90;
const int X_ENLARGE = 720,Y_ENLARGE = 110;
const int WIDTH_ENLARGE =280,HEIGHT_ENLARGE = 280;
using namespace Eigen;
#define PI 3.141592654
CArmWidget::CArmWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CArmWidget)
{
    ui->setupUi(this);

    this->setWindowTitle(QString::fromLocal8Bit("2D图像参数测量系统"));
    QIcon windowicon(":/new/prefix1/images/center.png");
    this->setWindowIcon(windowicon);
    iRadioButtonIndex=0;//采集的是第几个点

    Bkg = QPixmap(":/images/bkg.png");
    Bkg = Bkg.scaled(this->width(),this->height());

    //btnGroupFruits=new QButtonGroup(this);
    btnGroupFruits.addButton(ui->radioButton_1,0);
    btnGroupFruits.addButton(ui->radioButton_2,1);
    btnGroupFruits.addButton(ui->radioButton_3,2);
    btnGroupFruits.addButton(ui->radioButton_4,3);
    btnGroupFruits.addButton(ui->radioButton_5,4);
    btnGroupFruits.addButton(ui->radioButton_6,5);
    for(int i = 0; i < 6; i++)
    {
        qPoint_originalImagePoint[i] = QPoint(0,0);
    }
    connect(this,SIGNAL(sendsingnal()),this,SLOT(slot_text()));
}

CArmWidget::~CArmWidget()
{
    delete ui;
}


void CArmWidget::on_pushButtonOpenPicture_clicked()
{
    //打开图片

    qStr_ImageFilePath= QFileDialog::getOpenFileName
             (this, "打开图片", QDir::currentPath(), "images(*.jpg *.png *.bmp)");//打开图片
    OpenPiture_temp.load(qStr_ImageFilePath);
    OpenPiture=OpenPiture_temp.scaled(WIDTH_OPENPICTURE,HEIGHT_OPENPICTURE);
    OpenPiture_temp=OpenPiture;
    update();
}


void CArmWidget::paintEvent(QPaintEvent * )
{

    QPainter painter1;
    painter1.begin(this);
    painter1.setPen(QPen(Qt::red, 1, Qt::SolidLine));
    painter1.drawPixmap(0,0,Bkg);
    painter1.drawPixmap(X_OPENPITURE,Y_OPENPICTURE,
                        WIDTH_OPENPICTURE,HEIGHT_OPENPICTURE,QPixmap(":/images/bkg5.png"));
    painter1.end();
   // painter2.setPen(QPen(Qt::red, 1, Qt::SolidLine));

    if(!qStr_ImageFilePath.isNull())    //打开了图片文件，原图片放到一个QPixmap文件下
    {
      //   if(originalImagePos.x()>=(SQUARE_LENGTH/2))
             if(originalImagePos.x()>=(0))
        {
            painter1.begin(&OpenPiture);
            painter1.setPen(QPen(Qt::red, 1, Qt::SolidLine));

            painter1.drawPixmap(QPoint(0,0),OpenPiture_temp);
            for(int  i = 0 ;i < 6 ; i++)
//            int i=btnGroupFruits.checkedId();//画原图十字
            {
                if(qPoint_originalImagePoint[i].x() ==0)
                    continue;

                    painter1.drawLine(qPoint_originalImagePoint[i]-QPointF(10, 0),
                                      qPoint_originalImagePoint[i]+QPointF(10, 0));
                    painter1.drawLine(qPoint_originalImagePoint[i]-QPointF(0, 10),
                                      qPoint_originalImagePoint[i]+QPointF(0, 10));

                painter1.drawText(qPoint_originalImagePoint[i]+QPointF(15, -15),
                                  QString("%1").arg(i));

            }



            //画原图上线
            painter1.setPen(QPen(Qt::blue, 3, Qt::SolidLine));
            if(qPoint_originalImagePoint[0].x()>0
                    &&qPoint_originalImagePoint[0].y()>0
                    &&qPoint_originalImagePoint[1].x()>0
                    &&qPoint_originalImagePoint[1].y()>0)
            {
                painter1.drawLine(qPoint_originalImagePoint[0],qPoint_originalImagePoint[1]);
            }

             painter1.setPen(QPen(Qt::yellow, 3, Qt::SolidLine));
             if(qPoint_originalImagePoint[2].x()>0
                     &&qPoint_originalImagePoint[2].y()>0
                     &&qPoint_originalImagePoint[3].x()>0
                     &&qPoint_originalImagePoint[3].y()>0)
            {
                painter1.drawLine(qPoint_originalImagePoint[2],qPoint_originalImagePoint[3]);
            }
             painter1.setPen(QPen(Qt::yellow, 3, Qt::SolidLine));
             if(qPoint_originalImagePoint[4].x()>0
                     &&qPoint_originalImagePoint[4].y()>0
                     &&qPoint_originalImagePoint[5].x()>0
                     &&qPoint_originalImagePoint[5].y()>0)
            {
                painter1.drawLine(qPoint_originalImagePoint[4],qPoint_originalImagePoint[5]);
            }


             painter1.end();

             painter1.begin(this);
             painter1.setPen(QPen(Qt::red, 1, Qt::SolidLine));
             painter1.drawPixmap(X_OPENPITURE,Y_OPENPICTURE,
                                 WIDTH_OPENPICTURE,HEIGHT_OPENPICTURE,OpenPiture);

            enlargePic(originalImagePos, SQUARE_LENGTH, SQUARE_LENGTH);//将原图上点击点附近52像素图片区放大
            //绘制放大图上的点
            painter1.drawPixmap(X_ENLARGE,Y_ENLARGE,
                                WIDTH_ENLARGE,HEIGHT_ENLARGE,EnlargedPicture);
            painter1.end();
            OpenPiture=OpenPiture_temp;
        }
         else
         {
             painter1.begin(this);
             painter1.setPen(QPen(Qt::red, 1, Qt::SolidLine));
             painter1.drawPixmap(X_OPENPITURE,Y_OPENPICTURE,
                                 WIDTH_OPENPICTURE,HEIGHT_OPENPICTURE,OpenPiture);
             painter1.drawPixmap(X_ENLARGE,Y_ENLARGE,
                                 WIDTH_ENLARGE,HEIGHT_ENLARGE,QPixmap(":/new/prefix1/images/bkg5.png"));
             painter1.end();
         }

        MeasureLength(qPoint_originalImagePoint);

    }
    else
    {
        painter1.begin(this);
        painter1.setPen(QPen(Qt::red, 1, Qt::SolidLine));
        painter1.drawPixmap(X_OPENPITURE,Y_OPENPICTURE,
                            WIDTH_OPENPICTURE,HEIGHT_OPENPICTURE,QPixmap(":/images/bkg5.png"));
        painter1.drawPixmap(X_ENLARGE,Y_ENLARGE,
                            WIDTH_ENLARGE,HEIGHT_ENLARGE,QPixmap(":/images/bkg5.png"));
        painter1.end();
    }
    calculateAngle();
    //显示角度
    int i;
    for(i =0; i<4; i++)
    {
        if(qPoint_originalImagePoint[i].x()<=0 || qPoint_originalImagePoint[i].x()>=1024)
        return;
    }
    if(i == 4)
    {
       double angle=Angle_Point(qPoint_originalImagePoint[0]-qPoint_originalImagePoint[1],qPoint_originalImagePoint[2]-qPoint_originalImagePoint[3]);
       ui->textBrowserMeasureValue_Angle->setText(QString::number(angle));

    }

}


void CArmWidget::mouseReleaseEvent(QMouseEvent *event)
{

    qPoint_MousePoint1=event->pos();

    QRect qrect_temp;

    double x1,y1,w1,h1;
    x1=X_OPENPITURE;
    y1=Y_OPENPICTURE;
    w1=WIDTH_OPENPICTURE;//缩放后的图片大小和图片框一致
    h1=WIDTH_OPENPICTURE;

    qrect_temp.setX(x1);
    qrect_temp.setY(y1);
    qrect_temp.setWidth(w1);
    qrect_temp.setHeight(h1);

    if((qPoint_MousePoint1.x()>=qrect_temp.x())
            &&(qPoint_MousePoint1.y()>=qrect_temp.y())
            &&(qPoint_MousePoint1.x()<=(qrect_temp.x()+qrect_temp.width()))
            &&(qPoint_MousePoint1.y()<=(qrect_temp.y()+qrect_temp.height())))
         //如果鼠标在原始图片框里 获得鼠标屏幕坐标，所有计算都在屏幕坐标系下
    {
        qPoint_MousePoint=event->pos();//鼠标的屏幕坐标
        originalImagePos.setX(qPoint_MousePoint.x()-X_OPENPITURE);
        originalImagePos.setY(qPoint_MousePoint.y()-Y_OPENPICTURE);
        //给图片坐标赋一个初值，要计算在缩放后的原始图片上的坐标，便于放大局部点的采集
        dx=originalImagePos.x();
        dy=originalImagePos.y();

//        qDebug()<<qPoint_MousePoint.x()<<";"<<qPoint_MousePoint.y()<<"qPoint_MousePoint"<<endl;
//       qDebug()<<originalImagePos.x()<<";"<<originalImagePos.y()<<"originalImagePos"<<endl;


        qPoint_originalImagePoint[btnGroupFruits.checkedId()]=originalImagePos;
        qDebug()<<qPoint_originalImagePoint[btnGroupFruits.checkedId()].x()
                <<";"<<qPoint_originalImagePoint[btnGroupFruits.checkedId()].y()
                 <<"qPoint_originalImagePoint["<<btnGroupFruits.checkedId()<<"]"<<endl;

        update();
    }
//放大图像：
    x1=X_ENLARGE;
    y1=Y_ENLARGE;
    w1=WIDTH_ENLARGE;
    h1=HEIGHT_ENLARGE;

    qrect_temp.setX(x1);
    qrect_temp.setY(y1);
    qrect_temp.setWidth(w1);
    qrect_temp.setHeight(h1);

    if((qPoint_MousePoint1.x()>=qrect_temp.x())             //获取放大图像的点
            &&(qPoint_MousePoint1.y()>=qrect_temp.y())
            &&(qPoint_MousePoint1.x()<=(qrect_temp.x()+qrect_temp.width()))
            &&(qPoint_MousePoint1.y()<=(qrect_temp.y()+qrect_temp.height())))
    {
         qPoint_MousePoint=event->pos();
         enlargedImagePoint.setX(qPoint_MousePoint.x()-x1-w1/2);
         enlargedImagePoint.setY(qPoint_MousePoint.y()-y1-h1/2);//放大点的中心距离

         dx=originalImagePos.x()+enlargedImagePoint.x()/w1*SQUARE_LENGTH;
         dy=originalImagePos.y()+enlargedImagePoint.y()/w1*SQUARE_LENGTH;


         qPoint_originalImagePoint[btnGroupFruits.checkedId()].setX(dx);
         qPoint_originalImagePoint[btnGroupFruits.checkedId()].setY(dy);
         qDebug()<<qPoint_originalImagePoint[btnGroupFruits.checkedId()].x()
                 <<";"<<qPoint_originalImagePoint[btnGroupFruits.checkedId()].y()
                  <<"qPoint_originalImagePoint["<<btnGroupFruits.checkedId()<<"]"<<endl;
           update();
    }




}

void CArmWidget::enlargePic(const QPoint originalImagePos1, int width, int height)
{
   if(originalImagePos1.x() >= 0)//如果打开了原始图片文件
    {

       if((originalImagePos1.x()-SQUARE_LENGTH/2)<0)//如果选择的放大图片点小于选择方框，就偏移选择放大点
       {
           double dtx=originalImagePos1.x()+SQUARE_LENGTH/2;//坐标
           originalImagePos.setX(dtx);

       }
       if((originalImagePos1.x()+SQUARE_LENGTH/2)>(WIDTH_OPENPICTURE))
       {
           double dtx=originalImagePos1.x()-SQUARE_LENGTH/2;
           originalImagePos.setX(dtx);
       }

       if((originalImagePos1.y()-SQUARE_LENGTH/2)<0)
       {
           double dty=originalImagePos1.y()+SQUARE_LENGTH/2;
           originalImagePos.setY(dty);
       }
       if((originalImagePos1.y()+SQUARE_LENGTH/2)>(HEIGHT_OPENPICTURE))
       {
           double dty=originalImagePos1.y()-SQUARE_LENGTH/2;
           originalImagePos.setY(dty);
       }

        QPixmap imgTemp;
        imgTemp = OpenPiture.copy
                (QRect(QPoint(originalImagePos.x()-SQUARE_LENGTH/2, originalImagePos.y()-SQUARE_LENGTH/2),
                        QSize(width, height)));//局部截图,
     //   imgTemp.save("enlarge.jpg");
        EnlargedPicture = imgTemp.scaled
                (WIDTH_ENLARGE,HEIGHT_ENLARGE);//放大采集的图片,参数是放大后的尺寸
    }

}

void CArmWidget::MeasureLength(QPoint qPoint[4])
{
    double LenthReference=ui->textEditReferenceValue->toPlainText().toDouble();
    double lenth1_2,lenth3_4,lenth;
    for(int i=0;i<4;i++)
    {
        if(qPoint[i].x()<0 && qPoint[i].y()<0)
        {
            return;
        }
    }
    if(LenthReference!=0)
    {
    lenth1_2=Distance_Point(qPoint[0],qPoint[1]);
    lenth3_4=Distance_Point(qPoint[2],qPoint[3]);
    lenth=LenthReference/lenth1_2*lenth3_4;
    ui->textBrowserMeasureValue->setText(QString::number(lenth));
    }

}



double  CArmWidget::Distance_Point(QPointF StartPoint,QPointF EndPoint)//计算两点之间距离
{
    double dDistPointTemp;
    dDistPointTemp=sqrt(pow((StartPoint.x()-EndPoint.x()), 2) + pow((StartPoint.y()-EndPoint.y()), 2));
    return dDistPointTemp;
}

double CArmWidget::Angle_Point(QPointF Line1,QPointF Line2)
{
    double angle,angle_1,angle_2;
    if(Line1.x() == 0.0)
    {
        angle_1 = 90;
    }
    else
    {
        angle_1 = qAtan2(Line1.y(),Line1.x());

    }
    if(Line2.x() == 0.0)
    {
        angle_2 =90;
    }
    else
    {
        angle_2 = qAtan2(Line2.y(),Line2.x());

    }
    angle = abs((angle_1-angle_2)/PI*180);
    if(angle>180)
    {
        angle -= 180;
    }
    if(angle>90)
    {
        angle =180-angle;
    }
    return angle;

}

void CArmWidget::calculateAngle()
{
    if(qPoint_originalImagePoint[0].x() == 0 )
        return;
    if(qPoint_originalImagePoint[1].x() == 0 )
        return;
    double x = qPoint_originalImagePoint[1].x() - qPoint_originalImagePoint[0].x();
    double y = qPoint_originalImagePoint[1].y() - qPoint_originalImagePoint[0].y();
    double theta = atanl(x/y);
    ui->label_Rz->setText(QString("%1").arg(theta  * 180 /PI));

    double referenceLength_B,referenceLength_Ankle;
    referenceLength_Ankle = ui->lineEdit_ankle->text().toDouble();
    referenceLength_B = ui->lineEdit_B->text().toDouble();
    if(referenceLength_Ankle == 0 || referenceLength_B == 0)
        return;

    double dis_ReferencePix = Distance_Point(qPoint_originalImagePoint[0] , qPoint_originalImagePoint[1]);
    if(qPoint_originalImagePoint[2].x() != 0 && qPoint_originalImagePoint[3].x() != 0)
    {
       QPoint line1 = (qPoint_originalImagePoint[0] - qPoint_originalImagePoint[1]);
       QPoint line2 = (qPoint_originalImagePoint[2] - qPoint_originalImagePoint[3]);
        double dis_Pix1 = (line2.x() * line1.x() + line1.y() * line2.y())
                /Distance_Point(qPoint_originalImagePoint[0],qPoint_originalImagePoint[1]);
        double dis_length1 = dis_Pix1 / dis_ReferencePix * referenceLength_B;
        double theta1 = atanl(dis_length1 / referenceLength_Ankle);
        ui->label_Ry->setText(QString("%1").arg(theta1  * 180 /PI));
    }
    if(qPoint_originalImagePoint[4].x() != 0 && qPoint_originalImagePoint[5].x() != 0)
    {

        QPoint line1 = (qPoint_originalImagePoint[0] - qPoint_originalImagePoint[1]);
        QPoint line2 = (qPoint_originalImagePoint[4] - qPoint_originalImagePoint[5]);
         double dis_Pix2 = (line2.x() * line1.x() + line1.y() * line2.y())
                 /Distance_Point(qPoint_originalImagePoint[0],qPoint_originalImagePoint[1]);
        double dis_length2 = dis_Pix2 / dis_ReferencePix * referenceLength_B;
        double theta2 = atanl(dis_length2 / referenceLength_Ankle);
        ui->label_Rx->setText(QString("%1").arg(theta2 * 180 /PI));
    }
}


void CArmWidget::on_textEditReferenceValue_textChanged()
{
    MeasureLength(qPoint_originalImagePoint);
}



void CArmWidget::on_pushButton_calculate2_clicked()
{
    double x,y,theta;
    x = ui->lineEdit_line1->text().toDouble();
    y = ui->lineEdit_line2->text().toDouble();
    theta = atanl(x/y) * 180 / PI;
    ui->label_result2_2->setText(QString("%1").arg(theta));

}

void CArmWidget::matrix_2_axisangle(const Matrix3d &m, double AxisAngle[3])
{
    double angle = 0;
    double temp1 = 0;
    double temp2 = 0;
    double temp3 = 0;
    double x =0;
    double y =0;
    double z =0;

    //need to be modified later
    double epsilon1 = 0.01;
    double epsilon2 = 0.1;
    //end

    /*singularity found,first check for identity matrix which must have +1 for all terms
      in leading diagonaland zero in other terms
    */

    if ((abs(m(0,1)-m(1,0))< epsilon1)
        && (abs(m(0,2)-m(2,0))< epsilon1)        //矩阵对称性检查（angle为0°或180°时矩阵为对称阵）
        && (abs(m(1,2)-m(2,1))< epsilon1))
        /*singularity found,first check for identity matrix which must have +1 for all terms
                     in leading diagonaland zero in other terms
        */

    {
        if ((abs(m(0,1)+m(1,0)) < epsilon2)
            && (abs(m(0,2)+m(2,0)) < epsilon2)
            && (abs(m(1,2)+m(2,1)) < epsilon2)
            && (abs(m(0,0)+m(1,1)+m(2,2)-3) < epsilon2))   //m近似为单位矩阵

        {
            for(int i = 0; i < 3; i++)
            {
                AxisAngle[i] = 0;             //等效转角angle为0°

            }
            return;
        }


        // otherwise this singularity is angle = 180
        angle = PI;
        double xx = (m(0,0)+1)/2;
        double yy = (m(1,1)+1)/2;
        double zz = (m(2,2)+1)/2;
        double xy = (m(0,1)+m(1,0))/4;
        double xz = (m(0,2)+m(2,0))/4;
        double yz = (m(1,2)+m(2,1))/4;

        if ((xx > yy) && (xx > zz))
        { // m(0,0) is the largest diagonal term
            if (xx< epsilon1)
            {
                x = 0;
                y = 0.7071;
                z = 0.7071;
            }
            else
            {
                x = sqrt(xx);
                y = xy/x;
                z = xz/x;
            }
        }
        else if (yy > zz)
        {
            // m(1,1) is the largest diagonal term
            if (yy< epsilon1)
            {
                x = 0.7071;
                y = 0;
                z = 0.7071;
            }
            else
            {
                y = sqrt(yy);
                x = xy/y;
                z = yz/y;
            }
        }
        else
        { // m(2,2) is the largest diagonal term so base result on this
            if (zz< epsilon1)
            {
                x = 0.7071;
                y = 0.7071;
                z = 0;
            }
            else
            {
                z = sqrt(zz);
                x = xz/z;
                y = yz/z;
            }
        }
        // return 180 deg rotation
        AxisAngle[0] = x*PI;
        AxisAngle[1] = y*PI;
        AxisAngle[2] = z*PI;
        return;
    }


    temp1 = pow((m(2,1)-m(1,2)),2) + pow((m(0,2)-m(2,0)),2) + pow((m(1,0)-m(0,1)),2);
    temp1 = sqrt(temp1);   // tmp1 = 2*sin(angle)    根据公式2.80中矩阵元素对称性可以计算出sin(angle)

    if (abs(temp1) < 0.001)
        temp1 = 1;
    // prevent divide by zero, should not happen if matrix is orthogonal and should be
    // caught by singularity test above, but I've left it in just in case
    angle = acos((m(0,0) + m(1,1) + m(2,2) - 1) / 2);

    x = (m(2,1) - m(1,2))/temp1;
    y = (m(0,2) - m(2,0))/temp1;
    z = (m(1,0) - m(0,1))/temp1;   //参考《机器人学导论》英文版第3版 P48 公式2.82
    AxisAngle[0] = x*angle;
    AxisAngle[1] = y*angle;
    AxisAngle[2] = z*angle;
}

void CArmWidget::matrix_2_Rotate(const Matrix3d &m, double AxisAngle[])
{
   AxisAngle[2] = atanl(m(1,0) / m(0,0));
   AxisAngle[1] = atanl(-(m(2,0)) / (m(0,0) *cosl(AxisAngle[2]) +m(1,0) * sinl(AxisAngle[2])) );
   AxisAngle[0] = atanl( m(0,2) *sinl(AxisAngle[2])-m(1,2) * cosl(AxisAngle[2])/
            (m(1,1) *cosl(AxisAngle[2]) - m(0,1) *sinl(AxisAngle[2])));
}

void CArmWidget::axisangle_2_matrix(const double AxisAngle[3], Matrix3d &m) //使用Eigen矩阵库
{
    double angle = 0;
    double c = 0;
    double s = 0;
    double t = 0;
    double x = 0;
    double y = 0;
    double z = 0;

    for(int i =0 ; i < 3; i++)
    {
        angle += AxisAngle[i] * AxisAngle[i];
    }
    angle = sqrt(angle); //计算等效转角angle

    x = AxisAngle[0] / angle;
    y = AxisAngle[1] / angle;    // (x,y,z)为单位向量
    z = AxisAngle[2] / angle;

    c = cos(angle);
    s = sin(angle);
    t = 1-c;

    m(0,0) = t*x*x + c;
    m(0,1) = t*x*y - z*s;
    m(0,2) = t*x*z + y*s;
    m(1,0) = t*x*y + z*s;
    m(1,1) = t*y*y + c;         //参考《机器人学导论》英文版第3版 P47 公式2.80
    m(1,2) = t*y*z - x*s;
    m(2,0) = t*x*z - y*s;
    m(2,1) = t*y*z + x*s;
    m(2,2) = t*z*z + c;
}


void CArmWidget::on_lineEdit_B_textChanged(const QString &arg1)
{
    calculateAngle();
}

void CArmWidget::on_lineEdit_ankle_textChanged(const QString &arg1)
{
    calculateAngle();
}

