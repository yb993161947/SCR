#ifndef IMAGESCENE_CAMERA_H
#define IMAGESCENE_CAMERA_H
#include "QGraphicsScene"
#include "QGraphicsPixmapItem"
#include "QTimer"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include "Eigen/Eigen"
using namespace cv;
using namespace Eigen;
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

        Vector2d CalculateProjection(Vector4d Pos,Matrix4d T_Cam);
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

        void setcameraPos(Matrix4d cam){cameraPos = cam;}
        void setTipPos(Vector4d tip){TipPos = tip; }
        void setCameraSee(bool flag){isCameraSee = flag;}
        cv::Mat getCameraImage(){return camImage;}
private:
        //摄像头
        QTimer* camTimer;
        cv::VideoCapture* camera;
        int cam_index;
        int cameraCount;
        cv::Mat camImage; //视频采集的图片

        //标定参数
        Vector2d fc;//Focal length
        Vector2d cc;//Principal point
        double alpha_c;//Skew coefficient
        VectorXd kc;//Distortion coefficients
        Matrix4d T_CameraMarker2Camera_Calib; //MarkerOnCamera 2 Cameara_CalibPos
        Matrix4d T_Camera_Calib2CameraMarker; //MarkerOnCamera 2 Cameara_CalibPos

        //相机输入
        Matrix4d cameraPos;
		Vector4d TipPos;
		
        bool isCameraSee;

 private slots:
        void timerSlot();

 signals:
        void doubleclicked1(QGraphicsScene *scene);
};

#endif // IMAGESCENE_CAMERA_H
