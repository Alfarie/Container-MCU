
class FillWaterHandler
{
  public:
    static FillWaterHandler *s_instance;
    static int valveStatus;
    FillWaterHandler()
    {
        button = new Button(A4, onButtonChanged);
        taskManager.StartTask(button);
    };
    static FillWaterHandler *instance()
    {
        if (!s_instance)
            s_instance = new FillWaterHandler;
        return s_instance;
    }

  private:
    Button *button;
    static void onButtonChanged(int state)
    {
        valveStatus = state;
        mpuCom.println("[Info] Fill Button: " + String(state));
    }
    
    
};
FillWaterHandler *FillWaterHandler::s_instance = 0;
int FillWaterHandler::valveStatus = 0;