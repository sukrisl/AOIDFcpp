#pragma once

#include <cstring>
#include <cstdint>

#include "esp_event.h"

class Active_ao;
class State_ao {
 public:
    Active_ao* context;
    virtual ~State_ao() { context = NULL; }

    virtual void entry() = 0;
    virtual void exit() = 0;
    virtual void signalIn(uint32_t signal, void* data) = 0;
};

typedef enum {
   ACTIVE_OBJECT_UNINITIALIZED = 0,
   ACTIVE_OBJECT_RUNNING,
   ACTIVE_OBJECT_ERROR,
} ActiveStatus_ao;

class Active_ao {
 protected:
    const char* name_;
    State_ao* state_ = NULL;
    ActiveStatus_ao status_ = ACTIVE_OBJECT_UNINITIALIZED;

    virtual uint8_t initialization() { return true; }
    virtual uint8_t deinitialization() { return true; }

    virtual void dispatch(uint32_t sig, void* data) = 0;

 private:
    esp_event_loop_handle_t loopHandle_;

    static void eventLoop(void* handler_args, esp_event_base_t base, int32_t id, void* event_data);

 public:
    uint8_t start(
      const char* name, State_ao* entryState = NULL, int32_t queueLen = 10,
      uint8_t priority = 0, uint32_t stackSize = 2048);
    uint8_t stop();

    uint8_t startWithExternalEventLoop(const char* name, const esp_event_loop_handle_t loop, State_ao* entryState = NULL);

    bool post(
      uint32_t sig, uint32_t waitTime_ms = 1000,
      void* data = NULL, size_t dataSize = 0);
    void transitionTo(State_ao* state);

    void getName(char* dest) { (void) strcpy(dest, name_); }
    ActiveStatus_ao getStatus() { return status_; }
    State_ao* getCurrentState() { return state_; }
};