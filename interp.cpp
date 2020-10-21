#include <string>

#include "interp.h"



void Dashboard::chartInit(){
    QChart *chart = new QChart();
    // chart->setTitle("Function Graph"); 
    // chart->createDefaultAxes();
    // chart->axes(Qt::Horizontal).first()->setRange(0, 20);
    // chart->axes(Qt::Vertical).first()->setRange(0, 10);


    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QValueAxis *axisX = new QValueAxis();
    QValueAxis *axisY = new QValueAxis();

    axisX->setTickCount(10);
    axisY->setTickCount(10);

    chartView->chart()->addAxis(axisX, Qt::AlignBottom);
    chartView->chart()->addAxis(axisY, Qt::AlignLeft);

    QScatterSeries *series0 = new QScatterSeries();
    chartView->chart()->addSeries(series0);
    series0->attachAxis(axisX);
    series0->attachAxis(axisY);
}


void Dashboard::formulaInit(){
    formulaLabel = new QLabel();
}



void Dashboard::pointsTableInit(){
    pointsTable = new QTableWidget(10, 2);
    
    pointsTable->horizontalHeader()->setDefaultSectionSize(60);
    pointsTable->verticalHeader()->setDefaultSectionSize(20);

    pointsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("x"));
    pointsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("y"));

    pointsTable->setFixedWidth(144);

    connect(pointsTable, &QTableWidget::cellChanged, this, &Dashboard::cellChangeHandler); 
}



void Dashboard::buttonGroupInit(){
    buttonGroup = new QGroupBox();
    QGridLayout *layout = new QGridLayout;


    QPushButton *addRowBtn = new QPushButton("Add");
    QPushButton *clearPointsBtn = new QPushButton("Clear");
    QPushButton *demoPointsBtn = new QPushButton("Demo");
    QPushButton *drawBtn = new QPushButton("Demo");
    // QPushButton *exitBtn = new QPushButton("Exit");

    connect(addRowBtn, &QPushButton::clicked, this, &Dashboard::addRow);
    connect(clearPointsBtn, &QPushButton::clicked, this, &Dashboard::clearPoints);
    connect(demoPointsBtn, &QPushButton::clicked, this, &Dashboard::demoPoints);
    connect(drawBtn, &QPushButton::clicked, this, &Dashboard::draw);
    // connect(exitBtn, &QPushButton::clicked, qApp, &QApplication::quit);


    layout->addWidget(addRowBtn, 0, 0);
    layout->addWidget(demoPointsBtn, 0, 1);
    layout->addWidget(clearPointsBtn, 1, 0);
    layout->addWidget(drawBtn, 1, 1);

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
    if (pointsTable->rowCount() >= MAXIMUM_ROW) {
        err("Exceed maximum rows");
        return;
    }
    pointsTable->insertRow(pointsTable->rowCount());
}


void Dashboard::clearPoints(){
	int rowCount = pointsTable->rowCount();
	for (int r = 0; r < rowCount; r++){
		pointsTable->setItem(r, 0, new QTableWidgetItem(""));
		pointsTable->setItem(r, 1, new QTableWidgetItem(""));
	}
}


void Dashboard::demoPoints(){
	point demo_points[6] = {
		{0.4, 0.41075},
		{0.55, 0.57815},
		{0.65, 0.69675},
		{0.80, 0.90},
		{0.95, 1.00},
		{1.05, 1.25382}
	};

	for (int r = 0; r < sizeof(demo_points)/sizeof(demo_points[0]); r++){
		pointsTable->setItem(r, 0, new QTableWidgetItem(QString::number(demo_points[r].x)));
		pointsTable->setItem(r, 1, new QTableWidgetItem(QString::number(demo_points[r].y)));
	}
}


void Dashboard::cellChangeHandler(){
    /*
    QMessageBox msgBox;

    msgBox.setText("found u!");
    msgBox.exec();
    */
}


void Dashboard::preprocessor(){


}


void Dashboard::draw(){
	QScatterSeries *series0 = new QScatterSeries();
	series0->setName("points");

	series0->setMarkerSize(10);
    series0->setColor(QColor(0, 0, 0, 255));

	for (int r = 0; r < 6; r ++){
		series0->append(pointsTable->item(r, 0)->text().toDouble(),
					    pointsTable->item(r, 1)->text().toDouble());
	}

	chartView->chart()->addSeries(series0);

    // series0->attachAxis(axisX);
    // series0->attachAxis(axisY);

	chartView->chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
}


void Dashboard::err(QString msg){
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}