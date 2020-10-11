#include "interp.h"


QChartView* Dashboard::chartInit(){
    QChart *chart = new QChart();
    chart->setTitle("Function Graph"); 
    chart->createDefaultAxes();
    // chart->axes(Qt::Horizontal).first()->setRange(0, 20);
    // chart->axes(Qt::Vertical).first()->setRange(0, 10);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}



QLabel* Dashboard::formulaInit(){
    QLabel *formulaLabel = new QLabel();
    return formulaLabel;
}



QGroupBox* Dashboard::pointsViewInit(){
    QGroupBox *groupBox = new QGroupBox("Points");
    return groupBox;
}



QGroupBox* Dashboard::buttonGroupInit(){
    QGroupBox *groupBox = new QGroupBox();
    QGridLayout *layout = new QGridLayout;


    QPushButton *addBtn = new QPushButton("Add");


    connect(addBtn, &QPushButton::clicked, this, &Dashboard::addPoint);


    layout->addWidget(addBtn, 0, 0);
    groupBox->setLayout(layout);

    return groupBox;
}



QGroupBox* Dashboard::radioGroupInit(){
    QGroupBox *groupBox = new QGroupBox("Interpolation Methods");
    return groupBox;
}



Dashboard::Dashboard(QWidget *parent) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);

    QChartView *chart = chartInit();
    QLabel *formulaLabel = formulaInit();
    QGroupBox *pointsView = pointsViewInit();
    QGroupBox *buttonGroup = buttonGroupInit();
    QGroupBox *radioGroup = radioGroupInit();

    layout->addWidget(chart, 0, 0);
    layout->addWidget(formulaLabel, 1, 0);
    layout->addWidget(pointsView, 0, 1);
    layout->addWidget(buttonGroup, 1, 1);
    layout->addWidget(radioGroup, 0, 2, 2, 1);
}



void Dashboard::addPoint() {
    QMessageBox msgBox;
    msgBox.setText("Click event test.");
    msgBox.exec();
}


void Dashboard::deletePoint() {


}

void Dashboard::clearPoint(){


}



void Dashboard::demoPoint(){

}


