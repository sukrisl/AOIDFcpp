#include <iterator>

#include "esp_log.h"

#include "AOeventBus.h"

#define EVENT_ASSERT(event, flag) { do { if (!event) { ESP_LOGE(TAG, "Event 0x%04x has not created, call AOeventBus::createEvent() first.", flag); abort(); } } while(0); }

static const char* TAG = "ao_evt_bus";

void AOevent::notify() {
    ESP_LOGW(TAG, "Event received (0x%04x)", this->_flag);

    for (std::list<std::shared_ptr<AOidf>>::iterator i = _subscribers.begin(); i != _subscribers.end(); ++i) {
        char subsName[20];
        (*i)->getName(subsName);
        ESP_LOGI(TAG, "Posting (0x%04x) to %s", this->_flag, subsName);
        (*i)->post(this->_flag, NULL, 0);
    }
}

void AOeventBus::_init() {
    // Default: do nothing
}

void AOeventBus::_deinit() {
    // Default: do nothing
}

void AOeventBus::dispatch(uint32_t eventFlag, void* eventData) {
    EVENT_ASSERT(_eventList[eventFlag], eventFlag);
    _eventList[eventFlag]->notify();
}

void AOeventBus::createEvent(uint32_t flag) {
    std::shared_ptr<AOevent> eventBuf = std::make_shared<AOevent>(flag);
    this->subscribe(flag);
    _eventList.insert(std::make_pair(flag, eventBuf));
}

void AOeventBus::createEvent(uint32_t flag, std::shared_ptr<AOidf> subscriber) {
    this->createEvent(flag);
    this->attach(flag, subscriber);
}

void AOeventBus::attach(uint32_t flag, std::shared_ptr<AOidf> subscriber) {
    EVENT_ASSERT(_eventList[flag], flag);

    _eventList[flag]->attach(subscriber);
    subscriber->subscribe(flag);
}

void AOeventBus::detach(uint32_t flag, std::shared_ptr<AOidf> subscriber) {
    EVENT_ASSERT(_eventList[flag], flag);

    _eventList[flag]->detach(subscriber);
    subscriber->unsubscribe(flag);
}