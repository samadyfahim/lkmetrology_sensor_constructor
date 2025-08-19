#pragma once
#include <QObject>
#include <QGraphicsPixmapItem>
#include "../models/component.h"

// Represents a draggable/clickable component in scene
class SensorGraphicsItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    SensorGraphicsItem(const QPixmap &pix, const Component &c);

signals:
    void clicked(const Component &c);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Component comp;
};
