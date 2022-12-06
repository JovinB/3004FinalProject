#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    control = new Control();
    Timer = new QTimer(this);
    blinkTimer = new QTimer(this);
    noUser = 0;

    redPalette = this->palette();
    redPalette.setColor(QPalette::Highlight, QColor(Qt::red));
    bluePalette = this->palette();
    bluePalette.setColor(QPalette::Highlight, QColor(Qt::blue));

    ui->setupUi(this);

    ui->progressBar->setPalette(bluePalette);

    connect(Timer, SIGNAL(timeout()), this, SLOT(depleteBattery()));
    Timer->setInterval(1700);
    connect(blinkTimer, SIGNAL(timeout()), this, SLOT(blinkBattery()));
    blinkTimer->setInterval(300);

    connect(ui->powerButton, SIGNAL(released()), this, SLOT(powerButtonPressed()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT(upButtonPressed()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(downButtonPressed()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT(selectButtonPressed()));
    connect(ui->rechargeButton, SIGNAL(released()), this, SLOT(recharge()));
    connect(ui->skinCheckBox, SIGNAL(stateChanged(int)), this, SLOT(skinCheckBoxUpdate()));
    connect(ui->addUserButton, SIGNAL(released()), this, SLOT(addUser()));
    connect(ui->selectUser, SIGNAL(released()), this, SLOT(currentUser()));
    connect(ui->saveRecordButton, SIGNAL(released()), this, SLOT(saveRecord()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::powerButtonPressed() {
    if(ui->progressBar->value() != 0) {
        if(!control->isPowerOn()) {
            control->turnOn();
            control->startSelectingSession();

            ui->upButton->setEnabled(true);
            ui->downButton->setEnabled(true);
            ui->skinCheckBox->setEnabled(true);
            ui->userDropdown->setEnabled(true);
            ui->addUserButton->setEnabled(true);

            if(control->getNumUsers() > 0) { ui->selectUser->setEnabled(true); }



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
        else {
            shutdown();
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
            Timer->setInterval((Timer->interval()) - 200);
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
            Timer->setInterval((Timer->interval()) + 200);
        }
    }
}

void MainWindow::selectButtonPressed() {
    QString sessionName;
    QString groupName;
    control->stopSelectingSession();
    ui->selectButton->setEnabled(false);
    ui->endSessionButton->setEnabled(true);
    ui->saveRecordButton->setEnabled(true);
    ui->selectUser->setEnabled(false);
    sessionTimer.start();

    if(ui->twentyMin->styleSheet() == "background-color: red;") {
        sessionName = "twentyMin";
    }
    else if(ui->fortyfiveMin->styleSheet() == "background-color: red;") {
        sessionName = "fortyfiveMin";
    }
    else {
        sessionName = "userDesigned";
    }

    if(ui->delta->styleSheet() == "background-color: red;") {
        groupName = "delta";
    }
    else if(ui->theta->styleSheet() == "background-color: red;") {
        groupName = "theta";
    }
    else if(ui->alpha->styleSheet() == "background-color: red;") {
        groupName = "alpha";
    }
    else {
        groupName = "beta1";
    }

    control->setCurrentSession(sessionName, groupName);
    Timer->start();
}

void MainWindow::skinCheckBoxUpdate() {
    if(ui->skinCheckBox->isChecked()) {
        Timer->setInterval(Timer->interval() - 200);
    }
    else {
        Timer->setInterval(Timer->interval() + 200);
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

void MainWindow:: recharge(){
    ui->progressBar->setValue(100);
    blinkTimer->stop();
    ui->progressBar->setPalette(bluePalette);
}

void MainWindow:: depleteBattery(){
    ui->progressBar->setValue((ui->progressBar->value())-1);
    if(ui->progressBar->value() == 0) {
        shutdown();
    }
    if(!blinkTimer->isActive() && ui->progressBar->value() < 30) {
        blinkTimer->start();
    }
}

void MainWindow::blinkBattery() {
    if(ui->progressBar->palette() == bluePalette) {
        ui->progressBar->setPalette(redPalette);
    }
    else {
        ui->progressBar->setPalette(bluePalette);
    }
}

void MainWindow::addUser() {
    QString s = QString::number(control->getNumUsers()+1);
    QString userName = "User " + s;
    ui->userDropdown->addItem(userName);
    control->addUser(userName);
    ui->selectUser->setEnabled(true);
}

void MainWindow::currentUser() {
    control->setCurrentUser(ui->userDropdown->currentText());
    ui->currentUserText->setText(ui->userDropdown->currentText());
    ui->userDropdown->setEnabled(false);
    ui->addUserButton->setEnabled(false);
    ui->selectButton->setEnabled(true);
}

void MainWindow::saveRecord() {
    control->saveRecord(sessionTimer.elapsed());
}

void MainWindow::shutdown() {
    control->reset();

    ui->upButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->selectButton->setEnabled(false);
    ui->skinCheckBox->setChecked(false);
    ui->skinCheckBox->setEnabled(false);
    ui->selectUser->setEnabled(false);
    ui->saveRecordButton->setEnabled(false);
    ui->userDropdown->setEnabled(false);
    ui->addUserButton->setEnabled(false);
    ui->endSessionButton->setEnabled(false);

    ui->powerLabel->setStyleSheet("");
    ui->twentyMin->setStyleSheet("");
    ui->fortyfiveMin->setStyleSheet("");
    ui->userDes->setStyleSheet("");
    ui->delta->setStyleSheet("");
    ui->theta->setStyleSheet("");
    ui->alpha->setStyleSheet("");
    ui->beta1->setStyleSheet("");

    Timer->stop();
    Timer->setInterval(1700);
    blinkTimer->stop();
}
