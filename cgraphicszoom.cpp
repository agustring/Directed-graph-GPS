#include "cgraphicszoom.h"
#include <QDebug>
#include <QWheelEvent>



CGraphicsZoom::CGraphicsZoom(QWidget* hola):QGraphicsView (hola)
{

}

void CGraphicsZoom::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().ry()<0 && event->angleDelta().rx()==0){
        scale(1.1,1.1);
    }
    else {
        scale(0.9,0.9);
    }
}

void CGraphicsZoom::mousePressEvent(QMouseEvent *event){
    this->f=true;
    lastpos=event->pos();
}

void CGraphicsZoom::mouseReleaseEvent(QMouseEvent *e){
    this->f=false;
}

void CGraphicsZoom::mouseMoveEvent(QMouseEvent *e){
    if (this->f) {
        centerOn(e->localPos());
    }
}
