#pragma once
#include <QGraphicsView>
#include "../models/component.h"

class QGraphicsScene;

class SensorViewWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit SensorViewWidget(QWidget *parent = nullptr);
    void displaySensor(const QList<Component> &sensor);

signals:
    void componentClicked(const Component &comp);

private:
    QGraphicsScene *scene;
    
    static QPixmap scalePixmap(const QPixmap &pix, int viewHeight, double totalHeight);
};
