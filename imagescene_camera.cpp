#include "imagescene_camera.h"


imagescene_camera::imagescene_camera(QObject *parent): QGraphicsScene(parent)
{
    camera = new cv::VideoCapture;
    camTimer = new QTimer();
    cameraCount = countCameras();
    CameraPix = new QGraphicsPixmapItem();
    CameraPix->setPos(0,0);
    this->addItem(CameraPix);
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

