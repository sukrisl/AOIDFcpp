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
    for (uint32_t i = 0; i < _subscribers.size(); i++) {
        char subsName[20];
        _subscribers[i]->getName(subsName);
        ESP_LOGI(TAG, "Posting (0x%04x) to %s", eventFlag, subsName);
        _subscribers[i]->post(eventFlag);
    }
}

void AOeventBus::attach(std::shared_ptr<AOidf> subscriber) {
    _subscribers.push_back(subscriber);
}

void AOeventBus::detach(std::shared_ptr<AOidf> subscriber) {
    _subscribers.erase(std::remove(_subscribers.begin(), _subscribers.end(), subscriber), _subscribers.end());
}