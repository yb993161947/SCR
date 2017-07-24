#ifndef CAPTUREVIDEOWIDGET_H
#define CAPTUREVIDEOWIDGET_H

#include <Eigen/Eigen>
#include <QButtonGroup>
#include <QCommandLineParser>
#include <QLabel>
#include <QList>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QWidget>
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <QList>
using namespace std;
using namespace Eigen;


namespace Ui
{
class CaptureVideoWidget;
}

class CaptureVideoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CaptureVideoWidget(QWidget* parent = 0);
    ~CaptureVideoWidget();

    //采集图像操作的变量
    cv::Mat camImage; //视频采集的图片
    QTimer* camTimer;
    cv::VideoCapture* camera;
    cv::Mat original_image; // original image
    cv::Mat refined_image;
    cv::Mat refined_image_nopoints;

    //函数
    bool openCamera(); //打开摄像头
    void closeCamera();
    QImage cvMat2QImage(const cv::Mat& mat);
    void pushXSpot3DCoordinates(const QList<Eigen::Vector3d>& input);
    QList<double> getPinHoleParameters();
    QImage getCaputuredImage();
    QImage getRifinedImage(bool removeCircles);
    //鼠标选中点
    QPointF	 _2DPt[9];

	vector<cv::Vec3f> XSpotPts2D; //图像上识别出的Xspot点
    //vector<QPoint> XSpotPts2D_sort;
    //标定参数
    //模型的两个特征坐标系在两个贴的Makrer的位置
    Eigen::Matrix4d Marker1ToXspot;
    Eigen::Matrix4d Marker2ToXspot;

    //模型中心坐标2相对于模型中心坐z标1旋转了40度，位移（35.75，0,98.25）
    Eigen::Matrix4d Marker1ToMarker2;
    Eigen::MatrixXd XSpotPts3DonMarker1;

    void caculateParam(vector<QPointF> ver_2DPt, MatrixXd XSpotPts3DonMarker1 , QList<double> &transparams);
    void paintPt();
protected:
    void paintEvent(QPaintEvent* event);

    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void processFinished(bool issuccessfully);
private slots:

    void timerSlot();

    void lassoHandler();

    void displaySrcImage();

    void on_pushButton_Exit_released();

    void on_pushButton_OpenVideo_released();

    void on_pushButton_Capture_released();

    void on_pushButton_OpenImage_clicked();

    void on_pushButton_Process_clicked();

	void on_pushButtonCalculate_clicked();

    void on_checkBox_removeCircle_toggled(bool checked);

    void on_radioButton_source_toggled(bool checked);

    void on_radioButton_refined_toggled(bool checked);

    void on_radioButton_1_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

    void on_radioButton_9_clicked();

    void on_radioButton_source_clicked();

    void on_radioButton_refined_clicked();

    void on_checkBox_removeCircle_clicked();

    void on_pushButton_clicked();

private:
    Ui::CaptureVideoWidget* ui;
    int cam_index;
    QList<Eigen::Vector3d> xSpotPoints3D;
    QList<double> transparams;

    int selectedIndex;
};

#endif // CAPTUREVIDEOWIDGET_H
