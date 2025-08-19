#include "sensorviewwidget.h"
#include "sensorgraphicsitem.h"
#include <QGraphicsScene>
#include <QPixmap>

SensorViewWidget::SensorViewWidget(QWidget *parent) : QGraphicsView(parent) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setFixedHeight(400);
}

void SensorViewWidget::displaySensor(const QList<Component> &sensor) {
    scene->clear();

    double totalHeight = 0;
    for (auto &c : sensor)
        totalHeight += QPixmap(c.imagePath).height();

    int yOffset = 0;
    int viewWidth = viewport()->width();

    for (auto &c : sensor) {
        QPixmap pix(c.imagePath);
        QPixmap scaled = scalePixmap(pix, height(), totalHeight);
        auto *item = new SensorGraphicsItem(scaled, c);

        // Center horizontally
        int xOffset = (viewWidth - scaled.width()) / 2;
        item->setPos(xOffset, yOffset);

        scene->addItem(item);
        connect(item, &SensorGraphicsItem::clicked, this, &SensorViewWidget::componentClicked);

        yOffset += scaled.height();
    }

    scene->setSceneRect(0, 0, viewWidth, yOffset);
}


QPixmap SensorViewWidget::scalePixmap(const QPixmap &pix, int viewHeight, double totalHeight) {
    if (totalHeight <= 0) return pix;
    double scaleFactor = static_cast<double>(viewHeight) / totalHeight;
    return pix.scaled(pix.width() * scaleFactor, pix.height() * scaleFactor, Qt::KeepAspectRatio);
}
