#pragma once
#include <QWidget>
#include "cataloguemanager.h"
#include "sensormodel.h"

class TopBarWidget;
class CatalogueTabsWidget;
class SidePanelWidget;
class SensorView;

/**
 * @brief Main container widget holding all sections.
 */
class MainWidget : public QWidget {
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private slots:
    void handleComponentSelected(const Component &comp);
    void handleAddToSensor();
    void handleCalculate();

private:
    void setupLayout();

    CatalogueManager m_catalogueManager;
    SensorModel m_sensorModel;

    TopBarWidget *m_topBar;
    CatalogueTabsWidget *m_tabs;
    SidePanelWidget *m_sidePanel;
    SensorView *m_sensorView;

    Component m_currentSelection;
};
