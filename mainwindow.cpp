#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>

#include <vector>

/**
 * @brief MainWindow::MainWindow
 * @param parent - Parent QWidget
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

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
    m_pageList.checkAnswer();
    update();
}

void MainWindow::on_text_nextButton_clicked(){
    if(m_pageList.checkAnswer(ui->text_lineEdit->text())){
        update();
    } else {
        incorrect();
    }
    ui->text_lineEdit->clear();
}

void MainWindow::on_check_nextButton_clicked(){
    if(m_pageList.checkAnswer({
                              ui->check_1->checkState()==Qt::Checked,
                              ui->check_2->checkState()==Qt::Checked,
                              ui->check_3->checkState()==Qt::Checked,
                              ui->check_4->checkState()==Qt::Checked
})){
        update();
    } else {
        incorrect();
    }
    ui->check_1->setChecked(false);
    ui->check_2->setChecked(false);
    ui->check_3->setChecked(false);
    ui->check_4->setChecked(false);
}

/**
 * @brief MainWindow::update
 * Updates the window to show m_pageList.getDisplayData();
 */
void MainWindow::update(){
    m_current=m_pageList.getDisplayData();
    if(m_current.s_isCheckpoint
            && m_saveLocation!=NULL_SAVE_FILE
            && m_autoSaveEnabled)
        on_actionSave_triggered();
    QStringList list = m_current.s_prompt.split(SPLIT);
    switch (m_current.s_type) {
    case PageType::Info:
        ui->stackedWidget->setCurrentWidget(ui->info);
        ui->info_label->setText(m_current.s_text);
        break;
    case PageType::Textbox:
        ui->stackedWidget->setCurrentWidget(ui->text);
        ui->text_label->setText(m_current.s_text);
        ui->text_lineEdit->setPlaceholderText(m_current.s_prompt);
        break;
    case PageType::Checkbox:
        ui->stackedWidget->setCurrentWidget(ui->check);
        ui->check_1->setText(list.at(0));
        ui->check_2->setText(list.at(1));
        ui->check_3->setText(list.at(2));
        ui->check_4->setText(list.at(3));
        ui->check_label->setText(m_current.s_text);
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



void MainWindow::on_actionSave_triggered(){
    if(m_saveLocation==NULL_SAVE_FILE) on_actionSave_As_triggered();
    else saveTo(m_saveLocation);
}

void MainWindow::on_actionSave_As_triggered(){
    saveTo(QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
                                        tr("Save Files (*.sav)")));
}

/**
 * @brief MainWindow::saveTo
 * @param fileName - location to save to
 * Saves the m_pageList.mM_saveData
 */
void MainWindow::saveTo(QString fileName){
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
        } else {
            file.remove();
            file.open(QIODevice::WriteOnly);
            QTextStream stream(&file);
            stream << m_pageList.getSaveData();
            stream.flush();
            file.close();
            m_saveLocation=fileName;
        }
    }
}

void MainWindow::on_actionLoad_triggered(){
    if(!warn()) return;

    m_pageList=PageList();

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
                                                    tr("Save Files (*.sav)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);

        m_pageList.loadSaveData(in.readAll());
        update();

        file.close();
        m_saveLocation=fileName;
    }
}

bool MainWindow::warn(){
    return QMessageBox::Yes
            == QMessageBox(QMessageBox::Information,
                           "Warning!",
                           "This will erase your current save.\n"
                           "Are you really sure you want to do this?",
                           QMessageBox::Yes|QMessageBox::No
                           ).exec();
}

void MainWindow::on_actionNew_triggered(){
    if(!warn()) return;
    m_pageList=PageList();
    update();
}

void MainWindow::on_actionAutosave_enabled_toggled(bool newVal){
    m_autoSaveEnabled=newVal;
}
