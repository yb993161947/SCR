#include "capturevideowidget.h"
#include "QFileDialog.h"
#include "carm/DxPoint.h"
#include "carm/DxSpatialMatching.h"
#include "carm/ImageRectify.h"
#include "ui_capturevideowidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <cstring>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <fstream>
#include <sstream>
#include<algorithm>  





CaptureVideoWidget::CaptureVideoWidget(QWidget* parent)
: QWidget(parent), ui(new Ui::CaptureVideoWidget), cam_index(0), camera(new cv::VideoCapture)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    camTimer = new QTimer();
    connect(camTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    connect(ui->widget_lasso, SIGNAL(finished()), this, SLOT(lassoHandler()));
    selectedIndex = 0;
    for(int i = 0 ; i < 9 ;i ++)
    {
        _2DPt[i] = QPointF(0,0);
    }
	ui->label_Picture->raise();

    Marker1ToXspot<<
            0.9999,0.0008,-0.0003,14.81733179,
            -0.0146,-0.9998,-0.0182,-26.91508238,
            0,	0.0182,	-0.9997,-0.77761967,
            0,	0,	0,	1;

    Marker2ToXspot <<
            -1	,0.0056	,-0.0003,-15.31207789,
            0.0011,	-0.9999,-0.0087,-27.07246304,
            -0.0003,-0.0087,0.9999,-0.63725643,
            0,	0,	0,	1;

    Marker1ToMarker2<<
        0.766044443,0,-0.64278761,35.75,
        0,1,0,0,
        0.64278761,0,0.766044443,98.25,
        0,0,0,1;
	XSpotPts3DonMarker1.resize(8,3);

	//时间7_15Marker1标定?orMarker2(有错误)
    //XSpotPts3DonMarker1<<
		 //46.12,-25.61,9.06,
   //      46.12,29.39,9.06,
   //      64.24,4.39,58.86,
   //      64.24,15.61,58.86,
   //      -3.01,-40.00,5.65,
   //      22.37,-40,31.53,
   //      53.14, 40,57.58,
   //      14.45, 40,112.10;

		//时间7_16Marker1标定
	XSpotPts3DonMarker1 <<
		65.27, -25.61,  -61.67,
		65.27, 29.39, -61.67,
		47.15, 4.39, -11.86,
		47.15, -15.61, -11.86,
		29.83, -40.00, -95.85,
		32.64, -40.00, -59.71,
		39.46, 40.00, -19.98,
		-25.22, 40.00, -3.09;



}

CaptureVideoWidget::~CaptureVideoWidget()
{
    if(camera->isOpened())
        camera->release();
    delete camera;
    delete ui;
}

void CaptureVideoWidget::on_pushButton_Exit_released() //退出
{
    QMessageBox msgBox;

    msgBox.setText(u8"询问: 确定关闭程序吗？");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

    switch(ret)
    {
    case QMessageBox::Yes:
        // Yes was clicked
        this->close();
    case QMessageBox::No:
        break;
    default:
        // should never be reached
        break;
    }
}

void CaptureVideoWidget::on_pushButton_OpenVideo_released() //打开设备打开
{
	ui->widget_lasso->raise();
    if(!openCamera()) //打开视频
    {
        QMessageBox::warning(this, u8"打开设备失败", u8"未找到视频设备", QMessageBox::Ok);
    }
}

void CaptureVideoWidget::on_pushButton_Capture_released() //采集图片
{
	ui->label_Picture ->raise();
    closeCamera();
    camImage.copyTo(original_image);
    displaySrcImage();
    ui->widget_lasso->start();
}

bool CaptureVideoWidget::openCamera() //打开摄像头
{
    bool ret = camera->open(cam_index);
    if(ret)
    {
        camTimer->start(50);
    }
    return ret;
}

