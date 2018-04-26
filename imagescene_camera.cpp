#include "imagescene_camera.h"
#include "QDebug"

imagescene_camera::imagescene_camera(QObject *parent): QGraphicsScene(parent)
{
    camera = new cv::VideoCapture;
    camTimer = new QTimer();
    cameraCount = countCameras();
   // cameraCount = 0;
    CameraPix = new QGraphicsPixmapItem();
    CameraPix->setPos(0,0);
    this->addItem(CameraPix);

    fc <<  1268.034480283278500 , 1276.666036280597200;
    cc <<  670.565833828430530 , 362.885608061998200;
    alpha_c = 0;
    kc.resize(5);
    kc(0) = 0.071056317914753;
    kc(1) = -0.151398783760712;
    kc(2) = -0.000626556538805;
    kc(3) = 0.012567480504458;
    kc(4) = 0.000000000000000;

	T_CameraMarker2Camera_Calib << -0.5101, - 0.0747, - 0.7881,  881.1718,
									-0.1047 ,- 0.9535 ,   0.0828 , 402.1091,
									-0.7856 ,   0.1007,   0.4639,  498.5174,
									0  ,       0  ,       0  ,  1.0000;
    T_Camera_Calib2CameraMarker = T_CameraMarker2Camera_Calib.inverse();
    cameraPos.setZero(4,4);
    TipPos.setZero(4);


}

imagescene_camera::~imagescene_camera()
{
    delete camera;
}

bool imagescene_camera::OpenCamera(int index)
{
    if(index < 0 )
        index = 0;
    cam_index = index;
    bool ret = camera->open(index);
    if(ret)
    {
        camTimer->start(50);
        connect(camTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    }
    return ret;
}

void imagescene_camera::CloseCamera()
{
    delete camera;
}

int imagescene_camera::countCameras()
{
    int maxTested = 10;
    for (int i = 0; i < maxTested; i++){
        cv::VideoCapture temp_camera(i);
        bool res = (!temp_camera.isOpened());
        temp_camera.release();
        if (res)
        {
            return i;
        }
    }
    return maxTested;
}



void imagescene_camera::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

}

void imagescene_camera::timerSlot()
{
    camera->retrieve(camImage); //获取一帧图像
    if(!camImage.empty())
    {
        cv::cvtColor(camImage, camImage, cv::COLOR_BGR2GRAY);
        if(isCameraSee)
        {
            Vector2d Pos2D = CalculateProjection(TipPos,cameraPos);
            cv::Point pt((int)Pos2D(0),(int)Pos2D(1));
            qDebug() <<   "Pos2D" << Pos2D(0) << "," << Pos2D(1);
            if(Pos2D(0) <= (camImage.size)[0] &&
                    Pos2D(0) >= 0 &&
                    Pos2D(1) <= (camImage.size)[1] &&
                    Pos2D(0) >= 0)
            drawMarker(camImage,pt,Scalar(255));
        }
        QImage disImage = cvMat2QImage(camImage);
        CameraPix->setPixmap(QPixmap::fromImage(disImage).scaled(CameraHeight,CameraWidth));
    }
    update();
}

QImage imagescene_camera::cvMat2QImage(const Mat &mat)
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
        //qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    }
    else
    {
       // qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

Vector2d imagescene_camera::CalculateProjection(Vector4d Pos,Matrix4d T_Cam)
{

    //参考www.vision.caltech.edu/bouguetj/calib_doc/htmls/parameters.html
    Vector4d PosinCamear_calib = T_Camera_Calib2CameraMarker * T_Cam.inverse()* Pos;

    Vector2d Xn;
    Xn(0) = PosinCamear_calib(0) / PosinCamear_calib(2);
    Xn(1) = PosinCamear_calib(1) / PosinCamear_calib(2);

    double r2 = Xn(0)*Xn(0) + Xn(1)*Xn(1);
    Vector2d Xd,dx;
    dx(0) = 2 * kc(2) * Xn(0) * Xn(1) + kc(3) * (r2 + 2 * Xn(0) * Xn(0));
    dx(1) = kc(2) * (r2 + 2 * Xn(1) * Xn(1)) + 2 * kc(3) * Xn(0) * Xn(1);
    Xd = (1 + kc(0)*r2 + kc(1) * r2*r2 +kc(4) * r2*r2*r2) * Xn + dx;
    Vector2d x_pixel;
    x_pixel(0) = fc(0) * (Xd(0) * alpha_c * Xd(1)) + cc(0);
    x_pixel(1) = fc(1) * Xd(1) + cc(1);
    return x_pixel;
}
