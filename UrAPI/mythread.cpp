#include "mythread.h"
#include <QDebug>


MyThread::MyThread(UR_class_test *ur_APP)
{
pUR_class_test = ur_APP;
}

void MyThread::run()
{
    while(pUR_class_test->GetRobotInfoThreadFlag)
    {
        pUR_class_test->pUR5->get_tcp_pos(pUR_class_test->TcpPos);
        pUR_class_test->pUR5->yb_get_joint_angle(pUR_class_test->Jointangle);
        emit this->threadSignal();

        sleep(1);
    }
}
