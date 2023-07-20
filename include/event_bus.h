#pragma once

#include <algorithm>
#include <list>

#include "active.h"

class EventBus_ao : public Active_ao {
 protected:
    void dispatch(uint32_t sig, void* data) override;

 private:
    size_t bufferSize_;
    std::list<Active_ao*> subscriberList_;

 public:
    EventBus_ao(size_t bufferSize) : bufferSize_(bufferSize) {}
    void attach(Active_ao* subscriber);
    void detach(Active_ao* subscriber);
};