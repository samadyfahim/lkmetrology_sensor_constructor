#include "mainwindow.h"
#include "topbarwidget.h"
#include "detailspanelwidget.h"
#include "sensortabswidget.h"
#include "sensorviewwidget.h"
#include "../models/catalogue.h"

#include <QVBoxLayout>
#include <QSplitter>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    catalogue = Catalogue::getAll();
    setupLayout();
    resize(1200, 800);
}

void MainWindow::setupLayout() {
    QWidget *central = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // --- TopBar ---
    topBar = new TopBarWidget;
    mainLayout->addWidget(topBar);

    // --- Tabs ---
    tabs = new SensorTabsWidget(catalogue);
    mainLayout->addWidget(tabs);

    // --- Split Panels ---
    QSplitter *split = new QSplitter(Qt::Horizontal);

    detailsPanel = new DetailsPanelWidget;
    sensorView = new SensorViewWidget;

    split->addWidget(detailsPanel);
    split->addWidget(sensorView);

    detailsPanel->setMinimumWidth(200);
    sensorView->setMinimumWidth(400);

    // --- Initial sizes (30% / 70%) ---
    split->setSizes({300, 700}); // initial pixel sizes

    mainLayout->addWidget(split, 1); // splitter takes remaining vertical space

    setCentralWidget(central);

    // --- Connections ---
    connect(tabs, &SensorTabsWidget::componentSelected, this, [=](const Component &c) {
        currentSelection = c;
        detailsPanel->showDetails(c);
    });

    connect(detailsPanel, &DetailsPanelWidget::addClicked, this, [=]() {
        if (currentSelection.name.isEmpty()) return;
        sensorController.addComponent(currentSelection);
        sensorView->displaySensor(sensorController.getSensor());
    });

    connect(detailsPanel, &DetailsPanelWidget::calculateClicked, this, [=]() {
        detailsPanel->showResult(sensorController.calculateResult());
    });

    connect(sensorView, &SensorViewWidget::componentClicked, this, [=](const Component &c) {
        currentSelection = c;
        detailsPanel->showDetails(c);
    });

    connect(sensorView, &SensorViewWidget::clearRequested, this, [=]() {
        sensorController.clearSensor();
        sensorView->displaySensor({});
    });


}


MainWindow::~MainWindow() = default;
