#include "mainwidget.h"
#include "topbarwidget.h"
#include "cataloguetabswidget.h"
#include "sidepanelwidget.h"
#include "sensorview.h"
#include <QVBoxLayout>
#include <QSplitter>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setupLayout();
}

void MainWidget::setupLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Top bar
    m_topBar = new TopBarWidget;

    // Tabs
    m_tabs = new CatalogueTabsWidget(m_catalogueManager);

    // Side panel + SensorView in splitter
    m_sidePanel = new SidePanelWidget;
    m_sensorView = new SensorView;

    QSplitter *split = new QSplitter(Qt::Horizontal);
    split->addWidget(m_sidePanel);
    split->addWidget(m_sensorView);
    split->setSizes({420, 780}); // 35:65 ratio

    mainLayout->addWidget(m_topBar);
    mainLayout->addWidget(m_tabs, 1);
    mainLayout->addWidget(split, 9);

    // Connections
    connect(m_tabs, &CatalogueTabsWidget::componentSelected,
            this, &MainWidget::handleComponentSelected);
    connect(m_sensorView, &SensorView::componentClicked,
            this, &MainWidget::handleComponentSelected);
    connect(m_sidePanel, &SidePanelWidget::addClicked,
            this, &MainWidget::handleAddToSensor);
    connect(m_sidePanel, &SidePanelWidget::calculateClicked,
            this, &MainWidget::handleCalculate);
}

void MainWidget::handleComponentSelected(const Component &comp)
{
    m_currentSelection = comp;
    m_sidePanel->showDetails(comp);
}

void MainWidget::handleAddToSensor()
{
    if (m_currentSelection.name.isEmpty()) return;
    m_sensorModel.addComponent(m_currentSelection);
    m_sensorView->updateSensor(m_sensorModel);
}

void MainWidget::handleCalculate()
{
    m_sidePanel->showCalculation(m_sensorModel.calculateSummary());
}
