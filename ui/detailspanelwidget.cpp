#include "detailspanelwidget.h"
#include "../constants.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

DetailsPanelWidget::DetailsPanelWidget(QWidget *parent) : QWidget(parent) {
    auto *mainLayout = new QVBoxLayout(this); // main vertical layout

    // Top horizontal split
    auto *splitLayout = new QHBoxLayout();

    // Left side: details + formula
    auto *leftLayout = new QVBoxLayout();
    lblDetails = new QLabel("Select an item");
    leftLayout->addWidget(lblDetails);

    lblFormula = new QLabel(
        "<b>Overall CTE formula:</b><br>"
        "CTE<sub>total</sub> = "
        "(&Sigma; L<sub>i</sub> × CTE<sub>i</sub>) / (&Sigma; L<sub>i</sub>)"
        );
    lblFormula->setTextFormat(Qt::RichText);
    lblFormula->setAlignment(Qt::AlignLeft);
    lblFormula->setStyleSheet("color: #012f6c; font-style: italic; margin-bottom: 8px;");
    leftLayout->addWidget(lblFormula);
    leftLayout->addStretch(); // push content to top

    // Right side: image
    lblImage = new QLabel;
    lblImage->setFixedSize(120, 120);
    lblImage->setAlignment(Qt::AlignCenter);

    splitLayout->addLayout(leftLayout, 1); // left side stretches
    splitLayout->addWidget(lblImage);      // right side fixed size

    mainLayout->addLayout(splitLayout);

    // Bottom: buttons + calculation result
    btnAdd = new QPushButton("Add to Sensor");
    btnAdd->setStyleSheet(Constants::BUTTON_STYLE_PRIMARY);
    connect(btnAdd, &QPushButton::clicked, this, &DetailsPanelWidget::addClicked);

    btnCalc = new QPushButton("Calculate");
    btnCalc->setStyleSheet(Constants::BUTTON_STYLE_SECONDARY);
    connect(btnCalc, &QPushButton::clicked, this, &DetailsPanelWidget::calculateClicked);

    lblCalcResult = new QLabel;
    lblCalcResult->setWordWrap(true);              // enable word wrap
    lblCalcResult->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // allow vertical expansion

    auto *bottomLayout = new QVBoxLayout();
    bottomLayout->addWidget(btnAdd);
    bottomLayout->addWidget(btnCalc);
    bottomLayout->addWidget(lblCalcResult);

    mainLayout->addLayout(bottomLayout);

}



void DetailsPanelWidget::showDetails(const Component &comp) {
    lblDetails->setText(formatComponentDetails(comp.name, comp.type, comp.length, comp.cte));
    QPixmap pix(comp.imagePath);
    lblImage->setPixmap(pix.scaled(lblImage->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


void DetailsPanelWidget::showResult(const QString &result) {
    lblCalcResult->setText(result);
}

QString DetailsPanelWidget::formatComponentDetails(const QString &name, const QString &type, double length, double cte) {
    return QString("Name:   %1\n"
                   "Type:   %2\n"
                   "Length: %3 mm\n"
                   "CTE:    %4 µm/m·K")
        .arg(name, type, QString::number(length, 'f', 2), QString::number(cte, 'f', 2));
}



