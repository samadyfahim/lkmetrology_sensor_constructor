#pragma once
#include "component.h"
#include <QList>
#include <QString>

/**
 * @brief Logical representation of a built sensor
 */
class SensorModel {
public:
    void addComponent(const Component &comp);
    void clear() { m_sensor.clear(); }
    const QList<Component>& components() const { return m_sensor; }

    QString calculateSummary() const;

private:
    QList<Component> m_sensor;
};
