#include "sensorview.h"

SensorView::SensorView(QWidget *parent)
    : QGraphicsView(parent), m_scene(new QGraphicsScene(this))
{
    setScene(m_scene);
    setStyleSheet("background:white; border:1px solid #ccc;");
    setFixedHeight(400);
}

void SensorView::updateSensor(const SensorModel &model)
{
    m_scene->clear();

    // Compute scaling factor
    double totalHeight = 0;
    for (const auto &c : model.components())
        totalHeight += QPixmap(c.imagePath).height();

    const double scale = (totalHeight > height()) ? (height() / totalHeight) : 0.4;

    int yOffset = 0;
    for (const auto &c : model.components()) {
        QPixmap pix(c.imagePath);
        QPixmap scaled = pix.scaled(pix.width() * scale, pix.height() * scale,
                                    Qt::KeepAspectRatio, Qt::SmoothTransformation);

        auto *item = new SensorGraphicsItem(scaled, c);
        m_scene->addItem(item);
        item->setPos(0, yOffset);

        connect(item, &SensorGraphicsItem::clicked, this, &SensorView::componentClicked);

        yOffset += scaled.height();
    }
}
