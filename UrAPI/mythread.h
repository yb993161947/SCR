#ifndef MYTHREAD2_H
#define MYTHREAD2_H

#include <QThread>
#include <QtWidgets/QWidget>

#include"ur_class_test.h"
#include"UR_interface.h"

class UR_class_test;
class UR_interface;
class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread(UR_class_test *ur_APP);
    UR_class_test *pUR_class_test;
    void run();

signals:
    void threadSignal();
};

#endif // MYTHREAD2_H
