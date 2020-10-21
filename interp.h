#include "poly.h"
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>

#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include <QTableWidget>
#include <QtCharts>

#include <QMessageBox>
#define MAXIMUM_ROW 1000


class Dashboard : public QWidget {
private:
	QChartView* chartView;
	QLabel* formulaLabel;
	QTableWidget* pointsTable;
	QGroupBox* buttonGroup;
	QGroupBox* radioGroup;
	QGroupBox* evaluateArea;
	QLineEdit* variableLineEdit;
	QLabel* valueLabel;
	Polynomial poly;
	bool has_poly;

	std::vector<point> getPoints();
	void chartInit();
	void formulaInit();
	void pointsTableInit();
	void buttonGroupInit();
	void radioGroupInit();
	void evaluateAreaInit();

	void addRow();
	void clearPoints();
	void demoPoints();
	void draw();
	void formulate();
	void evaluate();

	void cellChangeHandler();

	void err(QString msg);

public:
	Dashboard(QWidget *parent = 0);
};

