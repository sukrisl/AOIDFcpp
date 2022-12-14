#include <iterator>

#include "AOeventBus.h"

void AOeventBus::dispatch(uint32_t sig, void* data) {
    std::list<std::shared_ptr<AOidf>>::iterator i;
    for (i = subscriberList_.begin(); i != subscriberList_.end() && (*i); ++i) {
        (*i)->post(sig);
    }
}

void AOeventBus::attach(std::shared_ptr<AOidf> subscriber) {
    std::vector<uint32_t> eventList = subscriber->getSignalList();

    for (uint32_t i = 0; i < eventList.size(); i++) {
        subscribe(eventList[i]);
    }

    subscriberList_.push_back(subscriber);
}

void AOeventBus::detach(std::shared_ptr<AOidf> subscriber) {
    std::vector<uint32_t> eventList = subscriber->getSignalList();

    for (uint32_t i = 0; i < eventList.size(); i++) {
        unsubscribe(eventList[i]);
    }

    subscriberList_.erase(std::remove(subscriberList_.begin(), subscriberList_.end(), subscriber), subscriberList_.end());
}