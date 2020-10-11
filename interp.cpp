#include <string>

#include "interp.h"



void Dashboard::chartInit(){
    QChart *chart = new QChart();
    // chart->setTitle("Function Graph"); 
    chart->createDefaultAxes();
    // chart->axes(Qt::Horizontal).first()->setRange(0, 20);
    // chart->axes(Qt::Vertical).first()->setRange(0, 10);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}


void Dashboard::formulaInit(){
    formulaLabel = new QLabel();
}



void Dashboard::pointsTableInit(){
    pointsTable = new QTableWidget(10, 2);
    
    pointsTable->horizontalHeader()->setDefaultSectionSize(60);
    pointsTable->verticalHeader()->setDefaultSectionSize(20);
    pointsTable->setFixedWidth(144);

    QTableWidgetItem *newItem = new QTableWidgetItem("newItem");

    pointsTable->setItem(1, 1, newItem);
}



void Dashboard::buttonGroupInit(){
    buttonGroup = new QGroupBox();
    QGridLayout *layout = new QGridLayout;


    QPushButton *addRowBtn = new QPushButton("Add");
    QPushButton *clearPointsBtn = new QPushButton("Clear");
    QPushButton *demoPointsBtn = new QPushButton("Demo");
    // QPushButton *exitBtn = new QPushButton("Exit");

    connect(addRowBtn, &QPushButton::clicked, this, &Dashboard::addRow);
    connect(clearPointsBtn, &QPushButton::clicked, this, &Dashboard::clearPoints);
    connect(demoPointsBtn, &QPushButton::clicked, this, &Dashboard::demoPoints);
    // connect(exitBtn, &QPushButton::clicked, qApp, &QApplication::quit);


    layout->addWidget(addRowBtn, 0, 0);
    layout->addWidget(demoPointsBtn, 0, 1);
    layout->addWidget(clearPointsBtn, 1, 0);

    buttonGroup->setLayout(layout);
}



void Dashboard::radioGroupInit(){
    radioGroup = new QGroupBox("Interpolation Methods");
}



Dashboard::Dashboard(QWidget *parent) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);

    chartInit();
    formulaInit();
    pointsTableInit();
    buttonGroupInit();
    radioGroupInit();

    layout->addWidget(chartView, 0, 0);
    layout->addWidget(formulaLabel, 1, 0);
    layout->addWidget(pointsTable, 0, 1);
    layout->addWidget(buttonGroup, 1, 1);
    // layout->addWidget(radioGroup, 0, 2, 2, 1);
}


void Dashboard::addRow() {
    pointsTable->insertRow(pointsTable->rowCount());
}


void Dashboard::clearPoints(){

}


void Dashboard::demoPoints(){

}


