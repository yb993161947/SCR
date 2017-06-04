#ifndef LASSOWIDGET_H
#define LASSOWIDGET_H

#include <QRect>
#include <QWidget>

class LassoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LassoWidget(QWidget* parent = 0);
    enum State
    {
        Disabled,
        Ready,
        Selecting,
    };

    QRect getSelection();

protected:
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;
signals:
    void finished();
public slots:
    void start();

private:
    QPoint startPoint;
    QPoint endPoint;
    QRect selection;
    State state;
};

#endif // LASSOWIDGET_H
