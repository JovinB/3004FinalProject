#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "control.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Control *control;
    QTimer *Timer;
    QTimer *blinkTimer;
    QPalette redPalette;
    QPalette bluePalette;
    int noUser;

    void flashIntensityNumber(int);
    void wait(int);
    void shutdown();


private slots:
    void powerButtonPressed();
    void upButtonPressed();
    void downButtonPressed();
    void selectButtonPressed();
    void skinCheckBoxUpdate();
    void recharge();
    void depleteBattery();
    void blinkBattery();
    void addUser();
    void currentUser();
    void saveRecord();
};
#endif // MAINWINDOW_H
