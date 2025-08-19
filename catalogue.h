#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "component.h"
#include <QList>

inline QList<Component> getCatalogue() {
    return {
        {"Head", "Head", 37, 14, ":/images/Head"},
        {"ProbeA", "Probe", 45, 23.94, ":/images/ProbeA"},
        {"ProbeB", "Probe", 62, 10, ":/images/ProbeB"},
        {"ModuleA-1", "Module", 27, 23.94, ":/images/ModuleA-1"},
        {"ModuleA-2", "Module", 65, 23.94, ":/images/ModuleA-2"},
        {"ModuleA-3", "Module", 150, 23.94, ":/images/ModuleA-3"},
        {"ModuleB-1", "Module", 19.5, 12.5, ":/images/ModuleB-1"},
        {"1mm x 20mm", "Tip", 20, 16.2, ":/images/1mmX20mmTip"},
        {"3mm x 30mm", "Tip", 30, 16.2, ":/images/3mmX30mmTip"},
        {"5mm x 50mm", "Tip", 50, 16.2, ":/images/5mmX50mmTip"}
    };
}

#endif // CATALOGUE_H
