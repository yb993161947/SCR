#include "ACLwidget.h"
#include <QApplication>
#include "captureVideo/capturevideowidget.h"
#include "./CArmAngleCalCuLate/widget.h"
#include "./fileWatcher/FileSystemWatcher.h"
#include "QSettings"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings *configIniRead = new QSettings("configure.ini", QSettings::IniFormat);
    QString WatchPath = configIniRead->value("/DcmFilePath/path").toString();
    FileSystemWatcher::addWatchPath(WatchPath);
    Widget w;
    w.show();
    return a.exec();
}
//[UR]
//IP="169.254.26.126"
//TCP="0,0,0,0,0,90"

//[MarkerName]
//MarkerFemur = "TTBLOCK0714"
//MarkerTibia = "Marker_UR_new"
//MarkerXspot1 = "XSPOT1"
//MarkerXspot2 = "XSPOT2"
//MarkerTip = "MARKERTIP_LONG"
//MarkerRobot = "Marker_Robot"

//[NDI]

//Port = 5555
//XSpotPts3DMatrix = "353.5917295, -28.94508077, -58.35207327,350.457801, -33.334644, -88.32555342,347.1837796, -37.57368775, -118.639914,295.8181762, -34.59162595, -31.80863198,282.4332982, -40.8479307, -63.78963793,267.7006404, -47.70638125, -98.62438413,296.9313793, 37.83713989, -48.21922192,286.5644333, 42.54051603, -74.75168674,276.5781768, 47.58420394, -101.5227552,343.6148427, 33.11330516, -67.86624091,339.9296347, 36.50701665, -92.54845644,336.1567828, 39.58543792, -116.878661"

//[Tracker]

//Port = 5302
//XSpotPts3DonMarker1 = "65.27, -25.61,  -61.67,65.27, 29.39, -61.67,47.15, 4.39, -11.86,47.15, -15.61, -11.86,29.83, -40.00, -95.85,32.64, -40.00, -59.71,39.46, 40.00, -19.98,-25.22, 40.00, -3.09"
//Marker1ToXspot = "0.9999,0.0008,-0.0003,14.81733179,-0.0146,-0.9998,-0.0182,-26.91508238,0,	0.0182, -0.9997,-0.77761967,0,	0,	0,	1"
//Marker2ToXspot  = "-1,0.0056,-0.0003,-15.31207789,0.0011,-0.9999,-0.0087,-27.07246304,-0.0003,-0.0087,0.9999,-0.63725643,0,	0,	0,	1"
//Marker1ToMarker2 = "0.766044443,0,-0.64278761,35.75,0,1,0,0,0.64278761,0,0.766044443,98.25,0,0,0,1"
//[Register]

//tanzhen2tip = "-196.4532 ,- 1.7583, - 0.1103,	1"
//TofTCP_Up2MarkeronRobot = ""
//TofTCP_Down2MarkeronRobot = ""
//TofMarkeronRobot2Robot = "-0.01892333118,0.004903443199,-0.9993053558,423.4891478,-0.9997157185,-0.01115633245,0.02974294868,-24.54059943,0.01449105839,0.9999246591,0.02259664511,17.39326934,0,	0,	0,	1"
