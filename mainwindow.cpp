#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <gmap.h>
#include <QList>
#include <QPen>
#include <QColor>
#include <QGraphicsPixmapItem>
#include <QtMath>


Gmap *m;
QGraphicsScene *scene;

void drawMap(QGraphicsScene &scene);
void pix(QGraphicsScene &scene, int p, int l, QPoint cs, QPoint cf);
void generartexto(QGraphicsTextItem *text1, int x, int y, int inclinacion, QString texto);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m = new Gmap();
    QFile f("datosmapa.txt");
    m->mapLoading(f);
    setWindowTitle("Proyecto Gaston Arroyo");
    scene= new QGraphicsScene(ui->graphicsView);
    drawMap(*scene);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_goButton_clicked()
{
    QString f1 = ui->fromEdit->text();
    QString f2 = ui->fromAltEdit->text();
    QString t1 = ui->toEdit->text();
    QString t2 = ui->toAltEdit->text();
    QList <Node*> Dijkstra;
    Dijkstra.clear();
    double d=0.0;

    scene->clear();
    drawMap(*scene);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->show();

    Node* from=nullptr;
    Node* to=nullptr;

    int auxpix;

    f1 = inputAnalyzeF(f1,f2,auxpix);
    if (m->getStreett(f1)!=nullptr){
        from=m->getStreett(f1)->getToND();
        pix(*scene,auxpix,0,m->getStreett(f1)->getFromND()->getCoord(),from->getCoord());
        d+=auxpix;
    }

    t1 = inputAnalyzeF(t1,t2,auxpix);
    if (m->getStreett(t1)!=nullptr){
        to=m->getStreett(t1)->getFromND();
        pix(*scene,0,auxpix,to->getCoord(),m->getStreett(t1)->getToND()->getCoord());
        d+=auxpix;
    }

    if (from!=nullptr && to!=nullptr){
        double da;
        Dijkstra=m->theShortestPathAlgorithm(from,to, da);
        ui->distLcd->display(d+da);
        double fuel = 11.5*(d+da)/100000;
        ui->fuelLcd->display(fuel);
        double money = fuel * 62.00;
        ui->moneyLcd->display(money);
    }

    drawDijkstra(Dijkstra,*scene);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->show();

}

QString MainWindow::inputAnalyzeF(QString auxin, QString auxn, int &auxpix){
    auxin = auxin.toLower();
    unsigned int auxnum = auxn.toUInt();
    auxpix=auxnum;

    auxnum = (unsigned int) trunc(auxnum/100)*100;
    auxin+=" ";
    QString auxnumstr;

    auxpix=auxpix-auxnum;

    auxnumstr = QString::number(auxnum);
    int i = 0;

    while (i<auxnumstr.length()) {
        auxin.push_back(auxnumstr.at(i));
        i++;
    }

    auxnum+=100;
    auxnumstr = QString::number(auxnum);
    auxin+="-";
    i=0;

    while (i<auxnumstr.length()) {
        auxin.push_back(auxnumstr.at(i));
        i++;
    }
    return auxin;
}

void pix(QGraphicsScene &scene, int p, int l, QPoint cs, QPoint cf){
    QPen path(Qt::red);
    path.setWidth(5);
    int lx = l;
    int ly = l;
    int px = p;
    int py = p;
    int m=5;

    if (cs.x()>cf.x()) {
        lx=-1*lx;
    }

    if (cs.y()>cf.y()) {
        ly=-1*ly;
    }

    if (cs.x()==cf.x()){
        scene.addLine(cs.x()+m,cs.y()+m+py,cf.x()+m,cf.y()+m-ly,path);
    }
    if(cs.y()==cf.y()){
        scene.addLine(cs.x()+px+m,cs.y()+m,cf.x()-lx+m,cf.y()+m,path);
    }
//    if(cs.y()!=cf.y() && cs.x()!=cf.x()){
//        scene.addLine(cs.x()+m+px,cs.y()+m+py,cf.x()+m+lx,cf.y()+m+ly,path);
//    }
}

void generartexto(QGraphicsTextItem *text1, int x, int y, int inclinacion, QString texto){

    text1->setDefaultTextColor(Qt::gray);
    text1->setRotation(inclinacion);
    text1->setPos(x,y);
    text1->setPlainText(texto);
}