void CaptureVideoWidget::closeCamera()
{
    camTimer->stop();
    if(camera != nullptr && camera->isOpened())
    {
        camera->release();
    }
}
void CaptureVideoWidget::timerSlot()
{
    camera->retrieve(camImage); //获取一帧图像
    if(!camImage.empty())
    {
        cv::cvtColor(camImage, camImage, cv::COLOR_BGR2GRAY);
        QImage disImage = cvMat2QImage(camImage);
        ui->label_Picture->setPixmap(QPixmap::fromImage(disImage));
    }
    update();
}

void CaptureVideoWidget::lassoHandler()
{
    QRect resized;
    resized.setX(ui->widget_lasso->getSelection().left() * original_image.cols / ui->widget_lasso->width());
    resized.setY(ui->widget_lasso->getSelection().top() * original_image.rows / ui->widget_lasso->height());
    resized.setWidth(ui->widget_lasso->getSelection().width() * original_image.cols /
                     ui->widget_lasso->width());
    resized.setHeight(ui->widget_lasso->getSelection().height() * original_image.rows /
                      ui->widget_lasso->height());
    cv::Rect roi;
    roi.x = resized.left();
    roi.y = resized.top();
    roi.width = resized.width();
    roi.height = resized.height();
    original_image(roi).copyTo(original_image);
    displaySrcImage();
}

void CaptureVideoWidget::displaySrcImage()
{
    ui->label_Picture->setPixmap(QPixmap::fromImage(cvMat2QImage(original_image)));
}


