#include <vector>
#include <utility>

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

	std::vector<point> points;

	void chartInit();
	void formulaInit();
	void pointsTableInit();
	void buttonGroupInit();
	void radioGroupInit();

	void addRow();
	void clearPoints();
	void demoPoints();

public:
	Dashboard(QWidget *parent = 0);
};

