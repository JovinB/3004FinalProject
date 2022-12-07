#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>
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
    QElapsedTimer sessionTimer;

    void flashIntensityNumber(int);
    void wait(int);
    void shutdown();
    void highlightSessionGroup(QString);
    void highlightSessionName(QString);
    void displayConnection(bool);


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
    void selectRecord();
    void endSession();
    void excellentConnectionUpdate();
    void okayConnectionUpdate();
    void noneConnectionUpdate();
};
#endif // MAINWINDOW_H
