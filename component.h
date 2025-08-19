#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>

struct Component {
    QString name;
    QString type;
    double length;
    double cte;
    QString imagePath; // path to image file
};

#endif // COMPONENT_H
