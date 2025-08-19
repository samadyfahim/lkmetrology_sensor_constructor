#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QSplitter>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "catalogue.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showDetails(const Component &comp);
    void addToSensor();
    void calculate();

private:
    void buildTabs();

    QTabWidget *tabs;
    QLabel *lblDetails;
    QLabel *lblCalcResult;

    QPushButton *btnAdd;
    QGraphicsScene *scene;
    QGraphicsView *view;

    QList<Component> catalogue;
    QList<Component> sensor;
    Component currentSelection;
    int sensorYOffset = 0; // stacking offset
};

#endif // MAINWINDOW_H
