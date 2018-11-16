
class TankHandler
{
  public:
    static TankHandler *s_instance;
    static int fullStatus, emptyStatus;
    TankHandler()
    {
        fullSignal = new Button(A6, onFullSignal);
        emptySignal = new Button(A7, onEmptySignal);
        taskManager.StartTask(fullSignal);
        taskManager.StartTask(emptySignal);
    };
    static TankHandler *instance()
    {
        if (!s_instance)
            s_instance = new TankHandler;
        return s_instance;
    }

  private:
    Button *fullSignal, *emptySignal;
    static void onFullSignal(int state)
    {
        fullStatus = state;
        mpuCom.println("[Info] FullSignal: " + String(state));
    }
    static void onEmptySignal(int state)
    {
        emptyStatus = state;
        mpuCom.println("[Info] EmptySignal: " + String(state));
    }
    
};
TankHandler *TankHandler::s_instance = 0;
int TankHandler::fullStatus = 0;
int TankHandler::emptyStatus = 0;