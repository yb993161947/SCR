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

protected:
    void paintEvent(QPaintEvent* event);
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

    void on_checkBox_removeCircle_toggled(bool checked);

    void on_radioButton_source_toggled(bool checked);

    void on_radioButton_refined_toggled(bool checked);

private:
    Ui::CaptureVideoWidget* ui;
    int cam_index;
    QList<Eigen::Vector3d> xSpotPoints3D;
    QList<double> transparams;
};

#endif // CAPTUREVIDEOWIDGET_H
