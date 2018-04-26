#include "ImageScene.h"
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include <QImage>
#include <QPointF>
#include <dcmimage.h>
#include <opencv2/opencv.hpp>
#include <QVector3D>
#include <Eigen/LU>
#include <QMessageBox>
#include <QGraphicsLineItem>
#include <QVector>
#include <stdio.h>
#include <qgraphicseffect.h>
#include <qdebug.h>
//const QString XSpotMarkerName = "Marker_XSpot";
//const QString FemoralMarkerName = "Marker_TreatedFar";
//const QString TooltipMarkerName = QStringLiteral("Marker_Tip");
//const Eigen::Vector4d Tooltip_Position1(0.0, 0.0, -17.64, 1);
//const Eigen::Vector4d Tooltip_Position2(158.53, 0.87, -16.81, 1);
////x-bot 3D点
//const Eigen::Vector4d kXspot3DPt[12] = {
//    Eigen::Vector4d(353.5917295,-28.94508077,-58.35207327,1),
//    Eigen::Vector4d(350.457801,-33.334644,-88.32555342,1),
//    Eigen::Vector4d(347.1837796,-37.57368775,-118.639914,1),
//    Eigen::Vector4d(295.8181762,-34.59162595,-31.80863198,1),
//    Eigen::Vector4d(282.4332982,-40.8479307,-63.78963793,1),
//    Eigen::Vector4d(267.7006404,-47.70638125,-98.62438413,1),
//    Eigen::Vector4d(296.9313793,37.83713989,-48.21922192,1),
//    Eigen::Vector4d(286.5644333,42.54051603,-74.75168674,1),
//    Eigen::Vector4d(276.5781768,47.58420394,-101.5227552,1),
//    Eigen::Vector4d(343.6148427,33.11330516,-67.86624091,1),
//    Eigen::Vector4d(339.9296347,36.50701665,-92.54845644,1),
//    Eigen::Vector4d(336.1567828,39.58543792,-116.878661,1) };

ImageScene::ImageScene(QObject *parent) :
    QGraphicsScene(parent),isOpenMouse(true)
{
/************************************
*yb添加
****************/

	//绿色图标
    Piximage_button[0].setPixmap(QPixmap(":/Resources/btn1.png"));

    Piximage_button[1].setPixmap(QPixmap(":/Resources/btn2.png"));

    Piximage_button[2].setPixmap(QPixmap(":/Resources/btn3.png"));

    Piximage_button[3].setPixmap(QPixmap(":/Resources/btn4.png"));

    Piximage_button[4].setPixmap(QPixmap(":/Resources/btn5.png"));

    Piximage_button[5].setPixmap(QPixmap(":/Resources/btn6.png"));
	//红色图标
    Piximage_button_selected[0].setPixmap(QPixmap(":/Resources/btn11.png"));

    Piximage_button_selected[1].setPixmap(QPixmap(":/Resources/btn22.png"));

    Piximage_button_selected[2].setPixmap(QPixmap(":/Resources/btn33.png"));

    Piximage_button_selected[3].setPixmap(QPixmap(":/Resources/btn44.png"));

    Piximage_button_selected[4].setPixmap(QPixmap(":/Resources/btn55.png"));

    Piximage_button_selected[5].setPixmap(QPixmap(":/Resources/btn66.png"));
	
	index_selected = -1;
    addItem(&pixImage);
    addItem(&pixImage_matching);
	pixImage_matching.setFlags(QGraphicsItem::ItemIsMovable);
    pixImage_matching.hide();
    pixImage_matching.setOpacity(0.5);
    chooseMoveObj = 0;
	for (size_t i = 0; i < 6; i++)
	{	
		//添加按钮到scene
		addItem(&Piximage_button[i]);
		addItem(&Piximage_button_selected[i]);
		Piximage_button[i].setZValue(1);
		Piximage_button_selected[i].setZValue(1);

        Piximage_button[i].setOpacity(0.7);
        Piximage_button_selected[i].setOpacity(0.7);
		//缩小
		Piximage_point[i] =  QPoint(-1, -1);
		//添加到父类图像中
		Piximage_button[i].setParentItem(&pixImage);
		Piximage_button_selected[i].setParentItem(&pixImage);
		
		Piximage_button[i].hide();
		Piximage_button_selected[i].hide();


	}
    setSceneRect(-375, -375, 750, 750);
	/****************/
    setBackgroundBrush(QBrush(Qt::black));
    transparams.fill(0, 11);
    movingImage = false;
    movingMatchiingImage =false;


	QPen pen;
	pen.setColor(Qt::green);
	pen.setWidth(2);

//    Marker_Tip = new QGraphicsLineItem();
//    addItem(Marker_Tip);
//    Marker_Tip->setParentItem(&(pixImage));
//    Marker_Tip->setPen(pen);
//    Marker_Tip->hide();

    Marker_Tip = new needle();
    addItem(Marker_Tip);
    Marker_Tip->setParentItem(&(pixImage));
    Marker_Tip->hide();

	//needle1 = new needle();
	//addItem(needle1);
	//needle1->setParentItem(&(pixImage));
	//needle1->setPen(pen);
	//needle1->hide();

	needle1 = new needle();
	addItem(needle1);
	needle1->setParentItem(&(pixImage));
	needle1->setPen(pen);
	needle1->hide();
}	

