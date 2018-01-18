#include <QDir>
#include <QFileInfo>
#include <qDebug>
#include "FileSystemWatcher.h"
#include "qsettings.h"
#include "QPixmap.h"
#include "QByteArray"
#include "string.h"
#include "dcmimgle/dcmimage.h"
#include "opencv.hpp"
#include "stdint.h"
#include "qthread.h"
using namespace cv;

QString FileSystemWatcher::WatchPath = "C:/";
FileSystemWatcher* FileSystemWatcher::m_pInstance = NULL;


FileSystemWatcher::FileSystemWatcher(QObject *parent)
    : QObject(parent)
{

}

// 监控文件或目录
void FileSystemWatcher::addWatchPath(QString path)
{
    WatchPath =path;
    qDebug() << QString("Add to watch: %1").arg(path);

    if (m_pInstance == NULL)
    {
        m_pInstance = new FileSystemWatcher();
        m_pInstance->m_pSystemWatcher = new QFileSystemWatcher();

        // 连接QFileSystemWatcher的directoryChanged和fileChanged信号到相应的槽
        connect(m_pInstance->m_pSystemWatcher, SIGNAL(directoryChanged(QString)), m_pInstance, SLOT(directoryUpdated(QString)));
        connect(m_pInstance->m_pSystemWatcher, SIGNAL(fileChanged(QString)), m_pInstance, SLOT(fileUpdated(QString)));
    }

    // 添加监控路径
    m_pInstance->m_pSystemWatcher->addPath(path);

    // 如果添加路径是一个目录，保存当前内容列表
    QFileInfo file(path);
    if (file.isDir())
    {
        const QDir dirw(path);
        m_pInstance->m_currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

// 只要任何监控的目录更新（添加、删除、重命名），就会调用。
void FileSystemWatcher::directoryUpdated(const QString &path)
{
    qDebug() << QString("Directory updated: %1").arg(path);

    // 比较最新的内容和保存的内容找出区别(变化)
    QStringList currEntryList = m_currentContentsMap[path];
    const QDir dir(path);

    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

    QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
    QSet<QString> currentDirSet = QSet<QString>::fromList(currEntryList);

    // 添加了文件
    QSet<QString> newFiles = newDirSet - currentDirSet;
    QStringList newFile = newFiles.toList();

    // 文件已被移除
    QSet<QString> deletedFiles = currentDirSet - newDirSet;
    QStringList deleteFile = deletedFiles.toList();

    // 更新当前设置
    m_currentContentsMap[path] = newEntryList;

    if (!newFile.isEmpty() && !deleteFile.isEmpty())
    {
        // 文件/目录重命名
        if ((newFile.count() == 1) && (deleteFile.count() == 1))
        {
            qDebug() << QString("File Renamed from %1 to %2").arg(deleteFile.first()).arg(newFile.first());
        }
    }
    else
    {
        // 添加新文件/目录至Dir
        if (!newFile.isEmpty())
        {
            qDebug() << "New Files/Dirs added: " << newFile;

            foreach (QString file, newFile)
            {
                // 处理操作每个新文件....
                char* filename;
             //   file ="2.IMA";
                QByteArray ba = file.toLatin1(); // QString转为char*
                filename = ba.data();

                char* prefix;
                size_t filename_length = strlen(filename); // length ()
                prefix = filename + filename_length - 3; //获得后三位字符
                QString path = WatchPath +QString("/")+ file;
               // if(strcmp(prefix, "IMA") == 0 || strcmp(prefix, "dcm") == 0) //判断是什么文件
               // {
					QThread::sleep(1);
                    DicomImage img(path.toLocal8Bit().data());
                    //	DicomImage img(filename);
                    Mat original_image;
                    cv::Mat(int(img.getWidth()), int(img.getHeight()), CV_16U, (uint16_t*)img.getOutputData(16)).copyTo(original_image);
                    double maxVal;
                    cv::minMaxLoc(original_image, nullptr, &maxVal);
                    original_image.convertTo(original_image, CV_8UC1, 256.0 / maxVal);
                    cvMat2QImage(original_image).save("XRayData.bmp");
               //}

            }
        }

        // 从Dir中删除文件/目录
        if (!deleteFile.isEmpty())
        {
            qDebug() << "Files/Dirs deleted: " << deleteFile;

            foreach(QString file, deleteFile)
            {
                // 处理操作每个被删除的文件....
            }
        }
    }
}

// 文件修改时调用
void FileSystemWatcher::fileUpdated(const QString &path)
{
    QFileInfo file(path);
    QString strPath = file.absolutePath();
    QString strName = file.fileName();

    qDebug() << QString("The file %1 at path %2 is updated").arg(strName).arg(strPath);
}

QImage FileSystemWatcher::cvMat2QImage(const cv::Mat& mat)
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
