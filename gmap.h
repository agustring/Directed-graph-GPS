#ifndef GMAP_H
#define GMAP_H
#include "node.h"
#include "street.h"
#include <QList>
#include <QString>
#include <QMap>
#include <QFile>

using namespace std;


class Gmap
{
public:
    Gmap();

    bool addNode(Node* nd);
    // Check if node neither street are repeated !
    bool addStreet(Street *s, Node* n1, Node* n2);
    QList <Node*> theShortestPathAlgorithm(Node* start, Node* finish, double &d);
    double indexMinDist(double a[],bool b[], int n);
    Node* getNode(QString a);
    bool mapLoading(QFile &file);
    Street* getStreett(QString st);

    void show()
    {
        for (int i=0; i<nodeList.length(); i++){
            nodeList.at(i)->mostrarNodo();
        }
    }

private:
    int seekNdIndex(Node* n);

    QString mapName; //City name or something like that 'd be ok.
    QList <Node*> nodeList; // List of every corner in the map.
    QList <Street*> streetList; // List of every street in the map.
};

#endif // GMAP_H
