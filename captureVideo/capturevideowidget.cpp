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


CaptureVideoWidget::CaptureVideoWidget(QWidget* parent)
: QWidget(parent), ui(new Ui::CaptureVideoWidget), cam_index(0), camera(new cv::VideoCapture)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    camTimer = new QTimer();
    connect(camTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    connect(ui->widget_lasso, SIGNAL(finished()), this, SLOT(lassoHandler()));
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
    if(!openCamera()) //打开视频
    {
        QMessageBox::warning(this, u8"打开设备失败", u8"未找到视频设备", QMessageBox::Ok);
    }
}

void CaptureVideoWidget::on_pushButton_Capture_released() //采集图片
{
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

void CaptureVideoWidget::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
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
    DxSpatialMatching matcher; // 2D-3D配准
    DxImageRectify rectifier;  //图像矫正

    rectifier.AdjustImage(original_image, refined_image, refined_image_nopoints); //图像纠正


    vector<cv::Vec3f> XSpotPts2D; //图像上识别出的Xspot点
    rectifier.GetxSPotPt(XSpotPts2D);

    //把点信息输入SpatialMatcher
    QVector<DxPoint> pts2d, pts3d;
    for(int i = 0; i < qMin(12, xSpotPoints3D.length()); i++)
    {
        DxPoint pt;
        pt.SetX(xSpotPoints3D[i](0));
        pt.SetY(xSpotPoints3D[i](1));
        pt.SetZ(xSpotPoints3D[i](2));
        pts3d.push_back(pt);
    }
    for(int i = 0; i < XSpotPts2D.size(); i++)
    {
        DxPoint pt;
        pt.SetX(XSpotPts2D[i][0]);
        pt.SetY(XSpotPts2D[i][1]);
        pts2d.push_back(pt);
    }
    if(!matcher.PushAllPointInfo(pts3d, pts2d))
    {
        QMessageBox::warning(this, u8"识别失败", u8"XSpot投影参数计算失败,无法得到有效的针孔模型。");
         emit processFinished(false);
    }

    //取出11个参数
    transparams = matcher.GetxSpotMatrix().toList();

    QString path = QApplication::applicationDirPath();
    path += "/DataDocument";
    QDir dir;
    dir.mkpath(path);
    path += "/param11.txt";
    QFile file(path);
    file.open(QFile::WriteOnly);
    for(int i = 0; i < transparams.size(); i++)
    {
        if(i == transparams.size() - 1)
        {
            file.write(QString("%1").arg(transparams[i]).toLocal8Bit());
        }
        else
        {
            file.write(QString("%1,").arg(transparams[i]).toLocal8Bit());
        }
    }
    file.close();
    ui->radioButton_refined->setChecked(true);
    ui->checkBox_removeCircle->setChecked(true);
    ui->label_Picture->setPixmap(QPixmap::fromImage(cvMat2QImage(refined_image_nopoints)));


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
