
class PumpHandler
{
  public:
    static PumpHandler *s_instance;
    static int pumpStatus, overloadStatus;
    PumpHandler()
    {
        pumpButton = new Button(A3, onPumpChanged);
        pumpOverload = new Button(A5, onOverloadChanged);
        taskManager.StartTask(pumpButton);
        taskManager.StartTask(pumpOverload);
    };
    static PumpHandler *instance()
    {
        if (!s_instance)
            s_instance = new PumpHandler;
        return s_instance;
    }
    
  private:
    Button *pumpButton, *pumpOverload;
    static void onPumpChanged(int state)
    {
        pumpStatus = state;
        mpuCom.println("[Info] Pump Button: " + String(state));
    }
    static void onOverloadChanged(int state)
    {
        overloadStatus = state;
        mpuCom.println("[Info] Overload signal: " + String(state));
    }
    
};
PumpHandler *PumpHandler::s_instance = 0;
int PumpHandler::pumpStatus = 0;
int PumpHandler::overloadStatus = 0;