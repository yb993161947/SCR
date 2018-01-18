QT       += core gui
QT	     += network
QT           += opengl


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = ACLReconstruction

TEMPLATE = app

RESOURCES += resources.qrc
RC_FILE = ACL.rc

SOURCES += main.cpp\
        ACLwidget.cpp \
        ImageScene.cpp \
        imagescene_femur_lat.cpp \
        tablesketch_item.cpp \
        thread_get_ndi_marker.cpp \
    carm/DxMath.cpp \
    carm/DxPoint.cpp \
    carm/ImageRectify.cpp \
    captureVideo/capturevideowidget.cpp \
    captureVideo/lassowidget.cpp \
    imagescene_femur_ap.cpp \
    imagescene_Tibia_ap.cpp \
    imagescene_Tibia_lat.cpp \
    dialog_setting.cpp \
    UrAPI/mythread.cpp \
    UrAPI/socket.cpp \
    UrAPI/ur_class_test.cpp \
    UrAPI/UR_interface.cpp \
    needle.cpp \
    CArmAngleCalCuLate/widget.cpp \
    carm/DxSpatialMatching.cpp \
    fileWatcher/FileSystemWatcher.cpp \
    imagescene_camera.cpp \
    navilabel.cpp



HEADERS  += ACLwidget.h \
        ImageScene.h \
        imagescene_femur_lat.h \
        tablesketch_item.h \
        thread_get_ndi_marker.h \
    carm/DxArray.h \
    carm/DxMath.h \
    carm/DxPoint.h \
    carm/ImageRectify.h \
    captureVideo/capturevideowidget.h \
    captureVideo/lassowidget.h \
    imagescene_femur_ap.h \
    imagescene_Tibia_ap.h \
    imagescene_Tibia_lat.h \
    dialog_setting.h \
    UrAPI/mythread.h \
    UrAPI/socket.h \
    UrAPI/ur_class_test.h \
    UrAPI/UR_interface.h \
    needle.h \
    CArmAngleCalCuLate/widget.h \
    carm/DxSpatialMatching.h \
    fileWatcher/FileSystemWatcher.h \
    imagescene_camera.h \
    navilabel.h

FORMS    += ACLwidget.ui \
    captureVideo/capturevideowidget.ui \
    UrAPI/ur_class_test.ui \
    CArmAngleCalCuLate/CArmwidget.ui \
    dialog_setting.ui
#DCMTK

QMAKE_CFLAGS_DEBUG += -MDd
QMAKE_CXXFLAGS_DEBUG += -MDd

#Ur
INCLUDEPATH +=  $$PWD\UrAPI\
                $$PWD/ThirdLib/libmodbus/windows64/includes
LIBS +=  $$PWD\ThirdLib\libmodbus\windows64\lib\libmodbus.lib

#openCV2.4.13x64
INCLUDEPATH += 	$$PWD\ThirdLib\OpenCVMSVC2015_x64\include\
                $$PWD\ThirdLib\OpenCVMSVC2015_x64\include\opencv\
                $$PWD\ThirdLib\OpenCVMSVC2015_x64\include\opencv2
win32:CONFIG(debug, debug|release){
LIBS+=  $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_calib3d2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_contrib2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_core2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_features2d2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_flann2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_gpu2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_highgui2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_imgproc2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_legacy2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_ml2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_nonfree2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_objdetect2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_ocl2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_photo2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_stitching2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_superres2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_ts2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_video2413d.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_videostab2413d.lib
}else:win32:CONFIG(release, debug|release){
LIBS+=  $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_calib3d2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_contrib2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_core2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_features2d2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_flann2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_gpu2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_highgui2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_imgproc2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_legacy2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_ml2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_nonfree2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_objdetect2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_ocl2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_photo2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_stitching2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_superres2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_ts2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_video2413.lib\
        $$PWD\ThirdLib\OpenCVMSVC2015_x64\x64\vc14\lib\opencv_videostab2413.lib
}

#eigen
INCLUDEPATH +=	$$PWD\ThirdLib\eigen-eigen-07105f7124f9

#dcmtk
INCLUDEPATH +=  $$PWD\ThirdLib\DCMTK3.6.0x64\include\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\config\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmdata\libi2d\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmdata\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmimage\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmimgle\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmjpeg\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmjpls\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmnet\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmpstat\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmqrdb\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmsign\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmsr\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmtls\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\dcmwlm\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\oflog\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\oflog\config\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\oflog\helpers\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\oflog\spi\
                $$PWD\ThirdLib\DCMTK3.6.0x64\include\dcmtk\ofstd
LIBS += $$PWD\ThirdLib\netapi32.Lib\
        $$PWD\ThirdLib\WSock32.Lib\
        ws2_32.lib\
        Advapi32.lib

win32:CONFIG(debug, debug|release){
LIBS +=$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\charls.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmdata.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmdsig.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmimage.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmimgle.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmjpeg.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmjpls.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmnet.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmpstat.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmqrdb.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmsr.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmtls.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\dcmwlm.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\ijg8.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\ijg12.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\ijg16.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\libi2d.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\oflog.lib\
$$PWD\ThirdLib\DCMTK3.6.0x64\lib\debug\ofstd.lib
}else:win32:CONFIG(release, debug|release){
LIBS += $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\charls.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmdata.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmdsig.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmimage.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmimgle.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmjpeg.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmjpls.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmnet.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmpstat.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmqrdb.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmsr.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmtls.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\dcmwlm.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\ijg8.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\ijg12.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\ijg16.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\libi2d.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\oflog.lib\
        $$PWD\ThirdLib\DCMTK3.6.0x64\lib\release\ofstd.lib

}





