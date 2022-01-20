#ifndef CGRAPHICSZOOM_H
#define CGRAPHICSZOOM_H
#include<QGraphicsView>

class CGraphicsZoom: public QGraphicsView
{
public:
    CGraphicsZoom(QWidget* hola);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
private:
    bool f = false;
    QPoint lastpos;
};

#endif // CGRAPHICSZOOM_H
