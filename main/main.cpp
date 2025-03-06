#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Calculator");
    window.resize(250, 300);
    window.show();

    return app.exec();
}