void drawMap(QGraphicsScene &scene){

        QList <QString> lista_de_calles_verticales = {"calle a -->", "calle b <--", "calle c -->","calle d <--","calle e -->","calle f <--", "calle g -->"};
        QList <QString> lista_de_calles_horizontales = {"calle 1 -->", "calle 2 <--", "calle 3 -->", "calle 4 <--", "calle 5 -->", "calle 6 <--", "calle 7 -->"};
        QList <QString> lista_de_calles_diagonales1 = { "diagonal 2 -->", "diagonal 3 -->", "diagonal 4 <--","diagonal 5 -->"};
        QList <QString> lista_de_calles_diagonales2 = {"diagonal 6 <-- ", "diagonal 7 <--", "diagonal 9 -->", "diagonal 10 <--", "diagonal 11 -->", "diagonal 12 -->"};


        QGraphicsTextItem *text = new QGraphicsTextItem;
        generartexto(text,45,27,45,"diagonal 1 -->");
        scene.addItem(text);
        QGraphicsTextItem *text5 = new QGraphicsTextItem;
        generartexto(text5,397,140,45,"diagonal 8 -->");
        scene.addItem(text5);

        for (int k = 0; k<7; k++){


            QGraphicsTextItem *text1 = new QGraphicsTextItem;
            generartexto(text1,10,-10 +k*120,0,lista_de_calles_verticales.at(k));
            scene.addItem(text1);

            QGraphicsTextItem *text2 = new QGraphicsTextItem;
            generartexto(text2,10+k*120,10,90,lista_de_calles_horizontales.at(k));
            scene.addItem(text2);


            if (k<2){
                QGraphicsTextItem *text5 = new QGraphicsTextItem;
                generartexto(text5,367,575+k*120,-45, lista_de_calles_diagonales2.at(k+2));
                scene.addItem(text5);
                QGraphicsTextItem *text4 = new QGraphicsTextItem;
                generartexto(text4,150,313+k*360,-45, lista_de_calles_diagonales2.at(k));
                scene.addItem(text4);
                QGraphicsTextItem *text6 = new QGraphicsTextItem;
                generartexto(text6,505,79+k*600,-45, lista_de_calles_diagonales2.at(k+4));
                scene.addItem(text6);
            }

            QGraphicsTextItem *text3 = new QGraphicsTextItem;

            if (k<2){
                generartexto(text3,30,193+k*120,-45, lista_de_calles_diagonales1.at(k));
                scene.addItem(text3);
            }
            else if (k<4){
                generartexto(text3,30,313+k*120,-45, lista_de_calles_diagonales1.at(k));
                scene.addItem(text3);
            }
        }

        int j=10;
        int k=0;
        while (j<6*120) {
            for (int i = 10;i<6*120;i+=120) {
                QPolygon triangle;
                QPolygon triangle1;
                QRect cuadra(QPoint (250,0+j),QSize(100,100));
                QRect cuadra3(QPoint (610,0+j),QSize(100,100));
                QRect cuadra2(QPoint (0+i,370),QSize(100,100));
                QRect plaza(QPoint (250,0+j),QSize(220,220));

                QPen p(Qt::yellow);
                QBrush b(Qt::gray);
                QBrush colorplaza(Qt::green);

                if(i!=250 && i!=370)
                    scene.addRect(cuadra2,p,b);
                if(j!=250 && j!=370)
                    scene.addRect(cuadra,p,b);

                scene.addRect(cuadra3,p,b);

                if(j==250)
                    scene.addRect(plaza,p,colorplaza);
                if(i==j && i!=250 && i!=370 && j!=370 && j!=610 ){
                    triangle << QPoint(10+i,0+j) << QPoint(100+i,0+j) << QPoint(100+i,90+j);
                    scene.addPolygon(triangle, p, b);
                    triangle1 << QPoint(0+i,10+j) <<QPoint(90+i,100+j) << QPoint(0+i,100+j);
                    scene.addPolygon(triangle1, p, b);
               }
                if(i!=j && i==240+j){
                    triangle << QPoint(10+i,0+j) << QPoint(100+i,0+j) << QPoint(100+i,90+j);
                    scene.addPolygon(triangle, p, b);
                    triangle1 << QPoint(0+i,10+j) <<QPoint(90+i,100+j) << QPoint(0+i,100+j);
                    scene.addPolygon(triangle1, p, b);
                }
                if(i!=j && i!=240+j && i!=250 && j!=370 && i!=610){
                    triangle << QPoint(0+i,0+j) << QPoint(90+i,0+j) << QPoint(0+i,90+j);
                    scene.addPolygon(triangle, p, b);
                    triangle1 << QPoint(10+i,100+j) <<QPoint(100+i,10+j) << QPoint(100+i,100+j);
                    scene.addPolygon(triangle1, p, b);
                }
            }
            k++;
            j+=120;
        }

}

void MainWindow::drawDijkstra(QList <Node*> l, QGraphicsScene &scene){
      QPen path(Qt::red);
      path.setWidth(5);
      int m=5;

      for (int i=0;i<l.length()-1;i++) {
          scene.addLine(l.at(i)->getCoord().rx()+m,l.at(i)->getCoord().ry()+m,l.at(i+1)->getCoord().rx()+m,l.at(i+1)->getCoord().ry()+m,path);
      }
}
