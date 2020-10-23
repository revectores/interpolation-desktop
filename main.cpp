#include <QApplication>
#include "interp.h"

int main(int argc, char *argv[]){

	QApplication app(argc, argv);

	Dashboard window;

	window.resize(1080, 550);
	window.setWindowTitle("Interpolation");
	window.show();

	return app.exec();
}
