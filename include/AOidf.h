#pragma once

#include "esp_event.h"

class AOidf {
 protected:
    esp_event_base_t _eventBase;

    virtual void _init();
    virtual void _deinit();
    virtual void dispatch(uint32_t eventFlag, void* eventData) = 0;

 private:
    esp_event_loop_handle_t _eventLoopHandle;
    uint32_t _eventSubscriptionCount = 0;

    static void eventLoop(void* handler_args, esp_event_base_t base, int32_t id, void* event_data);

 public:
    AOidf() {}
    ~AOidf() {}

    virtual void start(
      const char* aoname,
      int32_t queueLen,
      uint8_t priority,
      uint32_t stackSize
    );

    void stop();
    void post(uint32_t eventFlag, void* eventData = NULL, size_t dataSize = 0);

    bool subscribe(uint32_t eventFlag);
    bool unsubscribe(uint32_t eventFlag);

    void getName(char* dest);
};