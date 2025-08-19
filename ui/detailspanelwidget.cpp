#include "detailspanelwidget.h"
#include "../constants.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

DetailsPanelWidget::DetailsPanelWidget(QWidget *parent) : QWidget(parent) {
    auto *layout = new QVBoxLayout(this);

    lblDetails = new QLabel("Select an item");
    layout->addWidget(lblDetails);

    btnAdd = new QPushButton("Add to Sensor");
    btnAdd->setStyleSheet(Constants::BUTTON_STYLE_PRIMARY);
    connect(btnAdd, &QPushButton::clicked, this, &DetailsPanelWidget::addClicked);
    layout->addWidget(btnAdd);

    btnCalc = new QPushButton("Calculate");
    btnCalc->setStyleSheet(Constants::BUTTON_STYLE_SECONDARY);
    connect(btnCalc, &QPushButton::clicked, this, &DetailsPanelWidget::calculateClicked);
    layout->addWidget(btnCalc);

    lblCalcResult = new QLabel;
    layout->addWidget(lblCalcResult);

    layout->addStretch();
}

void DetailsPanelWidget::showDetails(const Component &comp) {
    lblDetails->setText(formatComponentDetails(comp.name, comp.type, comp.length, comp.cte));
}

void DetailsPanelWidget::showResult(const QString &result) {
    lblCalcResult->setText(result);
}

QString DetailsPanelWidget::formatComponentDetails(const QString &name, const QString &type, double length, double cte) {
    return QString("Name: %1\nType: %2\nLength: %3 mm\nCTE: %4 µm/m·K")
            .arg(name)
            .arg(type)
            .arg(length)
            .arg(cte);
}
