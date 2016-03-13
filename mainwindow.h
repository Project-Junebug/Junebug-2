#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "pagelist.h"

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

    void on_text_lineEdit_returnPressed();

private:
    /**
     * @brief mp_ui
     * Holds the ui QObjects
     */
    Ui::MainWindow *ui;

    /**
     * @brief m_pageList
     */
    PageList m_pageList;

    /**
     * @brief m_current
     * Holds the current display data
     */
    Page m_current;

    void update();
    void incorrect();
};

#endif // MAINWINDOW_H
