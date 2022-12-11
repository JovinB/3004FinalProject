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
    connect(ui->addUserButton, SIGNAL(released()), this, SLOT(addUser()));
    connect(ui->selectUser, SIGNAL(released()), this, SLOT(currentUser()));
    connect(ui->saveRecordButton, SIGNAL(released()), this, SLOT(saveRecord()));
    connect(ui->endSessionButton,SIGNAL(released()), this, SLOT(endSession()));
    connect(ui->selectRecord,SIGNAL(released()), this, SLOT(selectRecord()));

    connect(ui->skinCheckBox, SIGNAL(stateChanged(int)), this, SLOT(skinCheckBoxUpdate()));
    connect(ui->excellentCheckBox, SIGNAL(stateChanged(int)), this, SLOT(excellentConnectionUpdate()));
    connect(ui->okayCheckBox, SIGNAL(stateChanged(int)), this, SLOT(okayConnectionUpdate()));
    connect(ui->noneCheckBox, SIGNAL(stateChanged(int)), this, SLOT(noneConnectionUpdate()));
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
            ui->excellentCheckBox->setEnabled(true);
            ui->okayCheckBox->setEnabled(true);
            ui->noneCheckBox->setEnabled(true);
            ui->excellentCheckBox->setChecked(true);

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
    displayConnection(true);

    if(control->getConnectionLevel() != "No Connection") {
        QString sessionName;
        QString groupName;
        control->stopSelectingSession();
        ui->selectButton->setEnabled(false);
        ui->endSessionButton->setEnabled(true);
        ui->saveRecordButton->setEnabled(true);
        ui->selectUser->setEnabled(false);
        ui->selectRecord->setEnabled(false);
        ui->recordDropdown->setEnabled(false);
        ui->excellentCheckBox->setEnabled(false);
        ui->okayCheckBox->setEnabled(false);
        ui->noneCheckBox->setEnabled(false);

        if(ui->twentyMin->styleSheet() == "background-color: red;") {
            groupName = "twentyMin";
        }
        else if(ui->fortyfiveMin->styleSheet() == "background-color: red;") {
            groupName = "fortyfiveMin";
        }
        else {
            groupName = "userDesigned";
        }

        if(ui->delta->styleSheet() == "background-color: red;") {
            sessionName = "delta";
        }
        else if(ui->theta->styleSheet() == "background-color: red;") {
            sessionName = "theta";
        }
        else if(ui->alpha->styleSheet() == "background-color: red;") {
            sessionName = "alpha";
        }
        else {
            sessionName = "beta1";
        }

        sessionTimer.start();
        Timer->start();
        control->setCurrentSession(sessionName, groupName);
    }
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

    User* currUser = control->getUser(control->getCurrentUser());
    if(currUser->getNumRecords() != 0) {
        ui->recordDropdown->setEnabled(true);
        ui->selectRecord->setEnabled(true);
        QVector<Record*> records = currUser->getRecords();
        for(int i = 0; i < currUser->getNumRecords(); i++) {
            ui->recordDropdown->addItem(records[i]->getRecordName());
        }
    }
}

void MainWindow::saveRecord() {
    control->saveRecord(sessionTimer.elapsed());
}

void MainWindow::selectRecord() {
    Record* currRecord = control->fetchRecord(ui->recordDropdown->currentText());
    highlightSessionGroup(currRecord->getSessionGroup());
    highlightSessionName(currRecord->getSessionName());

    if(control->getIntensity() > currRecord->getIntensityLevel()) {
        for(int i = control->getIntensity(); i > currRecord->getIntensityLevel(); i--) {
            Timer->setInterval((Timer->interval()) + 200);
        }
    }
    else {
        for(int i = control->getIntensity(); i < currRecord->getIntensityLevel(); i++) {
            Timer->setInterval((Timer->interval()) - 200);
        }
    }
    control->setIntensity(currRecord->getIntensityLevel());
    flashIntensityNumber(currRecord->getIntensityLevel());
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
    ui->selectRecord->setEnabled(false);
    ui->recordDropdown->setEnabled(false);

    ui->excellentCheckBox->setChecked(false);
    ui->okayCheckBox->setChecked(false);
    ui->noneCheckBox->setChecked(false);
    ui->excellentCheckBox->setEnabled(false);
    ui->okayCheckBox->setEnabled(false);
    ui->noneCheckBox->setEnabled(false);

    ui->currentUserText->setText("");
    ui->recordDropdown->clear();

    ui->powerLabel->setStyleSheet("");
    ui->twentyMin->setStyleSheet("");
    ui->fortyfiveMin->setStyleSheet("");
    ui->userDes->setStyleSheet("");
    ui->delta->setStyleSheet("");
    ui->theta->setStyleSheet("");
    ui->alpha->setStyleSheet("");
    ui->beta1->setStyleSheet("");

    displayConnection(false);

    Timer->stop();
    Timer->setInterval(1700);
    blinkTimer->stop();
}

