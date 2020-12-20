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
#include <revector/poly.h>


typedef struct polyint_ {
	Polynomial poly;
	double left;
	double right;
} polyint;



class Dashboard : public QWidget {
private:
	QChartView* chartView;
	QValueAxis* axisX;
	QValueAxis* axisY;
	QLabel* formulaLabel;
	QTableWidget* pointsTable;
	QGroupBox* buttonGroup;
	QGroupBox* radioGroup;
	QGroupBox* evaluateArea;
	QLineEdit* variableLineEdit;
	QRadioButton* InterpMethodRadios[5];
	QLabel* valueLabel;
	std::vector<polyint> interp_polyints;
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

