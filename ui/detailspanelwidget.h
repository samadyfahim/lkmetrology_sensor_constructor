#pragma once
#include <QWidget>
#include "../models/component.h"

class QLabel;
class QPushButton;

class DetailsPanelWidget : public QWidget {
    Q_OBJECT
public:
    explicit DetailsPanelWidget(QWidget *parent = nullptr);
    void showDetails(const Component &comp);
    void showResult(const QString &result);

signals:
    void addClicked();
    void calculateClicked();
    void clearClicked();

private:
    QLabel *lblImage;
    QLabel *lblDetails;
    QLabel *lblCalcResult;
    QLabel *lblFormula;
    QPushButton *btnAdd;
    QPushButton *btnCalc;
    
    static QString formatComponentDetails(const QString &name, const QString &type, double length, double cte);
};
