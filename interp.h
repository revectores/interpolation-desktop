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
#include <QtCharts>

#include <QMessageBox>



typedef struct point {
	double x;
	double y;
} point;


class Dashboard : public QWidget {
private:
	std::vector<point> points;

	QChartView* chartInit();
	QLabel* formulaInit();
	QGroupBox* pointsViewInit();
	QGroupBox* buttonGroupInit();
	QGroupBox* radioGroupInit();

	void addPoint();
	void deletePoint();
	void clearPoint();
	void demoPoint();

public:
	Dashboard(QWidget *parent = 0);
};

