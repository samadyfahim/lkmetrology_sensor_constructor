#include "cataloguetabswidget.h"
#include <QTabWidget>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QSize>

CatalogueTabsWidget::CatalogueTabsWidget(const CatalogueManager &manager, QWidget *parent)
    : QWidget(parent), m_catalogueManager(manager)
{
    m_tabs = new QTabWidget;
    m_tabs->setStyleSheet(
        "QTabWidget::pane { border: none; background:white; }"
        "QTabBar::tab { padding: 8px 16px; margin-bottom: 16px; font-weight: bold; background:white; }"
        "QTabBar::tab:selected { background-color: #eaeaea; border-radius: 6px; }"
        );

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_tabs);

    buildTabs();
}

void CatalogueTabsWidget::buildTabs()
{
    for (const auto &cat : m_catalogueManager.categories()) {
        QWidget *tabPage = new QWidget;
        QHBoxLayout *hLayout = new QHBoxLayout(tabPage);

        QScrollArea *scroll = new QScrollArea;
        scroll->setFixedHeight(120);
        scroll->setFrameStyle(QFrame::NoFrame);
        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        QWidget *scrollContent = new QWidget;
        QHBoxLayout *scrollLayout = new QHBoxLayout(scrollContent);
        scrollLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        int buttonCount = 0;
        for (const auto &c : m_catalogueManager.components()) {
            if (cat == "All" || c.type == cat) {
                QPushButton *btn = new QPushButton;
                btn->setFixedSize(120, 100);
                btn->setIcon(QIcon(c.imagePath));
                btn->setIconSize(QSize(100, 100));
                connect(btn, &QPushButton::clicked, this, [this, c]() {
                    emit componentSelected(c);
                });
                scrollLayout->addWidget(btn);
                buttonCount++;
            }
        }

        scrollContent->setMinimumWidth(buttonCount * 124);
        scroll->setWidget(scrollContent);

        hLayout->addWidget(scroll);
        tabPage->setFixedHeight(scroll->height());
        m_tabs->addTab(tabPage, cat);
    }
}