QImage CaptureVideoWidget::cvMat2QImage(const cv::Mat& mat)
{

    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar* pSrc = mat.data;
        for(int row = 0; row < mat.rows; row++)
        {
            uchar* pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

void CaptureVideoWidget::pushXSpot3DCoordinates(const QList<Vector3d>& input)
{
    xSpotPoints3D.clear();
    for(int i = 0; i < qMin(input.length(), 12); i++)
    {
        xSpotPoints3D << input[i];
    }
}

QList<double> CaptureVideoWidget::getPinHoleParameters() { return transparams; }

QImage CaptureVideoWidget::getCaputuredImage() { return cvMat2QImage(original_image); }

QImage CaptureVideoWidget::getRifinedImage(bool removeCircles)
{
    if(removeCircles)
    {
        return cvMat2QImage(refined_image_nopoints);
    }
    else
    {
        return cvMat2QImage(refined_image);
    }
}

void CaptureVideoWidget::caculateParam(vector<QPointF> ver_2DPt, MatrixXd XSpotPts3DonMarker1, QList<double> &transparams)
{
    transparams.clear();
    int nCount = ver_2DPt.size();
    nCount *=2;
    MatrixXd XTemp = MatrixXd(nCount, 12);
    MatrixXd X= MatrixXd(nCount, 11);

    VectorXd imgx = VectorXd(nCount);
    VectorXd wx = VectorXd(11);
	MatrixXd XSpotPts3D_temp;
	XSpotPts3D_temp.resize(XSpotPts3DonMarker1.rows(), XSpotPts3DonMarker1.cols());
	for (int i = 0; i < XSpotPts3DonMarker1.rows(); i++)
	{
		Vector4d vec4d; 
		vec4d << XSpotPts3DonMarker1(i,0), XSpotPts3DonMarker1(i, 1), XSpotPts3DonMarker1(i, 2),1;
		XSpotPts3D_temp.row(i) = (Marker1ToXspot * vec4d).head(3);
	}
    nCount = 0;
    for ( int i = 0; i < ver_2DPt.size(); i++) {
        if(ver_2DPt[i] == QPointF(0,0) )
        {
            XTemp.row(nCount) = MatrixXd::Zero(1,12);
            nCount++;
            XTemp.row(nCount) = MatrixXd::Zero(1,12);
            nCount++;
            continue;
        }
        XTemp.row(nCount) << XSpotPts3D_temp(i,0), XSpotPts3D_temp(i,1), XSpotPts3D_temp(i,2),1,-XSpotPts3D_temp(i,0)*ver_2DPt[i].x(),
            -XSpotPts3D_temp(i,1)*ver_2DPt[i].x(),-XSpotPts3D_temp(i,2)*ver_2DPt[i].x(),0,0,0,0,ver_2DPt[i].x();
        nCount++;
        XTemp.row(nCount) << 0,0,0,0,-XSpotPts3D_temp(i,0)*ver_2DPt[i].y(),-XSpotPts3D_temp(i,1)*ver_2DPt[i].y(),-XSpotPts3D_temp(i,2)*ver_2DPt[i].y(),
			XSpotPts3D_temp(i,0), XSpotPts3D_temp(i,1), XSpotPts3D_temp(i,2),1,ver_2DPt[i].y();
        nCount++;
    }
    X <<XTemp.col(0),
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
        transparams.push_back(wx[i]);
    }
}

void CaptureVideoWidget::paintPt()
{
    cv::Mat mat_image;
    if(ui->radioButton_source->isChecked())
    {
        ui->radioButton_source->setChecked(true);
        mat_image = original_image;
    }

    else if(ui->radioButton_refined->isChecked())
    {
        ui->radioButton_refined->setChecked(true);
        if(ui->checkBox_removeCircle->isChecked())
        {
           ui->checkBox_removeCircle->setChecked(true);
           mat_image = refined_image_nopoints;
        }
        else
        {
           mat_image = refined_image;
        }
    }

    if (mat_image.size[0] != 0)
    {
        QPixmap pix = QPixmap::fromImage(cvMat2QImage(mat_image));
        QPainter p(&pix);
        p.setPen(QPen(Qt::red, 3, Qt::SolidLine));
        QFont font("Arial", 20, QFont::Bold, true);
        p.setFont(font);
        for (int i = 0; i < 9; i++)
        {
            if (_2DPt[i].x() == 0)
                continue;
            p.drawLine(_2DPt[i] + QPoint(-10, 0), _2DPt[i] + QPoint(10, 0));
            p.drawLine(_2DPt[i] + QPoint(0, -10), _2DPt[i] + QPoint(0, 10));
            p.drawEllipse(_2DPt[i], 10, 10);
            p.drawText(QRect(_2DPt[i].x() + 10 , _2DPt[i].y() - 10 , 40,40), QString("%1").arg(i+1));
        }
        p.end();
        ui->label_Picture->setPixmap(pix.scaled(ui->label_Picture->width(), ui->label_Picture->height()));
        update();
    }
}

void CaptureVideoWidget::paintEvent(QPaintEvent* event)
{
    //QStyleOption opt;
    //opt.init(this);

 //   style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	//QWidget::paintEvent(event);

}

void CaptureVideoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    if(pos.x() > ui->label_Picture->pos().x() &&
            pos.y() > ui->label_Picture->pos().y() &&
            pos.x() < ui->label_Picture->pos().x() +ui->label_Picture->width() &&
            pos.y() < ui->label_Picture->pos().y() +ui->label_Picture->height())
    {	
		
        if(selectedIndex != 0)
        {
			float radio_w = float(ui->label_Picture->width()) / original_image.cols;
			float radio_h = float(ui->label_Picture->height()) / original_image.rows;

            if(ui->radioButton_findPt->isChecked())
            {
                if (XSpotPts2D.size() != 0 && original_image.size[0] != 0)
                {
                    int *dis;
                    dis = (int *)malloc(XSpotPts2D.size() * sizeof(int));
                    for (auto i = 0; i < XSpotPts2D.size(); i++)
                    {
                        dis[i] = abs(XSpotPts2D[i][0]*radio_w - pos.x() + ui->label_Picture->pos().x())
                                + abs(XSpotPts2D[i][1]*radio_h - pos.y() + ui->label_Picture->pos().y());
                    }
                    int min = *std::min_element(dis, dis + XSpotPts2D.size());
                    if (min < 80)
                    {
                        int itr = std::find(dis, dis + XSpotPts2D.size(), min) - dis;
                        pos.setX(XSpotPts2D[itr][0] * radio_w + ui->label_Picture->pos().x());
                        pos.setY(XSpotPts2D[itr][1] * radio_h + ui->label_Picture->pos().y());
                    }
                }
            }

            _2DPt[selectedIndex - 1].setX( float(pos.x()- ui->label_Picture->pos().x()) / radio_w);//原始图像坐标
            _2DPt[selectedIndex - 1].setY( float(pos.y()- ui->label_Picture->pos().y()) / radio_h);

            paintPt();
        }
    }


}

