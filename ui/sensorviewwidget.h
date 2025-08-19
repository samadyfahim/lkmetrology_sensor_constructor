#pragma once
#include <QGraphicsView>
#include "../models/component.h"

class QGraphicsScene;
class QPushButton;

class SensorViewWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit SensorViewWidget(QWidget *parent = nullptr);
    void displaySensor(const QList<Component> &sensor);

signals:
    void componentClicked(const Component &comp);
    void clearRequested();

private:
    QGraphicsScene *scene;
    QPushButton *btnClear;
    
    static QPixmap scalePixmap(const QPixmap &pix, int viewHeight, double totalHeight);
};
