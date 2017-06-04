#include "lassowidget.h"
#include <QMouseEvent>
#include <QPainter>


LassoWidget::LassoWidget(QWidget* parent) : QWidget(parent), state(Disabled) {}

QRect LassoWidget::getSelection() { return selection; }

void LassoWidget::mousePressEvent(QMouseEvent* event)
{
    if(state == Ready)
    {
        startPoint = event->pos();
        state = Selecting;
    }
}

void LassoWidget::mouseMoveEvent(QMouseEvent* event)
{
    if(state == Selecting)
    {
        endPoint = event->pos();
        selection.setX(qMin(startPoint.x(), endPoint.x()));
        selection.setY(qMin(startPoint.y(), endPoint.y()));
        selection.setWidth(qAbs(startPoint.x() - endPoint.x()));
        selection.setHeight(qAbs(startPoint.y() - endPoint.y()));
        update();
    }
}

void LassoWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if(state == Selecting)
    {
        emit finished();
        state = Disabled;
        update();
    }
}

void LassoWidget::paintEvent(QPaintEvent* event)
{
    if(state == Disabled)
    {
        QPainter painter(this);
        painter.end();
    }
    else
    {
        QPainter painter(this);
        painter.setPen(QPen(QBrush(Qt::red), 2));
        painter.drawRect(selection);
        painter.end();
    }
}

void LassoWidget::start()
{
    state = Ready;
    selection = QRect();
}
