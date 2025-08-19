#include "mainwindow.h"
#include "mainwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Sensor Constructor");
    setCentralWidget(new MainWidget(this));
    resize(1200, 800);
}

MainWindow::~MainWindow() = default;