void ImageScene::zoomIn(float ratio)
{


    /***************************************/
    pixImage.setScale(pixImage.scale() * ratio);
    pixImage.setPos(pixImage.pos()* ratio);
   // update();


}

void ImageScene::zoomOut(float ratio)
{
	/***************************************/
    pixImage.setScale(pixImage.scale() / ratio);
    pixImage.setPos(pixImage.pos()/ ratio );
 //   update();
}

void ImageScene::zoomInMatching(float ratio)
{
    pixImage_matching.setScale(pixImage_matching.scale() * ratio);
   // pixImage_matching.setPos(pixImage_matching.pos()* ratio);
 //   update();
}

void ImageScene::zoomOutMatching(float ratio)
{
    pixImage_matching.setScale(pixImage_matching.scale() / ratio);
  //  pixImage_matching.setPos(pixImage_matching.pos()/ ratio );
 //   update();
}

void ImageScene::setPixImage(QPixmap Pix_Scr)
{
    Pixmap_scr = Pix_Scr;
    pixImage.setPixmap(Pixmap_scr);
    pixImage.setPos(-375, -375);
    pixImage.setScale(width() / Pix_Scr.width());
}

void ImageScene::setMoveObj(int Obj)
{
    chooseMoveObj = Obj;
}

void ImageScene::loadDCMImage(QString FilePath)
{
    QImage qimg;
    QByteArray ba = FilePath.toLatin1(); // QString转为char*
    char* filename = ba.data();

    char* prefix;
    size_t filename_length = strlen(filename); // length ()
    // int filename_length=filename.length();//
    prefix = filename + filename_length - 3; //获得后三位字符
    cv::Mat original_image;
    if(strcmp(prefix, "IMA") == 0 || strcmp(prefix, "dcm") == 0) //判断是什么文件
    {
        DicomImage img(FilePath.toLocal8Bit().data());

        cv::Mat(int(img.getWidth()), int(img.getHeight()), CV_16U, (uint16_t*)img.getOutputData(16)).copyTo(original_image);
        double maxVal;
        cv::minMaxLoc(original_image, nullptr, &maxVal);
        original_image.convertTo(original_image, CV_8UC1, 256.0 / maxVal);
        qimg = cvMat2QImage(original_image);
    }
    else if(strcmp(prefix, "BMP") == 0 || strcmp(prefix, "bmp") == 0 ||
            strcmp(prefix, "JPG") == 0 || strcmp(prefix, "jpg") == 0)
    {
        original_image = cv::imread(std::string(FilePath.toLocal8Bit()), CV_LOAD_IMAGE_GRAYSCALE);
        if(original_image.type() != CV_8UC1)
        {
            double maxVal;
            cv::minMaxLoc(original_image, nullptr, &maxVal);
            original_image.convertTo(original_image, CV_8UC1, 256.0 / maxVal);
        }
        qimg.load(FilePath);

    }
    else
    {

        return;
    }
    Pixmap_scr = QPixmap::fromImage(qimg);
    pixImage.setPixmap(Pixmap_scr);
    pixImage.setPos(-375, -375);
    pixImage.setScale(width() / qimg.width());
 // update();
}

void ImageScene::loadBMPImage(QString FilePath)
{

    originalImage = cv::imread((FilePath.toLocal8Bit()).data(), CV_LOAD_IMAGE_GRAYSCALE);
    QImage qimg = cvMat2QImage(originalImage);
    Pixmap_scr = QPixmap::fromImage(qimg);
    pixImage.setPixmap(Pixmap_scr);
     pixImage.setPos(-375, -375);
    pixImage.setScale(width() / qimg.width());
 //   update();
}

