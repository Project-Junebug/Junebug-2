#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

#include "QuestionList.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent - Parent QWidget
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    QMessageBox(QMessageBox::Warning, "Warning!",
                "If you are using Windows 10, restart your PC after running for the first time. Don't ask me why.",
                QMessageBox::Close).exec();

    //Allowing links to be openable
    for(QLabel* i: {ui->text_label, ui->terminator_label, ui->check_label, ui->info_label}){
        i->setTextInteractionFlags(Qt::TextBrowserInteraction);
        i->setOpenExternalLinks(true);
    }

    update();
}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_info_nextButton_clicked(){
    if(m_questionList.testAnswer("")){
        m_questionList.advance();
    }
    update();
}

void MainWindow::on_text_nextButton_clicked(){
    if(m_questionList.testAnswer(ui->text_lineEdit->text().toStdString())){
        m_questionList.advance();
        update();
    } else {
        incorrect();
    }
    ui->text_lineEdit->clear();
}

void MainWindow::on_check_nextButton_clicked(){
    std::string answer="";
    for(auto i: {ui->check_1, ui->check_2, ui->check_3, ui->check_4}){
        answer+=(i->checkState()==Qt::Checked)?"1":"0";
    }
    if(m_questionList.testAnswer(answer)){
        m_questionList.advance();
        update();
    } else {
        incorrect();
    }
    for(auto i: {ui->check_1, ui->check_2, ui->check_3, ui->check_4}){
        i->setChecked(false);
    }
}

/**
 * @brief MainWindow::update
 * Updates the window to show m_pageList.getDisplayData();
 */
void MainWindow::update(){

    QCheckBox* checkArray[4]={ui->check_1, ui->check_2, ui->check_3, ui->check_4};
    const std::string* labels=m_questionList.getLabels();

    switch (m_questionList.getType()) {
    case QuestionType::INFO:
        ui->stackedWidget->setCurrentWidget(ui->info);
        ui->info_label->setText(m_questionList.getText().c_str());
        break;
    case QuestionType::BASE:
        ui->stackedWidget->setCurrentWidget(ui->text);
        ui->text_label->setText(m_questionList.getText().c_str());
        //ui->text_lineEdit->setPlaceholderText(m_current.s_prompt);
        break;
    case QuestionType::CHECKBOX:
        ui->stackedWidget->setCurrentWidget(ui->check);
        for(unsigned int i=0; i<4; i++){
            checkArray[i]->setText(labels[i].c_str());
        }
        ui->check_label->setText(m_questionList.getText().c_str());
        break;
    case QuestionType::TERMINATOR:
        ui->stackedWidget->setCurrentWidget(ui->terminator);
        ui->terminator_label->setText(m_questionList.getText().c_str());
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
    m_questionList.loadSaveData(m_questionList.getSaveData());//I'm so sorry
    update();
}

void MainWindow::on_text_lineEdit_returnPressed(){
    on_text_nextButton_clicked();
}

void MainWindow::on_actionSave_triggered(){
    if(m_saveLocation==NULL_SAVE_FILE) on_actionSave_As_triggered();
    else m_questionList.saveTo(m_saveLocation.toStdString());
}

void MainWindow::on_actionSave_As_triggered(){
    m_questionList.saveTo(QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                        tr("Save Files (*.sav)")).toStdString());
}

void MainWindow::on_actionLoad_triggered(){
    if(!warn()) return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Save Files (*.sav)"));
    m_questionList.loadFrom(fileName.toStdString());
    update();
}

bool MainWindow::warn(){
    return QMessageBox::Yes
            == QMessageBox(QMessageBox::Warning,
                           "Warning!",
                           "This will erase your current save.\n"
                           "Are you really sure you want to do this?",
                           QMessageBox::Yes|QMessageBox::No
                           ).exec();
}

void MainWindow::on_actionNew_triggered(){
    if(!warn()) return;
    m_questionList=QuestionList();
    update();
}
