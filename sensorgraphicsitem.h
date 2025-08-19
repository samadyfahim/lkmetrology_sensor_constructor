#pragma once
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "component.h"   // your struct/class definition

class SensorGraphicsItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Component comp;

    SensorGraphicsItem(const QPixmap &pix, const Component &c);

signals:
    void clicked(const Component &c);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};
