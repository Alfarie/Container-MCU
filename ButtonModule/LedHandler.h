class LEDHandler
{
  public:
    static LEDHandler *s_instance;
    static int onStatus, offStatus;
    LEDHandler()
    {
        ledOnButton = new Button(A1, ledOnChanged);
        ledOffButton = new Button(A2, ledOffChanged);
        onStatus = offStatus = 0;
        taskManager.StartTask(ledOnButton);
        taskManager.StartTask(ledOffButton);
    };
    static LEDHandler *instance()
    {
        if (!s_instance)
            s_instance = new LEDHandler;
        return s_instance;
    }

  private:
    Button *ledOnButton, *ledOffButton;

    static void ledOnChanged(int state)
    {
        mpuCom.println("[Info] LEDHandler ON: " + String(state));
        onStatus = state;
    }
    static void ledOffChanged(int state)
    {
        mpuCom.println("[Info] LEDHandler OFF: " + String(state));
        offStatus = state;
    }
};
LEDHandler *LEDHandler::s_instance = 0;
int LEDHandler::onStatus = 0;
int LEDHandler::offStatus = 0;