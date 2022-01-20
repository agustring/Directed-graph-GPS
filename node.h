#ifndef NODE_H
#define NODE_H
#include <QList>
#include <QString>

class Street;           // Forward declaration
#include "street.h"

using namespace std;

class Node
{
public:
    Node();
    Node(QString name){this->stName=name;}
    void addStr(Street* st);
    QString getName(){return stName;}
    double getDistances(int i);
    Street* getAStreetbyIndex(int i);
    QList <Node*> getNeighbor();
    QList <Street*> getStreets(){return conStreet;}
    void mostrarNodo();
    void setCoord(int x, int y){coord.setX(x); coord.setY(y);}
    QPoint getCoord(){return coord;}

protected:
    QString stName;  // Ehhhhh, this is actually work in progress, please come back later xD
    QList <Street*> conStreet;
    QPoint coord;
};

#endif // NODE_H
