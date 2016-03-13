#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

/**
 * @brief MainWindow::MainWindow
 * @param parent - Parent QWidget
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    update();
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_info_nextButton_clicked(){
    m_pageList.checkAnswer();
    update();
}

void MainWindow::on_text_nextButton_clicked(){
    if(m_pageList.checkAnswer(ui->text_lineEdit->text())){
        update();
    } else {
        incorrect();
    }
}

/**
 * @brief MainWindow::update
 * Updates the window to show m_pageList.getDisplayData();
 */
void MainWindow::update(){
    m_current=m_pageList.getDisplayData();
    switch (m_current.s_type) {
    case PageType::Info:
        ui->stackedWidget->setCurrentWidget(ui->info);
        ui->info_label->setText(m_current.s_text);
        break;
    case PageType::Question:
        ui->stackedWidget->setCurrentWidget(ui->text);
        ui->text_label->setText(m_current.s_text);
        ui->text_lineEdit->setPlaceholderText(m_current.s_prompt);
        break;
    case PageType::Terminator:
        ui->stackedWidget->setCurrentWidget(ui->terminator);
        ui->terminator_label->setText(m_current.s_text);
    default:
        break;
    }
}

/**
 * @brief MainWindow::incorrect
 * Called when an incorrect answer is submitted
 */
void MainWindow::incorrect(){
    QMessageBox::critical(this, "Incorrect", "I'm sorry, I'm afraid that's the wrong answer.");
    m_pageList.loadSaveData(m_pageList.getSaveData());
    update();
}

void MainWindow::on_text_lineEdit_returnPressed(){
    on_text_nextButton_clicked();
}
