#pragma once
#include <QWidget>
#include "cataloguemanager.h"

/**
 * @brief Widget showing tabs of component catalogue.
 */
class CatalogueTabsWidget : public QWidget {
    Q_OBJECT
public:
    explicit CatalogueTabsWidget(const CatalogueManager &manager, QWidget *parent = nullptr);

signals:
    void componentSelected(const Component &comp);

private:
    void buildTabs();

    const CatalogueManager &m_catalogueManager;
    class QTabWidget *m_tabs;
};