void MainWindow::endSession(){
    for (int i = 8; i > 0; i--){
         flashIntensityNumber(i);
    }
    shutdown();
}

void MainWindow::highlightSessionGroup(QString groupName) {
    if(groupName == "twentyMin") {
        ui->twentyMin->setStyleSheet("background-color: red;");
        ui->fortyfiveMin->setStyleSheet("background-color: green;");
        ui->userDes->setStyleSheet("background-color: green;");
    }
    else if(groupName == "fortyfiveMin") {
        ui->twentyMin->setStyleSheet("background-color: green;");
        ui->fortyfiveMin->setStyleSheet("background-color: red;");
        ui->userDes->setStyleSheet("background-color: green;");
    }
    else {
        ui->twentyMin->setStyleSheet("background-color: green;");
        ui->fortyfiveMin->setStyleSheet("background-color: green;");
        ui->userDes->setStyleSheet("background-color: red;");
    }
}

void MainWindow::highlightSessionName(QString sessionName) {
    if(sessionName == "delta") {
        ui->delta->setStyleSheet("background-color: red;");
        ui->theta->setStyleSheet("background-color: green;");
        ui->alpha->setStyleSheet("background-color: green;");
        ui->beta1->setStyleSheet("background-color: green;");
    }
    else if(sessionName == "theta") {
        ui->delta->setStyleSheet("background-color: green;");
        ui->theta->setStyleSheet("background-color: red;");
        ui->alpha->setStyleSheet("background-color: green;");
        ui->beta1->setStyleSheet("background-color: green;");
    }
    else if(sessionName == "alpha") {
        ui->delta->setStyleSheet("background-color: green;");
        ui->theta->setStyleSheet("background-color: green;");
        ui->alpha->setStyleSheet("background-color: red;");
        ui->beta1->setStyleSheet("background-color: green;");
    }
    else {
        ui->delta->setStyleSheet("background-color: green;");
        ui->theta->setStyleSheet("background-color: green;");
        ui->alpha->setStyleSheet("background-color: green;");
        ui->beta1->setStyleSheet("background-color: red;");
    }
}

void MainWindow::excellentConnectionUpdate() {
    if(ui->excellentCheckBox->isChecked()) {
        control->setConnectionLevel("Excellent Connection");
        ui->excellentCheckBox->setEnabled(false);
        ui->okayCheckBox->setChecked(false);
        ui->noneCheckBox->setChecked(false);
    }
    else {
        ui->excellentCheckBox->setEnabled(true);
    }
}

void MainWindow::okayConnectionUpdate() {
    if(ui->okayCheckBox->isChecked()) {
        control->setConnectionLevel("Okay Connection");
        ui->okayCheckBox->setEnabled(false);
        ui->excellentCheckBox->setChecked(false);
        ui->noneCheckBox->setChecked(false);
    }
    else {
        ui->okayCheckBox->setEnabled(true);
    }
}

void MainWindow::noneConnectionUpdate() {
    if(ui->noneCheckBox->isChecked()) {
        control->setConnectionLevel("No Connection");
        ui->noneCheckBox->setEnabled(false);
        ui->excellentCheckBox->setChecked(false);
        ui->okayCheckBox->setChecked(false);
    }
    else {
        ui->noneCheckBox->setEnabled(true);
    }
}

void MainWindow::displayConnection(bool flag) {
    if(flag) {
        QString connectionLevel = control->getConnectionLevel();
        ui->connectionLevelTitle->setText("Connection Level:");
        ui->connectionLabel->setText(connectionLevel);
        if(connectionLevel == "Excellent Connection") {
            ui->connectionLabel->setStyleSheet("background-color: green;");
        }
        else if(connectionLevel == "Okay Connection") {
            ui->connectionLabel->setStyleSheet("background-color: yellow;");
        }
        else {
            ui->connectionLabel->setStyleSheet("background-color: red;");
        }
    }
    else {
        ui->connectionLevelTitle->setText("");
        ui->connectionLabel->setText("");
        ui->connectionLabel->setStyleSheet("");
    }
}
