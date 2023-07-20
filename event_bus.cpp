#include <iterator>
#include "event_bus.h"

void EventBus_ao::dispatch(uint32_t sig, void* data) {
    std::list<Active_ao*>::iterator i;
    for (i = subscriberList_.begin(); i != subscriberList_.end() && (*i); ++i) {
        if ((*i)->getStatus() == ActiveStatus_ao::ACTIVE_OBJECT_RUNNING) {
            (*i)->post(sig, data, bufferSize_);
        }
    }
}

void EventBus_ao::attach(Active_ao* subscriber) {
    subscriberList_.push_back(subscriber);
}

void EventBus_ao::detach(Active_ao* subscriber) {
    subscriberList_.erase(std::remove(subscriberList_.begin(), subscriberList_.end(), subscriber), subscriberList_.end());
}