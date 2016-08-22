#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

/**
 * @brief main
 * @param argc Command line argument count
 * @param argv Command line arguments
 * @return
 */
int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    MainWindow w;
    w.setFixedSize(w.size());
    w.show();

    return a.exec();
}
