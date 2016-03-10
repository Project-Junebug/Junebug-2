#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

#include "lib.h"

/**
 * @brief main
 * @param argc Command line argument count
 * @param argv Command line arguments
 * @return
 */
int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    MainWindow w;
    w.show();


    return a.exec();
}
