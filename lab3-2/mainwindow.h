#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_switchOnButton_clicked();

    void led_shining();

    void on_switchOffButton_clicked();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

    int shiningTime;

    int timeLimit;

    QTimer *timer;
};

#endif // MAINWINDOW_H
