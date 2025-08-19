#include "topbarwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

TopBarWidget::TopBarWidget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    QLabel *logo = new QLabel;
    logo->setPixmap(QPixmap(":/logo/logo").scaled(200, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel *title = new QLabel("Sensor Constructor");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color:#012f6c;");

    layout->addWidget(logo);
    layout->addWidget(title);
    layout->addStretch();
}
