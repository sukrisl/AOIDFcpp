#include <iterator>

#include "esp_log.h"

#include "AOeventBus.h"

static const char* TAG = "ao_evt_bus";

void AOeventBus::_init() {
    // Default: do nothing
}

void AOeventBus::_deinit() {
    // Default: do nothing
}

void AOeventBus::dispatch(uint32_t eventFlag, void* eventData) {
    std::list<std::shared_ptr<AOidf>>::iterator i;
    for (i = _subscribers.begin(); i != _subscribers.end() && (*i); ++i) {
        char subsName[20];
        (*i)->getName(subsName);
        ESP_LOGD(TAG, "Posting (0x%04x) to %s", eventFlag, subsName);
        (*i)->post(eventFlag);
    }
}

void AOeventBus::attach(std::shared_ptr<AOidf> subscriber) {
    for (uint32_t i = 0; i < subscriber->_eventList.size(); i++) {
        subscribe(subscriber->_eventList[i]);
    }

    _subscribers.push_back(subscriber);
}

void AOeventBus::detach(std::shared_ptr<AOidf> subscriber) {
    for (uint32_t i = 0; i < subscriber->_eventList.size(); i++) {
        unsubscribe(subscriber->_eventList[i]);
    }

    _subscribers.erase(std::remove(_subscribers.begin(), _subscribers.end(), subscriber), _subscribers.end());
}