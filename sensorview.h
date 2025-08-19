#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include "sensormodel.h"
#include "SensorGraphicsItem.h"

/**
 * @brief Displays the current sensor visually
 */
class SensorView : public QGraphicsView {
    Q_OBJECT
public:
    explicit SensorView(QWidget *parent = nullptr);

    void updateSensor(const SensorModel &model);

signals:
    void componentClicked(const Component &comp);

private:
    QGraphicsScene *m_scene;
};
