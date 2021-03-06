#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "QuestionList.h"

#define NULL_SAVE_FILE "\u0013"

namespace Ui {
class MainWindow;
}
/**
 * @brief The MainWindow class
 * What do you think this does?
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_info_nextButton_clicked();
    void on_text_nextButton_clicked();
    void on_check_nextButton_clicked();

    void on_text_lineEdit_returnPressed();

    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionLoad_triggered();
    void on_actionNew_triggered();

    void closeEvent(QCloseEvent *event);

private:
    /**
     * @brief ui
     * Holds the ui QObjects
     */
    Ui::MainWindow *ui;

    /**
     * @brief m_pageList
     */
    QuestionList m_questionList;

    /**
     * @brief m_saveLocation
     * Holds the location of the last save
     */
    QString m_saveLocation=NULL_SAVE_FILE;

    void update();
    void incorrect();
    bool warn();
};

#endif // MAINWINDOW_H
