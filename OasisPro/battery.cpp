#include "battery.h"
#include "ui_mainwindow.h"
#include <unistd.h>


//#include <QDateTime>

//Battery::Battery(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
  //  connect(ui->progressBar, SIGNAL(valueChanged(int)), this, SLOT(setValue(0)));
//}

Battery::Battery(int BatteryLevel)
{

  batteryLevel = BatteryLevel;

}

void Battery::chargeBattery(){
    batteryLevel = 100;
}

void Battery::depleteBattery(){

}

void Battery::myfunction()
{
}

