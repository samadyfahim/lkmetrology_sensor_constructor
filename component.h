#pragma once
#include <QString>

/**
 * @brief Represents a single sensor component
 */
struct Component {
    QString name;
    QString type;
    double length;      ///< in millimeters
    double cte;         ///< coefficient of thermal expansion
    QString imagePath;  ///< Qt resource path to component image
};
