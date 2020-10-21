#include <string>
#include <sstream>
#include <QDebug>
#include <QString>

#include "interp.h"


const int LAGRANGEINDEX = 0;
const int NEWTONINDEX = 1;
const int LINEARINDEX = 2;
const int QUADRATICINDEX = 3;
const int CUBICINDEX = 4;
const int INTERPMETHODCOUNT = 5;



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
    
    pointsTable->horizontalHeader()->setDefaultSectionSize(80);
    pointsTable->verticalHeader()->setDefaultSectionSize(20);

    pointsTable->setHorizontalHeaderItem(0, new QTableWidgetItem("x"));
    pointsTable->setHorizontalHeaderItem(1, new QTableWidgetItem("y"));

    pointsTable->setFixedWidth(180);
}



void Dashboard::buttonGroupInit(){
    buttonGroup = new QGroupBox();
    QGridLayout *layout = new QGridLayout;


    QPushButton *addRowBtn = new QPushButton("Add");
    QPushButton *clearPointsBtn = new QPushButton("Clear");
    QPushButton *demoPointsBtn = new QPushButton("DemoPoints");
    QPushButton *formulateBtn = new QPushButton("Interpolate");
    // QPushButton *exitBtn = new QPushButton("Exit");

    connect(addRowBtn, &QPushButton::clicked, this, &Dashboard::addRow);
    connect(clearPointsBtn, &QPushButton::clicked, this, &Dashboard::clearPoints);
    connect(demoPointsBtn, &QPushButton::clicked, this, &Dashboard::demoPoints);
    connect(formulateBtn, &QPushButton::clicked, this, &Dashboard::formulate);
    // connect(exitBtn, &QPushButton::clicked, qApp, &QApplication::quit);

    layout->addWidget(addRowBtn, 0, 0);
    layout->addWidget(demoPointsBtn, 0, 1);
    layout->addWidget(clearPointsBtn, 1, 0);
    layout->addWidget(formulateBtn, 1, 1);

    buttonGroup->setLayout(layout);
}



void Dashboard::radioGroupInit(){
    radioGroup = new QGroupBox("Interpolation Methods");

    QGridLayout *layout = new QGridLayout;

    QRadioButton *LagrangeRadio = new QRadioButton("&Lagrange\nInterpolation");
    QRadioButton *NewtonRadio = new QRadioButton("&Newton's\nInterpolation");
    QRadioButton *LinearRadio = new QRadioButton("&Linear\nInterpolation");
    QRadioButton *QuadraticRadio = new QRadioButton("&Quadratic\nInterpolation");
    QRadioButton *CubicRadio = new QRadioButton("&Cubic\nInterpolation");

    InterpMethodRadios[LAGRANGEINDEX] = LagrangeRadio;
    InterpMethodRadios[NEWTONINDEX] = NewtonRadio;
    InterpMethodRadios[LINEARINDEX] = LinearRadio;
    InterpMethodRadios[QUADRATICINDEX] = QuadraticRadio;
    InterpMethodRadios[CUBICINDEX] = CubicRadio;

    LagrangeRadio->setChecked(true);

    layout->addWidget(LagrangeRadio, 0, 0);
    layout->addWidget(NewtonRadio, 1, 0);
    layout->addWidget(LinearRadio, 2, 0);
    layout->addWidget(QuadraticRadio, 3, 0);
    layout->addWidget(CubicRadio, 4, 0);

    radioGroup->setLayout(layout);
}



void Dashboard::evaluateAreaInit(){
    evaluateArea = new QGroupBox;
    QGridLayout *layout = new QGridLayout;

    QLabel *variableLabel = new QLabel("x=");
    variableLineEdit = new QLineEdit();
    // variableTextInput->setFixedWidth(50);
    // variableTextInput->setFixedHeight(20);
    variableLabel->resize(50, 20);

    valueLabel = new QLabel("f(x)=");

    layout->addWidget(variableLabel, 0, 0);
    layout->addWidget(variableLineEdit, 0, 1);
    layout->addWidget(valueLabel, 1, 0, 2, 1);

    evaluateArea->setFixedHeight(80);
    evaluateArea->setFixedWidth(160);

    evaluateArea->setLayout(layout);
    connect(variableLineEdit, &QLineEdit::textChanged, this, &Dashboard::evaluate);
}


