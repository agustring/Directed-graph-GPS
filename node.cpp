#include "node.h"
#include <QDebug>
Node::Node()
{
    stName="";
    conStreet.clear();
    coord.setX(0);
    coord.setY(0);
}

void Node::addStr(Street *st){
    conStreet.push_back(st);
}

double Node::getDistances(int i){
    if (i<conStreet.length() && i>-1){
        return conStreet.at(i)->getDist();
    }
    else {
        return 12e6;
    }
}

Street* Node::getAStreetbyIndex(int i){
    if (i<conStreet.length() && i>-1){
        return conStreet.at(i);
    }
    else {
        return nullptr;
    }
}

QList <Node*> Node::getNeighbor(){
    QList <Node*> Q;
    for (int i=0;i<conStreet.length();i++) {
        Q.push_back(conStreet.at(i)->getToND());
    }
    return Q;
}

void Node::mostrarNodo(){
    qDebug() << " **";
    qDebug() << stName;
    for(int i=0; i<conStreet.length();i++)
    {
        qDebug()<<"     " + conStreet.at(i)->getName();
    }
}
