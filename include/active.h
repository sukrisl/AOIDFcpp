#pragma once

#include <cstring>

#include "esp_event.h"

typedef enum {
   ACTIVE_OBJECT_UNINITIALIZED = 0,
   ACTIVE_OBJECT_RUNNING,
   ACTIVE_OBJECT_ERROR,
} ActiveStatus_ao;

class Active_ao {
 protected:
    const char* name_;
    ActiveStatus_ao status_ = ACTIVE_OBJECT_UNINITIALIZED;

    virtual uint8_t init() { return true; };
    virtual uint8_t deinit() { return true;};

    virtual void dispatch(uint32_t sig, void* data) = 0;

 private:
    esp_event_loop_handle_t loopHandle_;

    static void eventLoop(void* handler_args, esp_event_base_t base, int32_t id, void* event_data);

 public:
    uint8_t start(const char* name, int32_t queueLen, uint8_t priority, uint32_t stackSize);
    uint8_t stop();
    void post(uint32_t sig, void* data = NULL, size_t dataSize = 0);

    void getName(char* dest) { (void) strcpy(dest, name_); }
    ActiveStatus_ao getStatus() { return status_; }
};