#pragma once
#include "component.h"
#include <QList>
#include <QStringList>

/**
 * @brief Handles loading and providing access to the component catalogue
 */
class CatalogueManager {
public:
    CatalogueManager();
    const QList<Component>& components() const { return m_catalogue; }
    QStringList categories() const;

private:
    QList<Component> m_catalogue;
};
