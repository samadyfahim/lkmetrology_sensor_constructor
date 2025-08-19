#pragma once
#include <QMainWindow>

class MainWidget;

/**
 * @brief The main application window (orchestrator only).
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};
