#include <Task.h>
TaskManager taskManager;

#include <Wire.h>
#include <EEPROM.h>

#include <SoftwareSerial.h>
#define EEPROM_SIZE 1024
#define CHANNEL_NUMBER 6
#define VERSION 2.0
#define PROJECT "PLANTLAB-GROBOT"
#define UPLOADDATE String(__DATE__) + " " +  String(__TIME__)
#define ledPin 2
#define co2Pin 7
#define ecPin 4
#define phPin 5
#define pumpPin 3
#define valvePin 6
//2led, 3pump, 4ec, 5ph, 6valve, 7co2, 8led
String ShowBoardInfo(){
    String str = "INFOBOARD-VERSION" + String(VERSION) + "\r\n";
    str += "INFOPROJECT-NAME "+ String(PROJECT) + "\r\n";
    str += "INFODATE-" + String(UPLOADDATE) + "\r\n";
    return str;
}

HardwareSerial &debugCom = Serial;
// SoftwareSerial debugCom(21,22);
HardwareSerial &mpuCom    = Serial1;
HardwareSerial &solCom = Serial2;
HardwareSerial &lightCom  = Serial3;
HardwareSerial &airCom = Serial3;


#include "./modules/Helper/DisplayLog.h"

int CH_ON = HIGH;
int CH_OFF = LOW;
String MCU_STATE = "NRDY";

struct timer_s
{
    int st;
    int en; // end or working depend CH_ON timer mode
};

struct sensor_s
{
    float soil;
    float vpd;
    float ec;
    float ph;
    float water;
    float temp;
    float humi;
    float co2;
    float light;
    boolean floating;
};

#include "./modules/Control/Control.h"
Control *channel[CHANNEL_NUMBER];

//
int ChannelGpio[CHANNEL_NUMBER] = {ledPin,co2Pin,ecPin,phPin,pumpPin,valvePin};
int ChannelStatus[CHANNEL_NUMBER] = {LOW,LOW,LOW,LOW,LOW,LOW};

void DigitalWrite(int ch, int status){
    digitalWrite(ChannelGpio[ch], status);
    ChannelStatus[ch] = status;
}


//General module
#include "./modules/Memory/eeprom_manager.h"
// #include "./modules/DateTime.h"
#include "./modules/RTC.h"
#include "./modules/Sensors/Sensor.h"

//water process
#include "./modules/Process/WaterProcess.h"
WaterProcess *wt_process[6];
#include "./modules/Process/WaterProcessControl.h"

#include "./modules/Control/Manual.h"
#include "./modules/Control/Timer.h"
#include "./modules/Control/Setpoint.h"
#include "./modules/Control/SetBound.h"
#include "./modules/Control/Irrigation.h"

#include "./modules/Control/ControlFactory.h"
#include "./modules/ChannelHandler.h"
#include "./modules/Memory/MemoryCheck.h"


// #include "./ButtonModule/ButtonManager.h"
#include "./modules/Communication.h"

#include "./modules/Helper/Puppet.h"

void setup()
{
    // ButtonManager::instance();
    Puppet::instance();
    Wire.begin();

    debugCom.begin(9600);
    mpuCom.begin(115200);
    
    solCom.begin(9600);
    airCom.begin(9600);
    lightCom.begin(9600);
    
    debugCom.println("Initializing...");
    debugCom.println(ShowBoardInfo());
    mpuCom.println(ShowBoardInfo());
    //testCom.println(ShowBoardInfo());

    EEPROM_Manager::InitEEPROM();
    taskManager.StartTask(RTC::instance());
    taskManager.StartTask(WaterProcessControl::instance());
    taskManager.StartTask(Sensor::instance());
    taskManager.StartTask(Communication::instance());
    taskManager.StartTask(MemoryCheck::instance());
    ChannelHanler::instance();
    MCU_STATE = "RDY";
    mpuCom.println(MCU_STATE);
}
void loop()
{
    taskManager.Loop();
}


