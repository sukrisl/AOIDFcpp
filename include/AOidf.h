#pragma once

#include <cstring>
#include <memory>
#include <vector>

#include "esp_event.h"

class AOidf : public std::enable_shared_from_this<AOidf> {
 protected:
    const char* name_;
    std::vector<uint32_t> signalList_;

    virtual void init() {};
    virtual void deinit() {};

    virtual void dispatch(uint32_t sig, void* data) = 0;

 private:
    esp_event_loop_handle_t loopHandle_;

    bool checkSignalExist(const uint32_t flag);
    static void eventLoop(void* handler_args, esp_event_base_t base, int32_t id, void* event_data);

 public:
    void start(const char* name, int32_t queueLen, uint8_t priority, uint32_t stackSize);
    void stop();
    void post(uint32_t sig, void* data = NULL, size_t dataSize = 0);
    bool subscribe(uint32_t sig);
    bool unsubscribe(uint32_t sig);

    std::vector<uint32_t> getSignalList() { return signalList_; }
    void getName(char* dest) { strcpy(dest, name_); }
};