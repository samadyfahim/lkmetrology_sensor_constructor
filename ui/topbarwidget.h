#pragma once
#include <QWidget>

class QLabel;

class TopBarWidget : public QWidget {
    Q_OBJECT
public:
    explicit TopBarWidget(QWidget *parent = nullptr);

private:
    QLabel *logo;
    QLabel *title;
};
