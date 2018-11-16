#include <Task.h>
extern TaskManager taskManager;

class Button : public Task
{
  public:
    typedef void (*action)(int);
    Button(int pin, action function) : Task(MsToTaskTime(500))
    {
        _pin = pin;
        _callback = function;
        state = 3;
        pinMode(_pin, INPUT);
    }

  private:
    int _pin, state;
    action _callback;
    virtual bool OnStart() { return true; }
    virtual void OnUpdate(uint32_t delta_time)
    {
        // mpuCom.println("LED PIN: " + String(_pin) + " " + String(state));
        int input = digitalRead(_pin);
        if (input != state)
        {
            state = input;
            _callback(state);
        }
    }
};