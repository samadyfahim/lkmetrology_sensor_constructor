#include "sensormodel.h"
#include <algorithm>

void SensorModel::addComponent(const Component &comp)
{
    static const QStringList typeOrder = {"Head", "Probe", "Module", "Tip"};

    // Remove any existing component of the same type
    for (int i = 0; i < m_sensor.size(); ++i) {
        if (m_sensor[i].type == comp.type) {
            m_sensor.removeAt(i);
            break;
        }
    }

    // Insert in proper order
    int insertIndex = 0;
    for (; insertIndex < m_sensor.size(); ++insertIndex) {
        if (typeOrder.indexOf(comp.type) < typeOrder.indexOf(m_sensor[insertIndex].type)) break;
    }
    m_sensor.insert(insertIndex, comp);
}

QString SensorModel::calculateSummary() const
{
    const QStringList required = {"Head", "Probe", "Module", "Tip"};
    for (const auto &r : required) {
        if (std::none_of(m_sensor.begin(), m_sensor.end(),
                         [&](const Component &c) { return c.type == r; })) {
            return "⚠️ Please select Head, Probe, Module, and Tip before calculating.";
        }
    }

    double totalLength = 0, weightedSum = 0;
    for (const auto &c : m_sensor) {
        totalLength += c.length;
        weightedSum += c.length * c.cte;
    }
    double totalCTE = weightedSum / totalLength;

    return QString("Total Length: %1 mm\nOverall CTE: %2")
        .arg(totalLength).arg(totalCTE, 0, 'f', 2);
}
