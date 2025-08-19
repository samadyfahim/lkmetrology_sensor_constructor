#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QSplitter>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGroupBox>
#include <QStyle>
#include <QPalette>
#include <QGraphicsDropShadowEffect>
#include "SensorGraphicsItem.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Sensor Constructor");

    catalogue = getCatalogue();

    QWidget *central = new QWidget;
    central->setStyleSheet("background-color: white;");
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Top row: logo + title
    QHBoxLayout *topRow = new QHBoxLayout;
    topRow->setSpacing(10);
    topRow->setContentsMargins(0, 0, 0, 0);

    QLabel *logo = new QLabel;
    logo->setPixmap(QPixmap(":/logo/logo").scaled(200, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logo->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    QLabel *title = new QLabel("Sensor Constructor");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color:#012f6c;");
    title->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    topRow->addWidget(logo);
    topRow->addWidget(title);
    topRow->addStretch(); // pushes everything to the left

    mainLayout->addLayout(topRow);

    // Tabs
    tabs = new QTabWidget;
    tabs->setStyleSheet(
        "QTabWidget::pane { border: none; background:white; }"
        "QTabBar::tab { padding: 8px 16px; margin-bottom: 16px; font-weight: bold; background:white; }"
        "QTabBar::tab:selected { background-color: #eaeaea; border-radius: 6px; }"
        );
    buildTabs();

    // Split
    QSplitter *split = new QSplitter(Qt::Horizontal);
    split->setStyleSheet("background:white; padding: 0px; margin: 0px; border:none;");

    // Left
    QWidget *leftPanel = new QWidget;
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPanel);

    lblDetails = new QLabel("Select an item");
    lblDetails->setWordWrap(true);
    lblDetails->setStyleSheet("background:white; font-size:14px;");
    leftLayout->addWidget(lblDetails);

    btnAdd = new QPushButton("Add to Sensor");
    btnAdd->setStyleSheet(
        "padding: 12px; font-size: 14px; border-radius: 8px;"
        "background-color: #012f6c; color: white; border:none;");
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::addToSensor);
    leftLayout->addWidget(btnAdd);

    QPushButton *btnCalc = new QPushButton("Calculate");
    btnCalc->setStyleSheet(
        "padding: 12px; font-size: 14px; border-radius: 8px;"
        "background-color: #e53c2d; color: white; border:none;");
    connect(btnCalc, &QPushButton::clicked, this, &MainWindow::calculate);
    leftLayout->addWidget(btnCalc);

    lblCalcResult = new QLabel;
    lblCalcResult->setStyleSheet("background:white; font-size:14px; color:#333;");
    leftLayout->addWidget(lblCalcResult);

    leftLayout->addStretch();

    // Right
    scene = new QGraphicsScene;
    view = new QGraphicsView(scene);
    view->setStyleSheet("background:white; border:1px solid #ccc;");
    view->setFixedHeight(400);

    // After you add leftPanel and view to the splitter:
    split->addWidget(leftPanel);
    split->addWidget(view);

    // Enforce 35% : 65% ratio
    QList<int> sizes;
    sizes << int(0.35 * 1200) << int(0.65 * 1200);
    split->setSizes(sizes);

    mainLayout->addWidget(tabs, 1); // smaller height
    mainLayout->addWidget(split, 9);

    setCentralWidget(central);
    resize(1200, 800);
}


