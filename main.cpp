#include <QApplication>
#include "interp.h"

int main(int argc, char *argv[]){

	QApplication app(argc, argv);

	Dashboard window;

	window.resize(854, 480);
	window.setWindowTitle("Click");
	window.show();

	return app.exec();
}
