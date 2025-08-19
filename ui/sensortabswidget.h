#pragma once
#include <QTabWidget>
#include "../models/component.h"

class SensorTabsWidget : public QTabWidget {
    Q_OBJECT
public:
    explicit SensorTabsWidget(const QList<Component> &catalogue, QWidget *parent = nullptr);

signals:
    void componentSelected(const Component &comp);

private:
    void buildTabs(const QList<Component> &catalogue);
};
