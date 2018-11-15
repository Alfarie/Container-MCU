#include <Task.h>
extern TaskManager taskManager;
#define FLOATING A6

class Floating : public Task
{
  public:
    static Floating *s_instance;
    Floating() : Task(MsToTaskTime(100)){
        pinMode(FLOATING, INPUT);
    };
    static Floating *instance()
    {
      if (!s_instance)
      s_instance = new Floating;
      return s_instance;
    }
    int GetFloating(){
        return val;
    }

  private:
    int val;
    virtual bool OnStart()
    {
        val = 0;
        return true;
    }
    virtual void OnUpdate(uint32_t delta_time)
    {
        val = digitalRead(FLOATING);
        // val = !val;
    }
};
Floating *Floating::s_instance = 0;