void ImageScene::loadImage(cv::Mat Image)
{
   originalImage = Image;

   QImage qimg = cvMat2QImage(originalImage);
   Pixmap_scr = QPixmap::fromImage(qimg);
   pixImage.setPixmap(Pixmap_scr);
   pixImage.setPos(-375, -375);
   pixImage.setScale(width() / qimg.width());
//   update();
}

void ImageScene::loadMatchingImage(cv::Mat Image)
{
    originalImage = Image;

    QImage qimg = cvMat2QImage(Image);
    QPixmap Pixmap_matching = QPixmap::fromImage(qimg);
    pixImage_matching.setPixmap(Pixmap_matching);
    pixImage_matching.setPos(-375, -375);
    pixImage_matching.setTransformOriginPoint(pixImage_matching.pixmap().width() / 2, pixImage_matching.pixmap().height() / 2);
   // zoomOutMatching(1.5);
 //   update();
}

void ImageScene::loadMatchingImage(QPixmap Pixmap)
{
    pixImage_matching.setPixmap(Pixmap);
    pixImage_matching.setPos(-375, -375);
    pixImage_matching.setTransformOriginPoint(pixImage_matching.pixmap().width() / 2, pixImage_matching.pixmap().height() / 2);
   // zoomOutMatching(1.5);
 //   update();
}

void ImageScene::saveImage(QString FilePath)
{
    QFile file(FilePath);
    file.open(QIODevice::WriteOnly);
    pixImage.pixmap().save(&file, "PNG");
}

void ImageScene::setmouseConnect(bool a)
{
    isOpenMouse = a;
}

void ImageScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isOpenMouse == false)
        return;
    QGraphicsScene::mousePressEvent(mouseEvent);
    pressPoint = mouseEvent->scenePos();

	switch (mouseEvent->button())
	{
	case Qt::MouseButton::LeftButton:
		selected_show();
        break;
    case Qt::MouseButton::MiddleButton:
        movingImage = true;
        break;
    case Qt::MouseButton::RightButton:
        movingMatchiingImage = true;
            break;
        break;
    default:
        break;
    }
    update();
}

void ImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isOpenMouse == false)
        return;
      QGraphicsScene::mouseMoveEvent(mouseEvent);
      if(chooseMoveObj == 0)
      {
          QPointF move = mouseEvent->scenePos() - mouseEvent->lastScenePos();
          QPointF lastPos = pixImage.pos();
          if (movingImage)
          {
              pixImage.setPos(lastPos + move);
          }
      }
      else if(chooseMoveObj == 1)
      {
		  if (mouseEvent->buttons() & Qt::RightButton)
		  {
			  if (movingImage)
			  {
				  QPointF move = mouseEvent->scenePos() - mouseEvent->lastScenePos();
				  QPointF lastPos = pixImage.pos();
				  pixImage.setPos(lastPos + move);

			  }
			  if (movingMatchiingImage)
			  {
                  QPointF last_scene = mouseEvent->lastScenePos();
                  QPointF current_scene = mouseEvent->scenePos();
                  QPointF last_Matching = pixImage_matching.mapFromScene(last_scene);
                  QPointF current_Matching = pixImage_matching.mapFromScene(current_scene);
                  qDebug()<<last_scene <<current_scene <<last_Matching <<current_Matching;
//                  float rotate = pixImage_matching.rotation() /180 * PI;
//                  qDebug()<< rotate ;
                  QPointF lastmatchingPos = QPointF(pixImage_matching.pixmap().width()/2 * pixImage_matching.scale(), pixImage_matching.pixmap().height()/2* pixImage_matching.scale());
                  qDebug()<<lastmatchingPos ;
                  float x1 = last_Matching.x() - lastmatchingPos.x();
                  float y1 = last_Matching.y() - lastmatchingPos.y();
                  float x2 = current_Matching.x() - lastmatchingPos.x();
                  float y2 = current_Matching.y() - lastmatchingPos.y();
                   if((x1 == 0 && y1 == 0) || (x2 == 0 && y2 == 0))
                       return;
				  float theta = acosf((x1 * x2 + y1 * y2) / sqrtf(x1 * x1 + y1 * y1) / sqrtf(x2 * x2 + y2 * y2)) / PI * 180;
				  float cross = x1 * y2 - x2 * y1;
				  if (cross < 0)
                      theta = - theta + pixImage_matching.rotation();
                  else
                      theta =  theta + pixImage_matching.rotation();
                  if(theta > 360)
                      theta -=360;
                  if(theta < -360)
                      theta +=360;
                  qDebug() << theta;
                  pixImage_matching.setRotation(theta);

			  }
		  }


      }
      update();

}

void ImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isOpenMouse == false)
        return;
      QGraphicsScene::mouseReleaseEvent(mouseEvent);
//    bool bsuccess = false;
    QPointF moved = mouseEvent->scenePos() - pressPoint;
    //if (moved.manhattanLength() < 5)
    //{
    //    QGraphicsItem *item = itemAt(mouseEvent->scenePos(), QTransform());
    //}

    movingImage = false;
    movingMatchiingImage = false;
}

void ImageScene::wheelEvent(QGraphicsSceneWheelEvent *wheelEvent)
{
    if(isOpenMouse == false)
        return;
    QGraphicsScene::wheelEvent(wheelEvent);
    int delta = wheelEvent->delta();
    if (delta > 0)
    {
        if(chooseMoveObj ==0)
            zoomIn((float)1.1);
        else
            zoomInMatching((float)1.03);
    }
    else
    {   if(chooseMoveObj ==0)
            zoomOut((float)1.1);
        else
            zoomOutMatching( (float)1.03);
    }
    this->update();
}

void ImageScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(isOpenMouse == false)
        return;
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
  //  pixImage.resetTransform();
    emit doubleclicked1(this);

}

void ImageScene::show_otherItem()
{

}

QImage ImageScene::cvMat2QImage(const cv::Mat &mat)
{
    QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
    image.setColorCount(256);
    for (int i = 0; i < 256; i++)
    {
        image.setColor(i, qRgb(i, i, i));
    }
    // Copy input Mat
    uchar *pSrc = mat.data;
    for (int row = 0; row < mat.rows; row++)
    {
        uchar *pDest = image.scanLine(row);
        memcpy(pDest, pSrc, mat.cols);
        pSrc += mat.step;
    }
    return image;
}


QPointF ImageScene::Pt3DtoPt2D(QVector3D pt3d)
{
    if (transparams.length() != 11)
    {
        return QPointF(0, 0);
    }

    QPointF  ret;
    ret.setX((transparams[0] * pt3d.x() +
        transparams[1] * pt3d.y() +
        transparams[2] * pt3d.z() +
        transparams[3]) /
        (transparams[4] * pt3d.x() +
            transparams[5] * pt3d.y() +
            transparams[6] * pt3d.z() + 1));
    ret.setY((transparams[7] * pt3d.x() +
        transparams[8] * pt3d.y() +
        transparams[9] * pt3d.z() +
        transparams[10]) /
        (transparams[4] * pt3d.x() +
            transparams[5] * pt3d.y() +
            transparams[6] * pt3d.z() + 1));
    return ret;
}

QPointF ImageScene::getRotatePoint(QPointF Point, float rotate_Rad)
{
    float point_x = Point.x() * cosf(rotate_Rad) - Point.y() * sinf(rotate_Rad);
    float point_y = Point.x() * sinf(rotate_Rad) + Point.y() * cosf(rotate_Rad);
    return QPointF(point_x , point_y);
}
//画图
void  ImageScene::selected_show()
{
    if (index_selected >= 0)
    {
		QPointF pressPoint_pixImage = pixImage.mapFromScene(pressPoint);
		Piximage_point[index_selected] = pressPoint_pixImage;
		Piximage_button_selected[index_selected].setPos(pressPoint_pixImage - QPoint(10,10)*Piximage_button->scale());//按钮图片像素/2*倍率
		Piximage_button[index_selected].setPos(pressPoint_pixImage - QPoint(10, 10)*Piximage_button->scale());
		for (size_t i = 0; i < 6; i++)   //红绿按键切换
		{
			if (i == index_selected)
			{
				Piximage_button_selected[index_selected].show();
				Piximage_button[index_selected].hide();
			}
			else
			{
				if (Piximage_point[i].x() >= 0 && Piximage_point[i].y() >= 0)
				{
					Piximage_button[i].show();
					Piximage_button_selected[i].hide();
				}
			}
		}
        emit pointChanged(index_selected);
	}
	show_otherItem();
//    update();
}

void ImageScene::selected_hide()
{
     for(size_t i = 0; i < 6; i++)
     {
         Piximage_button[i].hide();
         Piximage_button_selected[i].hide();
     }

}

