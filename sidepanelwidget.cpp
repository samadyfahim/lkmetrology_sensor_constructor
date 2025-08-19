#include "sidepanelwidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

SidePanelWidget::SidePanelWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_lblDetails = new QLabel("Select an item");
    m_lblDetails->setWordWrap(true);
    layout->addWidget(m_lblDetails);

    QPushButton *btnAdd = new QPushButton("Add to Sensor");
    connect(btnAdd, &QPushButton::clicked, this, &SidePanelWidget::addClicked);
    layout->addWidget(btnAdd);

    QPushButton *btnCalc = new QPushButton("Calculate");
    connect(btnCalc, &QPushButton::clicked, this, &SidePanelWidget::calculateClicked);
    layout->addWidget(btnCalc);

    m_lblCalcResult = new QLabel;
    layout->addWidget(m_lblCalcResult);
    layout->addStretch();
}

void SidePanelWidget::showDetails(const Component &comp)
{
    m_lblDetails->setText(QString("Name: %1\nType: %2\nLength: %3 mm\nCTE: %4")
                              .arg(comp.name, comp.type, QString::number(comp.length), QString::number(comp.cte, 'f', 2)));
}

void SidePanelWidget::showCalculation(const QString &text)
{
    m_lblCalcResult->setText(text);
}