void CaptureVideoWidget::on_pushButton_OpenImage_clicked()
{
    closeCamera();
    //判断是什么图片文件
    char* filename;

    QString FilePath = QFileDialog::getOpenFileName(nullptr, u8"打开图片");

    QByteArray ba = FilePath.toLatin1(); // QString转为char*
    filename = ba.data();

    char* prefix;
    size_t filename_length = strlen(filename); // length ()
    // int filename_length=filename.length();//
    prefix = filename + filename_length - 3; //获得后三位字符

    if(strcmp(prefix, "IMA") == 0 || strcmp(prefix, "dcm") == 0) //判断是什么文件
    {
        DicomImage img(FilePath.toLocal8Bit().data());

        cv::Mat(int(img.getWidth()), int(img.getHeight()), CV_16U, (uint16_t*)img.getOutputData(16)).copyTo(original_image);
        double maxVal;
        cv::minMaxLoc(original_image, nullptr, &maxVal);
        original_image.convertTo(original_image, CV_8UC1, 256.0 / maxVal);
        QImage qimg = cvMat2QImage(original_image);

        ui->label_Picture->setPixmap(QPixmap::fromImage(qimg));
    }
    else if(strcmp(prefix, "BMP") == 0 || strcmp(prefix, "bmp") == 0 ||
            strcmp(prefix, "JPG") == 0 || strcmp(prefix, "jpg") == 0)
    {
        original_image = cv::imread(string(FilePath.toLocal8Bit()), CV_LOAD_IMAGE_GRAYSCALE);
        if(original_image.type() != CV_8UC1)
        {
            double maxVal;
            cv::minMaxLoc(original_image, nullptr, &maxVal);
            original_image.convertTo(original_image, CV_8UC1, 256.0 / maxVal);
        }
        QImage qimg;
        qimg.load(FilePath);
        ui->label_Picture->setPixmap(QPixmap::fromImage(qimg));
    }
    else
    {
        // cout<<"unrecognized format";
        return;
    }
}

void CaptureVideoWidget::on_pushButton_Process_clicked()
{
    //纠正图像变形

    DxImageRectify rectifier;  //图像矫正

	rectifier.AdjustImage_(original_image, refined_image, refined_image_nopoints); //图像纠正
	XSpotPts2D.clear();
	rectifier.GetxSPotPt(XSpotPts2D);

    ui->checkBox_removeCircle->setChecked(true);
    ui->radioButton_findPt->setChecked(true);
    paintPt();
    update();
//    ui->label_Picture->setPixmEap(QPixmap::fromImage(cvMat2QImage(refined_image_nopoints)));



}

