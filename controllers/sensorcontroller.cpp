#include "sensorcontroller.h"

void SensorController::addComponent(const Component &comp) {
    // Replace existing of same type
    for (int i = 0; i < sensor.size(); ++i) {
        if (sensor[i].type == comp.type) {
            sensor.removeAt(i);
            break;
        }
    }

    // Insert in correct order
    QStringList typeOrder = {"Head", "Probe", "Module", "Tip"};
    int insertIndex = 0;
    for (; insertIndex < sensor.size(); ++insertIndex) {
        if (typeOrder.indexOf(comp.type) < typeOrder.indexOf(sensor[insertIndex].type))
            break;
    }
    sensor.insert(insertIndex, comp);
}

QList<Component> SensorController::getSensor() const {
    return sensor;
}

void SensorController::clearSensor() {
    sensor.clear();
}


QString SensorController::calculateResult() const {
    QStringList required = {"Head", "Probe", "Module", "Tip"};
    for (auto &r : required) {
        if (std::none_of(sensor.begin(), sensor.end(), [&](auto &c){ return c.type==r; })) {
            return "⚠️ Please select Head, Probe, Module, and Tip before calculating.";
        }
    }

    double totalLength = 0, weightedSum = 0;
    for (auto &c : sensor) {
        totalLength += c.length;
        weightedSum += c.length * c.cte;
    }
    double totalCTE = weightedSum / totalLength;

    return QString("Total Length: %1 mm\nOverall CTE: %2")
            .arg(totalLength)
            .arg(totalCTE, 0, 'f', 2);
}
