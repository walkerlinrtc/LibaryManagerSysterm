#include "mainwindow.h"
#include <QApplication>
#include "document.h"

int main(int argc, char *argv[]) {
    Document::GetInstance()->readData();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
