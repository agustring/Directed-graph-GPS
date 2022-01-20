#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gmap.h>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void drawDijkstra(QList <Node*> l, QGraphicsScene &scene);
    QString inputAnalyzeF(QString auxin, QString auxn, int &auxpix);

    ~MainWindow();

private slots:
    void on_goButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
