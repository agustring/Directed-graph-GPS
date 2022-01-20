#include "gmap.h"
#include <QList>
#include <QMap>

Gmap::Gmap()
{
    mapName="Mapa de Agustin Copita & co.";
    nodeList.clear();
    streetList.clear();
}

bool Gmap::addNode(Node *nd){
    Node* A;
    A=nd;
    int i=0;
    bool found=false;

    while (i<nodeList.length() && !found) {
        found= (A->getName()==nodeList.at(i)->getName());
        i++;
    } //Proves that node either is or isn't yet in the list

    if (!found){
        nodeList.push_back(nd);
    }
    return !found; //Returns if node was successfully added.
}

bool Gmap::addStreet(Street *s, Node *n1, Node *n2){

    //Nodes 1 & 2 must already appear in the node list b4 conect w street.

    Street *A= s;
    int i=0;
    bool found = false;
    bool found3 = false;

    while (i<streetList.length() && !found) {
        found= (A->getName()==streetList.at(i)->getName());
        i++;
    }

    //Proves that street is not repeated

    if (!found){
        i=0;
        Node* B=n1;
        bool found2 = false;
        while (i<nodeList.length() && !found2) {
            found2= (B->getName()==nodeList.at(i)->getName());
            i++;
        }

        //Once street is truly new, proves that fst node is in the list

        if (found2){
            B=n2;
            i=0;
            while (i<nodeList.length() && !found3) {
                found3= (B->getName()==nodeList.at(i)->getName());
                i++;
            }

            // Same but w snd node.
        }
    }

    if (found3){
        s->addF(n1);
        s->addT(n2);
        streetList.push_back(s);
        n1->addStr(s);
    } //Done.

    return found3;
}

int Gmap::seekNdIndex(Node* n){
    bool found=false;
    int i=0;
    while (!found && i<nodeList.length()) {
        if (nodeList.at(i)==n){
            return i;
        }
        else {
            i++;
        }
    }
    if (!found){
        return -1;
    }
}

double Gmap::indexMinDist(double a[],bool b[], int n){
    int i=0;
    double min = 12e6;
    while (i<n) {
        if (b[i]==false){
            if (a[i]<min){
                min=a[i];
            }
            // min = (a[i]<min) ? a[i] : min;
        }
    }
    return min;
}

//Node* getMinDist(QMap <Node*,double> Q)
//{
//    QList<Node*> list = Q.keys();
//    double min = 10000000.0;
//    Node* node = nullptr;
//    for (int i=0; i<list.size(); i++)
//    {
//        if (Q[list.at(i)] < min) {
//            min = Q[list.at(i)];
//            node = list.at(i);
//        }
//    }

//    return node;
//}

Node* getMinDist(QSet <Node*> p, QMap <Node*,double> dist)
{
    QList <Node*> list = p.toList();
    double min = 10000000.0;
    Node* node = nullptr;
    for (int i=0; i<list.size(); i++)
    {
        if (dist[list.at(i)] < min) {
            min = dist[list.at(i)];
            node = list.at(i);
        }
    }

    return node;
}

QList <Node*> Gmap::theShortestPathAlgorithm(Node* start, Node* finish, double &d){

    QMap <Node*,double> dist;
    QSet <Node*> Q;
    int l = nodeList.length();
    QMap <Node*,Node*> P;
    int i;

    for (i=0;i<l;i++) {
        dist.insert(nodeList.at(i),nodeList.at(i)==start ? 0:12e6);
        P.insert(nodeList.at(i),nullptr);
        Q.insert(nodeList.at(i));
    }

    while (!Q.empty()) {
        Node* u = getMinDist(Q, dist);
        double udist = dist[u];
        Q.remove(u);

        if (u==finish){
            d=udist;
            QList <Node*> S;
            while (u!=start) {
                S.push_front(u);
                u=P[u];
            }
            S.push_front(start);
            return S;
        }

        QList <Street*> R = u->getStreets();


        for (int j=0;j<R.length();j++) {

            double alt = udist + R.at(j)->getDist();

            if (alt<dist[R.at(j)->getToND()]){
                dist[R.at(j)->getToND()]=alt;
                P[R.at(j)->getToND()]=u;
            }
        }


    }
}

Node* Gmap::getNode(QString a){
    for (int i=0;i<nodeList.length();i++) {
        if (nodeList.at(i)->getName()==a){
            return nodeList.at(i);
        }
    }
    return nullptr;
}

bool Gmap::mapLoading(QFile &file){

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))return false;
    //Nodes first, street at last
    while (!file.atEnd()) {

        QString line = file.readLine();
        int i=0;
        if(!line.isEmpty()){
            QString n;
            //Node from availability checking
            while (line.at(i)!=QChar::Tabulation) {
                n.push_back(line.at(i));
                i++;
            }
            Node* from = nullptr;
            if (getNode(n)==nullptr){
                from = new Node(n);
                addNode(from);
            } else {
                from = getNode(n);
            }
            i++;
            n.clear();
            //Coord from->x setting
            while (line.at(i)!=QChar::Tabulation) {
                n.push_back(line.at(i));
                i++;
            }
            unsigned int x = n.toUInt();
            i++;
            n.clear();
            //Coord from->y setting
            while (line.at(i)!=QChar::Tabulation) {
                n.push_back(line.at(i));
                i++;
            }
            unsigned int y = n.toUInt();
            i++;
            n.clear();
            from->setCoord(x,y);

            //Same process w node to
            while (line.at(i)!=QChar::Tabulation) {
                n.push_back(line.at(i));
                i++;
            }
            Node* to = nullptr;
            if (getNode(n)==nullptr){
                to = new Node(n);
                addNode(to);
            } else {
                to = getNode(n);
            }
            i++;
            n.clear();
            while (line.at(i)!=QChar::Tabulation) {
                n.push_back(line.at(i));
                i++;
            }
            x = n.toUInt();
            i++;
            n.clear();

            while (line.at(i)!=QChar::Tabulation) {
                n.push_back(line.at(i));
                i++;
            }
            y = n.toUInt();
            i++;
            n.clear();
            to->setCoord(x,y);
            //
            while (line.at(i)!=QChar::Tabulation) {
                n.push_back(line.at(i));
                i++;
            }
            Street *c = new Street(n);
            n.clear();
            i++;
            while (line.at(i)!=QChar::LineFeed) {
                n.push_back(line.at(i));
                i++;
            }

            double dist = n.toDouble();
            c->setDist(dist);

            addStreet(c,from,to);
        }
    }
    file.close();
    return true;
}

Street* Gmap::getStreett(QString st){
    int i=0;
    while(i<streetList.length()){
        if(streetList.at(i)->getName()==st)return streetList.at(i);
        i++;
    }
    return nullptr;
}
