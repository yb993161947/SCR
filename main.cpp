#include "ACLwidget.h"
#include <QApplication>
#include "captureVideo/capturevideowidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
