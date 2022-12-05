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
    void flashIntensityNumber(int);
    void wait(int);

private slots:
    void powerButtonPressed();
    void upButtonPressed();
    void downButtonPressed();
    void selectButtonPressed();
};
#endif // MAINWINDOW_H