void MainWindow::buildTabs() {
    QStringList categories = {"All", "Head", "Probe", "Module", "Tip"};

    for (auto &cat : categories) {
        QWidget *tabPage = new QWidget;
        QHBoxLayout *hLayout = new QHBoxLayout(tabPage);
        hLayout->setContentsMargins(0, 0, 0, 0);
        hLayout->setSpacing(0);

        // Scroll area (horizontal only)
        QScrollArea *scroll = new QScrollArea;
        scroll->setFixedHeight(120);
        scroll->setFrameStyle(QFrame::NoFrame);
        scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        // Container for buttons
        QWidget *scrollContent = new QWidget;
        QHBoxLayout *scrollLayout = new QHBoxLayout(scrollContent);
        scrollLayout->setContentsMargins(0, 0, 0, 0);
        scrollLayout->setSpacing(4);
        scrollLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

        int buttonCount = 0;
        for (auto &c : catalogue) {
            if (cat == "All" || c.type == cat) {
                QPushButton *btn = new QPushButton;
                btn->setFixedSize(120, 100);
                btn->setIcon(QIcon(c.imagePath));
                btn->setIconSize(QSize(100, 100));
                btn->setStyleSheet(
                    "QPushButton { background:white; border:none; }"
                    "QPushButton:hover { background:#f0f0f0; border-radius:6px; }"
                    );

                connect(btn, &QPushButton::clicked, this, [=]() {
                    showDetails(c);
                });

                scrollLayout->addWidget(btn);
                buttonCount++;
            }
        }

        scrollContent->setLayout(scrollLayout);

        // 🔑 Force scrollContent wider than the viewport if needed
        int minWidth = buttonCount * (100 + 4); // button size + spacing
        scrollContent->setMinimumWidth(minWidth);

        scroll->setWidget(scrollContent);
        scroll->setWidgetResizable(false); // don't resize to fit viewport

        hLayout->addWidget(scroll);
        tabPage->setLayout(hLayout);

        tabPage->setFixedHeight(scroll->height());
        tabs->addTab(tabPage, cat);
    }
}





void MainWindow::showDetails(const Component &comp) {
    currentSelection = comp;
    lblDetails->setText(
        QStringLiteral("Name: %1\nType: %2\nLength: %3 mm\nCTE: %4")
            .arg(comp.name,
                 comp.type,
                 QString::number(comp.length),
                 QString::number(comp.cte, 'f', 2)) // 2 decimals for clarity
        );

}

void MainWindow::addToSensor() {
    if (currentSelection.name.isEmpty()) return;
    QStringList typeOrder = {"Head", "Probe", "Module", "Tip"};

    for (int i = 0; i < sensor.size(); ++i) {
        if (sensor[i].type == currentSelection.type) {
            sensor.removeAt(i);
            break;
        }
    }

    int insertIndex = 0;
    for (; insertIndex < sensor.size(); ++insertIndex) {
        if (typeOrder.indexOf(currentSelection.type) <
            typeOrder.indexOf(sensor[insertIndex].type)) break;
    }
    sensor.insert(insertIndex, currentSelection);

    scene->clear();
    sensorYOffset = 0;
    double totalHeight = 0;
    for (auto &c : sensor) totalHeight += QPixmap(c.imagePath).height();

    double scale = (totalHeight > view->height()) ? (view->height() / totalHeight) : 0.4;

    for (auto &c : sensor) {
        QPixmap pix(c.imagePath);
        QPixmap scaled = pix.scaled(pix.width()*scale, pix.height()*scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        auto *item = new SensorGraphicsItem(scaled, c);
        scene->addItem(item);
        item->setPos(0, sensorYOffset);

        // Click to show details
        connect(item, &SensorGraphicsItem::clicked, this, &MainWindow::showDetails);


        sensorYOffset += scaled.height();
    }
}

void MainWindow::calculate() {
    QStringList required = {"Head", "Probe", "Module", "Tip"};
    for (auto &r : required)
        if (std::none_of(sensor.begin(), sensor.end(), [&](auto &c){ return c.type==r; })) {
            lblCalcResult->setText("⚠️ Please select Head, Probe, Module, and Tip before calculating.");
            return;
        }

    double totalLength = 0, weightedSum = 0;
    for (auto &c : sensor) {
        totalLength += c.length;
        weightedSum += c.length * c.cte;
    }
    double totalCTE = weightedSum / totalLength;

    lblCalcResult->setText(
        QString("Total Length: %1 mm\nOverall CTE: %2").arg(totalLength).arg(totalCTE, 0, 'f', 2)
        );
}

MainWindow::~MainWindow() = default;
