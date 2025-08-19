#include "sensorgraphicsitem.h"
#include <QGraphicsSceneMouseEvent>

SensorGraphicsItem::SensorGraphicsItem(const QPixmap &pix, const Component &c)
    : QGraphicsPixmapItem(pix), comp(c) {
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

void SensorGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsPixmapItem::mousePressEvent(event);
    emit clicked(comp);
}
