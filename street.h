#ifndef STREET_H
#define STREET_H
#include <QString>
#include <QPair>
#include <QPoint>

class Node;
#include "node.h"

using namespace std;

class Street
{
public:
    Street();
    Street(QString name){this->name=name;}
    void addF(Node* f){adj.first=f;}
    void addT(Node* t){adj.second=t;}
    void setDist(double dist){this->value=dist;}
    QString getName(){return name;}
    double getDist(){return value;}
    Node* getToND(){return adj.second;}
    Node* getFromND(){return adj.first;}
    void setName(QString n){name=n;}


private:
    QString name;
    double value;
    QPair <Node*,Node*> adj;

};

#endif // STREET_H
