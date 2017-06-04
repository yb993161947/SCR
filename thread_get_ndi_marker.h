#ifndef THREAD_GET_NDI_MARKER_H
#define THREAD_GET_NDI_MARKER_H
#include <QThread>
#include "Eigen/Eigen"
#include <QtNetwork/QtNetwork>
#include <QFile>
#include <QTextStream>
#include <Eigen/Eigen>
const int PORT = 5555;
using namespace Eigen;

struct Info_NDI{
    QString name;
    Matrix<double,4,4> Pos;
};
class thread_get_NDI_marker : public QThread
{
     Q_OBJECT

public:
    thread_get_NDI_marker();
    thread_get_NDI_marker(int port);
    ~thread_get_NDI_marker();

     QUdpSocket *UdpSocket;//UDP
     void init_udp(int port = PORT);//初始化UDP

     QList<Info_NDI> ListInfo_NDI;
     QList<Info_NDI> ProcessReceiveData(QString datas);
private:
    void run();//线程运行虚函数

    QFile file;
    QTextStream out_file;
private slots:
    void revData();//UDP接收槽
    void displayError(QAbstractSocket::SocketError);//UDP出错警告
signals:
    void threadSignal(QList<Info_NDI> ListInfo_NDI);

};

#endif // THREAD_GET_NDI_MARKER_H
