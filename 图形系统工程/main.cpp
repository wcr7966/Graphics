#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
