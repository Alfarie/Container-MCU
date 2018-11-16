class Emergency
{
  public:
    static Emergency *s_instance;
    static int emerStatus;
    Emergency(){
        emerButton = new Button(A0, emerButtonChanged);
        taskManager.StartTask(emerButton);
        emerStatus = 0;
    };
    static Emergency *instance()
    {
        if (!s_instance)
            s_instance = new Emergency;
        return s_instance;
    }
    private: 
        Button *emerButton;
        static void emerButtonChanged(int state){
            emerStatus = state;
        }
};
Emergency *Emergency::s_instance = 0;
int Emergency::emerStatus = 0;
