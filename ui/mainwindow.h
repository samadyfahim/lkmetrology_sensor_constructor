#pragma once
#include <QMainWindow>
#include "../controllers/sensorcontroller.h"
#include "../models/component.h"

class TopBarWidget;
class DetailsPanelWidget;
class SensorTabsWidget;
class SensorViewWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupLayout();

    TopBarWidget *topBar;
    DetailsPanelWidget *detailsPanel;
    SensorTabsWidget *tabs;
    SensorViewWidget *sensorView;

    QList<Component> catalogue;
    Component currentSelection;
    SensorController sensorController;
};
