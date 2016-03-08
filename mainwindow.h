#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    /**
     * @brief mp_ui
     * Holds the ui QObjects
     */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
