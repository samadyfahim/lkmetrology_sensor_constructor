#pragma once
#include <QWidget>
#include "component.h"

/**
 * @brief Widget showing details, Add button, Calculate button and result.
 */
class SidePanelWidget : public QWidget {
    Q_OBJECT
public:
    explicit SidePanelWidget(QWidget *parent = nullptr);

    void showDetails(const Component &comp);
    void showCalculation(const QString &text);

signals:
    void addClicked();
    void calculateClicked();

private:
    class QLabel *m_lblDetails;
    class QLabel *m_lblCalcResult;
};
