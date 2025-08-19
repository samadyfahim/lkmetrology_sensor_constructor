#include "sensortabswidget.h"
#include <QScrollArea>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include "../constants.h"

SensorTabsWidget::SensorTabsWidget(const QList<Component> &catalogue, QWidget *parent)
    : QTabWidget(parent) {
    buildTabs(catalogue);
}

void SensorTabsWidget::buildTabs(const QList<Component> &catalogue) {
    QStringList categories = {"All"};
    categories.append(Constants::TYPE_ORDER);

    for (const auto &cat : categories) {
        QWidget *tabPage = new QWidget(this);
        QHBoxLayout *hLayout = new QHBoxLayout(tabPage);
        hLayout->setContentsMargins(0, 0, 0, 0);

        QScrollArea *scroll = new QScrollArea(tabPage);
        scroll->setWidgetResizable(true);
        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scroll->setFixedHeight(140); // big enough for the buttons

        QWidget *scrollContent = new QWidget(scroll);
        QHBoxLayout *scrollLayout = new QHBoxLayout(scrollContent);
        scrollLayout->setAlignment(Qt::AlignLeft);  // Align buttons to left
        scrollLayout->setSpacing(4);                 // spacing between buttons
        scrollLayout->setContentsMargins(4, 4, 4, 4);

        for (const auto &c : catalogue) {
            if (cat == "All" || c.type == cat) {
                QPushButton *btn = new QPushButton(scrollContent);
                btn->setFixedSize(120, 120);
                btn->setIcon(QIcon(c.imagePath));
                btn->setIconSize(QSize(100, 100));

                // Hover effect
                btn->setStyleSheet(R"(
                    QPushButton {
                        border: 1px solid #999;
                        border-radius: 8px;
                        background-color: #f0f0f0;
                    }
                    QPushButton:hover {
                        background-color: #d0e1ff;
                    }
                )");

                connect(btn, &QPushButton::clicked, this, [=]() { emit componentSelected(c); });
                scrollLayout->addWidget(btn);
            }
        }

        scrollContent->setLayout(scrollLayout);
        scroll->setWidget(scrollContent);
        hLayout->addWidget(scroll);

        addTab(tabPage, cat);
    }
}




