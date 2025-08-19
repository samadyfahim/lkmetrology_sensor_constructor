#pragma once
#include "../models/component.h"
#include <QList>
#include <QString>

// Handles business logic for sensor construction
class SensorController {
public:
    void addComponent(const Component &comp);
    QList<Component> getSensor() const;
    void clearSensor();
    QString calculateResult() const;

private:
    QList<Component> sensor;
};