void CaptureVideoWidget::on_pushButtonCalculate_clicked()
{
	if (XSpotPts2D.size() < 6)
	{
		QMessageBox::warning(this, u8"识别失败", u8"特征点过少");
		emit processFinished(false);
	}
	//xspot计算
	////把点信息输入SpatialMatcher
	//DxSpatialMatching matcher; // 2D-3D配准
	//QVector<DxPoint> pts2d, pts3d;
	//for(int i = 0; i < qMin(12, xSpotPoints3D.length()); i++)
	//{
	//    DxPoint pt;
	//    pt.SetX(xSpotPoints3D[i](0));
	//    pt.SetY(xSpotPoints3D[i](1));
	//    pt.SetZ(xSpotPoints3D[i](2));
	//    pts3d.push_back(pt);
	//}
	//for(int i = 0; i < XSpotPts2D.size(); i++)
	//{
	//    DxPoint pt;
	//    pt.SetX(XSpotPts2D[i][0]);
	//    pt.SetY(XSpotPts2D[i][1]);
	//    pts2d.push_back(pt);
	//}
	//if(!matcher.PushAllPointInfo(pts3d, pts2d))
	//{
	//    QMessageBox::warning(this, u8"识别失败", u8"XSpot投影参数计算失败,无法得到有效的针孔模型。");
	//     emit processFinished(false);
	//}
	////取出11个参数
	//transparams = matcher.GetxSpotMatrix().toList();

	//自己做的Xspot
	vector<QPointF> ver_2DPt;
	ver_2DPt.resize(8);
	for (int i = 0; i < 8; i++)
	{
		ver_2DPt[i] = _2DPt[i];
	}
	caculateParam(ver_2DPt, XSpotPts3DonMarker1, transparams);

	QString path = QApplication::applicationDirPath();
	path += "/DataDocument";
	QDir dir;
	dir.mkpath(path);
	path += "/param11.txt";
	QFile file(path);
	file.open(QFile::WriteOnly);
	for (int i = 0; i < transparams.size(); i++)
	{
		if (i == transparams.size() - 1)
		{
			file.write(QString("%1").arg(transparams[i]).toLocal8Bit());
		}
		else
		{
			file.write(QString("%1,").arg(transparams[i]).toLocal8Bit());
		}
	}
	file.close();
	emit processFinished(true);
}

void CaptureVideoWidget::on_checkBox_removeCircle_toggled(bool checked)
{
    if(checked)
    {
        ui->label_Picture->setPixmap(QPixmap::fromImage(cvMat2QImage(refined_image_nopoints)));
    }
    else
    {
        ui->label_Picture->setPixmap(QPixmap::fromImage(cvMat2QImage(refined_image)));
    }
}

void CaptureVideoWidget::on_radioButton_source_toggled(bool checked)
{
    if(checked)
        ui->label_Picture->setPixmap(QPixmap::fromImage(cvMat2QImage(original_image)));
}

void CaptureVideoWidget::on_radioButton_refined_toggled(bool checked)
{
    if(checked)
    {
        if(ui->checkBox_removeCircle->isChecked())
        {
            ui->label_Picture->setPixmap(QPixmap::fromImage(cvMat2QImage(refined_image_nopoints)));
        }
        else
        {
            ui->label_Picture->setPixmap(QPixmap::fromImage(cvMat2QImage(refined_image)));
        }
    }
}

void CaptureVideoWidget::on_radioButton_1_clicked()
{
    selectedIndex = 1;
}

void CaptureVideoWidget::on_radioButton_2_clicked()
{
    selectedIndex = 2;
}

void CaptureVideoWidget::on_radioButton_3_clicked()
{
    selectedIndex = 3;
}

void CaptureVideoWidget::on_radioButton_4_clicked()
{
    selectedIndex = 4;
}

void CaptureVideoWidget::on_radioButton_5_clicked()
{
    selectedIndex = 5;
}

void CaptureVideoWidget::on_radioButton_6_clicked()
{
    selectedIndex = 6;
}


void CaptureVideoWidget::on_radioButton_7_clicked()
{
    selectedIndex = 7;
}

void CaptureVideoWidget::on_radioButton_8_clicked()
{
    selectedIndex = 8;
}

void CaptureVideoWidget::on_radioButton_9_clicked()
{
    selectedIndex = 9;
}

void CaptureVideoWidget::on_radioButton_source_clicked()
{
    paintPt();
}

void CaptureVideoWidget::on_radioButton_refined_clicked()
{
    paintPt();
}

void CaptureVideoWidget::on_checkBox_removeCircle_clicked()
{
    paintPt();
}

void CaptureVideoWidget::on_pushButton_clicked()
{
    if(selectedIndex >= 0 && selectedIndex < 9)
    _2DPt[selectedIndex] =QPointF(0,0);
}