Dashboard::Dashboard(QWidget *parent) : QWidget(parent) {
    QGridLayout *layout = new QGridLayout(this);

    chartInit();
    formulaInit();
    pointsTableInit();
    buttonGroupInit();
    radioGroupInit();
    evaluateAreaInit();

    layout->addWidget(chartView, 0, 0);
    layout->addWidget(formulaLabel, 1, 0);
    layout->addWidget(pointsTable, 0, 1);
    layout->addWidget(buttonGroup, 1, 1);
    layout->addWidget(radioGroup, 0, 2);
    layout->addWidget(evaluateArea, 1, 2);

    has_poly = false;
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


bool point_cmp(point point1, point point2){
    return point1.x < point2.x;
}


std::vector<point> Dashboard::getPoints(){
    std::vector<point> points;
    QTableWidgetItem *x_item;
    QTableWidgetItem *y_item;
    int r = 0;
    while(((x_item = pointsTable->item(r, 0)) && (y_item = pointsTable->item(r, 1)))) {
        if ( x_item->text().isEmpty() || y_item->text().isEmpty()) break;
        double x = x_item->text().toDouble();
        double y = y_item->text().toDouble();
        points.push_back({x, y});
        r++;
    }

    std::sort(points.begin(), points.end(), point_cmp);
    return points;
}


void Dashboard::draw(){
	QScatterSeries *series0 = new QScatterSeries();
	series0->setName("points");

	series0->setMarkerSize(10);
    series0->setColor(QColor(0, 0, 0, 255));

    std::vector<point> points = getPoints();
    for (auto it = points.begin(); it != points.end(); it++){
        series0->append(it->x, it->y);
    }

	chartView->chart()->addSeries(series0);

    // series0->attachAxis(axisX);
    // series0->attachAxis(axisY);

	chartView->chart()->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
}



std::string poly2str(Polynomial poly){
    /*
    std::ostringstream ss;
    ss << Lagrange_interp_poly;

    std::string polyString = ss.str();
    std::cout << polyString << std::endl;
    QString polyQString = QString::fromStdString(polyString);
    qDebug() << polyQString;
    formulaLabel->setText(polyQString);*/
    
    // formulaLabel->setText(QString::number(Lagrange_interp_poly.evaluate(0.596)));
    std::string polyString("");
    std::vector<Monomial> poly_terms = poly.terms;
    for(auto term_it = poly_terms.begin(); term_it != poly_terms.end(); term_it++){
        if (term_it->coef == 0.0) continue;
        if ((term_it->coef > 0) && (term_it != poly_terms.begin()))
            polyString += "+";
        polyString += std::to_string(term_it->coef) + "x^" + std::to_string(term_it->exp);
        if (term_it != poly_terms.end()) polyString += " "; 
    }
    return polyString;
}


std::string polyint2str(polyint poly_int) {
    std::string polyString = poly2str(poly_int.poly);
    std::string intervalString = "[" + std::to_string(poly_int.left) + "," + std::to_string(poly_int.right) + "]";
    return polyString + " " +  intervalString + "\n";
}


void Dashboard::formulate(){
    int method_index = 0;
    interp_polyints.clear();

    while (method_index < INTERPMETHODCOUNT){
        if (InterpMethodRadios[method_index]->isChecked()){
            break;
        }
        method_index++;
    }

    std::vector<point> points = getPoints();

    if (method_index == LAGRANGEINDEX || method_index == NEWTONINDEX){
        interp_polyints.push_back({
            method_index == LAGRANGEINDEX ? Lagrange_interp(points) : Newton_interp(points),
            points.front().x,
            points.back().x
        });
    } else {
        int deg = method_index - 1;
        for(int i = 0; i < points.size()-deg; i++) {
            std::vector<point> local_points(points.begin()+i, points.begin()+i+deg+1);
            interp_polyints.push_back({
                Lagrange_interp(local_points),
                points[i].x,
                points[i+deg].x
            });
        }
    }

    std::string polyintsString = "";
    for (auto it = interp_polyints.begin(); it != interp_polyints.end(); it++){
        polyintsString += polyint2str(*it);
    }
    formulaLabel->clear();
	formulaLabel->setText(QString::fromStdString(polyintsString));
    has_poly = true;
}



void Dashboard::evaluate(){
    if (has_poly){
        double x = variableLineEdit->text().toDouble();
        double y = 0;
        // qDebug() << variableLineEdit->text() << " ";
        // std::cout << v << std::endl;

        for (auto it = interp_polyints.begin(); it != interp_polyints.end(); it++){
        	if (it->left <= x && x <= it->right){
        		y = it->poly.evaluate(x);
        		break;
        	}
        }
        if (x < interp_polyints.front().left) {
            y = interp_polyints.front().poly.evaluate(x);
        }
        if (x > interp_polyints.back().right) {
            y = interp_polyints.back().poly.evaluate(x);
        }
        valueLabel->setText(QString::number(y));
    }
}



void Dashboard::err(QString msg){
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}




