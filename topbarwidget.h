#pragma once
#include <QWidget>

/**
 * @brief Widget showing logo and title at the top.
 */
class TopBarWidget : public QWidget {
    Q_OBJECT
public:
    explicit TopBarWidget(QWidget *parent = nullptr);
};
