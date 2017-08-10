  #ifndef IMAGESCENE_H
#define IMAGESCENE_H

#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QList>
#include <QPixmap>
#include <Eigen/Eigen>
#include <QVector4D>
#include <QVector>
#include <qlist.h>
#include<cv.hpp>
#include<core.hpp>
#include<highgui.hpp>
#include"needle.h"
	#define PI 3.141592654
namespace cv
{
    class Mat;
}

class ImageScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ImageScene(QObject *parent = Q_NULLPTR);
    static QImage cvMat2QImage(const cv::Mat &mat);

	//yb加
    cv::Mat originalImage;//原始图像
	QPixmap Pixmap_scr;   
	Eigen::Matrix4d MatrixXSpot;
    Eigen::Matrix4d MatrixTipTool;
	//YB改，将pixImage图像设为公有
	QGraphicsPixmapItem pixImage;
    QGraphicsPixmapItem pixImage_matching;


    public slots:
    void zoomIn(float ratio);
    void zoomOut(float ratio);
    void zoomInMatching(float ratio);
    void zoomOutMatching(float ratio);
    //void zoom(float ratio);
    void setPixImage(QPixmap Pix_Scr);
    void loadDCMImage(QString FilePath);
    void loadBMPImage(QString FilePath);
    void loadImage(cv::Mat Image);
    void loadMatchingImage(cv::Mat Image);
    void loadMatchingImage(QPixmap Pixmap);
    void saveImage(QString FilePath);

    void setmouseConnect(bool a);
    bool ismouseConnect()
    {
        return isOpenMouse;
    }

public:
    int index_selected;//判断选中的是哪个点
    QPointF Piximage_point[6];
    void selected_show();
    void selected_hide();

    void setMoveObj(int Obj);
    QGraphicsPixmapItem Piximage_button[6];
    QGraphicsPixmapItem Piximage_button_selected[6];
    QGraphicsLineItem *needle1;//针模型
    needle *Marker_Tip;
    virtual void show_otherItem();//响应鼠标事件点改变的虚函数
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void wheelEvent(QGraphicsSceneWheelEvent *wheelEvent) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) override;


	QVector<double> transparams;
    int chooseMoveObj;
	QPointF lastmatchingPos;

private:
    QPointF Pt3DtoPt2D(QVector3D pt3d);
	//YB改，将pixImage图像可由子类继承获取
    //QGraphicsPixmapItem pixImage;
    QPointF pressPoint;
    bool  movingImage;
    bool  movingMatchiingImage;
    QPointF getRotatePoint(QPointF Point , float rotate_Rad);

    bool isOpenMouse;

signals:
    void pointChanged(int index);



};

#endif // IMAGESCENE_H
