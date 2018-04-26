#ifndef IMAGESCENE_CAMERA_H
#define IMAGESCENE_CAMERA_H
#include "QGraphicsScene"
#include "QGraphicsPixmapItem"
#include "QTimer"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
using namespace cv;
class imagescene_camera : public QGraphicsScene
{
        Q_OBJECT
public:

        imagescene_camera(QObject *parent = Q_NULLPTR);
        ~imagescene_camera();
        QGraphicsPixmapItem *CameraPix;

        bool OpenCamera(int index);
        void CloseCamera();
        int countCameras();

        int getCameraCount()
        {
           return cameraCount;
        }
        qreal CameraHeight=500 ,CameraWidth =500;
        static QImage cvMat2QImage(const Mat &mat);

        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
        //摄像头
        QTimer* camTimer;
        cv::VideoCapture* camera;
        int cam_index;
        int cameraCount;
        cv::Mat camImage; //视频采集的图片
 private slots:
        void timerSlot();

 signals:
        void doubleclicked1(QGraphicsScene *scene);
};

#endif // IMAGESCENE_CAMERA_H
