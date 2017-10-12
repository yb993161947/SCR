#include <thread_get_ndi_marker.h>
#include <QDebug>
#include <Eigen/Eigen>
#include <qthread.h>
#include <QTextStream>
#include <QFile>
thread_get_NDI_marker::thread_get_NDI_marker()
{
    file.setFileName("log.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) //以文本文式写入
    {
        out_file.setDevice(&file);
        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
        QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
        out_file<<str;
    }
}

thread_get_NDI_marker::thread_get_NDI_marker(int port)
{
     file.setFileName("log.txt");
     if(file.open(QIODevice::WriteOnly | QIODevice::Text)) //以文本文式写入
     {
         out_file.setDevice(&file);
         QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
         QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式
         out_file<<str;
     }
    init_udp(port);
}

thread_get_NDI_marker::~thread_get_NDI_marker()
{
    file.close();
    delete UdpSocket;
    delete this;
}
//初始化udp
void thread_get_NDI_marker::init_udp(int port)
{
    UdpSocket = new QUdpSocket(this);
	qDebug() << "bind " << port;
	qDebug()<< UdpSocket->bind(port,QUdpSocket::ShareAddress);
    connect(UdpSocket,SIGNAL(readyRead()),this,SLOT(revData()));
    connect(UdpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));
}

QList<Info_NDI> thread_get_NDI_marker::ProcessReceiveData(QString datas)
{
QList<Info_NDI> ListInfoNDI;
ListInfoNDI.clear();
if(typeofdevice == Type_NDI)
{
	QStringList datalist = datas.split(' ');
	if (datalist.length() % 13 != 3)    // 4 lines for every marker , blank line at last.
	{
		return ListInfoNDI;
	}
	datalist.pop_front();
	datalist.pop_front();
	for (int i = 0; i < datalist.length() / 13; i++)
	{
        Info_NDI Marker;
		if (i == 0)
			Marker.name = datalist[i * 13];
		else
		{
			Marker.name = (datalist[i * 13]).remove(0, 1);
		}

		for (int j = 1; j < 13; j++)
		{

			Marker.Pos((j - 1) / 4, (j - 1) % 4) = datalist[i * 13 + j].toDouble();

		}
        Marker.Pos.row(3) << 0, 0, 0, 1;
        ListInfoNDI.push_back(Marker);
	}
	
}
else if (typeofdevice == Type_Tracker)
{
	QStringList datalist = datas.split('\n');

	if (datalist.length() % 4 != 1)    // 4 lines for every marker , blank line at last.
	{
		return ListInfoNDI;
	}
	for (int i = 0; i < datalist.length() / 4; i++)
	{
		Info_NDI marker;//NDI返回mark的齐次矩阵
		marker.Pos.row(3) << 0, 0, 0, 0;
		marker.name = datalist[i * 4];
		{
			for (int j = 0; j < 3; j++)
			{
				QStringList row = datalist[i * 4 + j + 1].split(",");
				if (row.length() != 4)
				{
					break;
				}
				else
				{
					for (int k = 0; k < 4; k++)
						marker.Pos(j, k) = row[k].toDouble();
				}
			}
			marker.Pos(3, 3) = 1;
			ListInfoNDI.push_back(marker);
		}
	}	
}
return ListInfoNDI;
}

void thread_get_NDI_marker::setTypeofDevice(TypeofDevice Type)
{
	typeofdevice = Type;
}

void thread_get_NDI_marker::run()
{
    //while(1);
	this->exec();
}

//UDP接收数据
void thread_get_NDI_marker::revData()
{
     QString datas ;
     while(UdpSocket -> hasPendingDatagrams())
     {
        QByteArray datagram;
        datagram.resize(UdpSocket->pendingDatagramSize());
        UdpSocket->readDatagram(datagram.data(),datagram.size());
        datas = QString::fromUtf8(datagram);   
        emit threadSignal(ProcessReceiveData(datas));
        out_file<<datas;
    }
	

}
//UDP出错警告
void thread_get_NDI_marker::displayError(QAbstractSocket::SocketError)
{
    qDebug()<<UdpSocket->errorString();
    UdpSocket->close();
}

