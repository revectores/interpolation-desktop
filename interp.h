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



typedef struct point {
	double x;
	double y;
} point;


class Dashboard : public QWidget {
private:
	QChartView* chartView;
	QLabel* formulaLabel;
	QTableWidget* pointsTable;
	QGroupBox* buttonGroup;
	QGroupBox* radioGroup;

	point points[MAXIMUM_ROW];

	void chartInit();
	void formulaInit();
	void pointsTableInit();
	void buttonGroupInit();
	void radioGroupInit();

	void addRow();
	void clearPoints();
	void demoPoints();
	void draw();

	void cellChangeHandler();

	void err(QString msg);

public:
	Dashboard(QWidget *parent = 0);
};

