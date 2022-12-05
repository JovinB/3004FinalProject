#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    control = new Control();

    ui->setupUi(this);

    connect(ui->powerButton, SIGNAL(released()), this, SLOT(powerButtonPressed()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT(upButtonPressed()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(downButtonPressed()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(selectButtonPressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::powerButtonPressed() {
    if(!control->isPowerOn()) {
        control->turnOn();
        control->startSelectingSession();
        ui->powerLabel->setStyleSheet("background-color: green;");
        ui->twentyMin->setStyleSheet("background-color: red;");
        ui->fortyfiveMin->setStyleSheet("background-color: green;");
        ui->userDes->setStyleSheet("background-color: green;");
        ui->delta->setStyleSheet("background-color: red;");
        ui->theta->setStyleSheet("background-color: green;");
        ui->alpha->setStyleSheet("background-color: green;");
        ui->beta1->setStyleSheet("background-color: green;");
    }
    else if(control->isSelectingSession()) {
        if(ui->twentyMin->styleSheet() == "background-color: red;") {
            ui->twentyMin->setStyleSheet("background-color: green;");
            ui->fortyfiveMin->setStyleSheet("background-color: red;");
        }
        else if(ui->fortyfiveMin->styleSheet() == "background-color: red;") {
            ui->fortyfiveMin->setStyleSheet("background-color: green;");
            ui->userDes->setStyleSheet("background-color: red;");
        }
        else {
            ui->userDes->setStyleSheet("background-color: green;");
            ui->twentyMin->setStyleSheet("background-color: red;");
        }
    }
}

void MainWindow::upButtonPressed() {
    if(control->isSelectingSession()) {
        if(ui->delta->styleSheet() == "background-color: red;") {
            ui->delta->setStyleSheet("background-color: green;");
            ui->theta->setStyleSheet("background-color: red;");
        }
        else if(ui->theta->styleSheet() == "background-color: red;") {
            ui->theta->setStyleSheet("background-color: green;");
            ui->alpha->setStyleSheet("background-color: red;");
        }
        else if(ui->alpha->styleSheet() == "background-color: red;") {
            ui->alpha->setStyleSheet("background-color: green;");
            ui->beta1->setStyleSheet("background-color: red;");
        }
        else {
            ui->beta1->setStyleSheet("background-color: green;");
            ui->delta->setStyleSheet("background-color: red;");
        }
    }
    else {
        int currentIntensity = control->getIntensity();
        if(currentIntensity == 8) {
            flashIntensityNumber(currentIntensity);
        }
        else {
            flashIntensityNumber(currentIntensity+1);
            control->setIntensity(currentIntensity+1);
        }
    }
}

void MainWindow::downButtonPressed() {
    if(control->isSelectingSession()) {
        if(ui->delta->styleSheet() == "background-color: red;") {
            ui->delta->setStyleSheet("background-color: green;");
            ui->beta1->setStyleSheet("background-color: red;");
        }
        else if(ui->theta->styleSheet() == "background-color: red;") {
            ui->theta->setStyleSheet("background-color: green;");
            ui->delta->setStyleSheet("background-color: red;");
        }
        else if(ui->alpha->styleSheet() == "background-color: red;") {
            ui->alpha->setStyleSheet("background-color: green;");
            ui->theta->setStyleSheet("background-color: red;");
        }
        else {
            ui->beta1->setStyleSheet("background-color: green;");
            ui->alpha->setStyleSheet("background-color: red;");
        }
    }
    else {
        int currentIntensity = control->getIntensity();
        if(currentIntensity == 1) {
            flashIntensityNumber(currentIntensity);
        }
        else {
            flashIntensityNumber(currentIntensity-1);
            control->setIntensity(currentIntensity-1);
        }
    }
}

void MainWindow::selectButtonPressed() {
    if(control->isSelectingSession()) {
        control->stopSelectingSession();
    }
}

void MainWindow::flashIntensityNumber(int number) {
    switch (number) {
    case 1:
        ui->intensity1->setStyleSheet("");
        wait(350);
        ui->intensity1->setStyleSheet("background-color: green;");
        break;
    case 2:
        ui->intensity2->setStyleSheet("");
        wait(350);
        ui->intensity2->setStyleSheet("background-color: green;");
        break;
    case 3:
        ui->intensity3->setStyleSheet("");
        wait(350);
        ui->intensity3->setStyleSheet("background-color: green;");
        break;
    case 4:
        ui->intensity4->setStyleSheet("");
        wait(350);
        ui->intensity4->setStyleSheet("background-color: yellow;");
        break;
    case 5:
        ui->intensity5->setStyleSheet("");
        wait(350);
        ui->intensity5->setStyleSheet("background-color: yellow;");
        break;
    case 6:
        ui->intensity6->setStyleSheet("");
        wait(350);
        ui->intensity6->setStyleSheet("background-color: yellow;");
        break;
    case 7:
        ui->intensity7->setStyleSheet("");
        wait(350);
        ui->intensity7->setStyleSheet("background-color: red;");
        break;
    case 8:
        ui->intensity8->setStyleSheet("");
        wait(350);
        ui->intensity8->setStyleSheet("background-color: red;");
        break;
    }
}

// used to stop the code at certain points to more accurately simulate real world events
void MainWindow::wait(int milliseconds) {
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(milliseconds);
    loop.exec();
}
