#include <QApplication>
#include "gui_shell.h"

int main(int argc,char *argv[]) {
	QApplication app(argc,argv);
	
	Shell window;
	window.setWindowTitle("dxsh GUI shell");
	window.resize(600,400);
	window.show();
	
	return app.exec();
}
