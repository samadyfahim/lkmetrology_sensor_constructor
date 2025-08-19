#pragma once
#include <QString>

// Represents a single component
struct Component {
    QString name;
    QString type;
    double length;
    double cte;
    QString imagePath;
};
