#include "./HardButton.h"
#include "./LedHandler.h"
#include "./EmergencyHandler.h"
#include "./PumpHandler.h"
#include "./FillWaterHandler.h"
#include "./TankHandler.h"
class ButtonManager
{
  public:
    static ButtonManager *s_instance;
    ButtonManager()
    {
        LEDHandler::instance();
        Emergency::instance();
        PumpHandler::instance();
        FillWaterHandler::instance();
        TankHandler::instance();
    };
    static ButtonManager *instance()
    {
        if (!s_instance)
            s_instance = new ButtonManager;
        return s_instance;
    }

    String GetStatus(){
        int emer = Emergency::instance()->emerStatus;
        int ledOn  = LEDHandler::instance()->onStatus;
        int ledOff = LEDHandler::instance()->offStatus;
        int pump = PumpHandler::instance()->pumpStatus;
        int valve = FillWaterHandler::instance()->valveStatus;
        int pumpOverload = PumpHandler::instance()->overloadStatus;
        int fullTank = TankHandler::instance()->fullStatus;
        int emptyTank = TankHandler::instance()->emptyStatus;

        return "{st-btn," + String(emer) + "," + String(ledOn) + "," + String(ledOff) + "," + String(pump) + "," + String(valve) + "," + String(pumpOverload) 
            + "," + String(fullTank) + "," + String(emptyTank) + "}";
    }
};
ButtonManager *ButtonManager::s_instance = 0;