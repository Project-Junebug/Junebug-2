#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent - Parent QWidget
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow(){
    delete ui;
}
