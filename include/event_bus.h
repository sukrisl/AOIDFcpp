#pragma once

#include <algorithm>
#include <list>

#include "active.h"

typedef struct {
    uint32_t id;
    void* data;
    size_t dataSize;
} Event_t;

typedef struct {
    Event_t event;
    Active_ao* listener;
} EventProcess_t;

class EventBus_ao {
 private:
    std::list<Active_ao*> subscriberList_;

 public:
    void start();
    void attach(Active_ao* subscriber);
    void detach(Active_ao* subscriber);
    void detachAll();

    void post(const Event_t event);
};