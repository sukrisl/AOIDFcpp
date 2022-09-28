#include "esp_log.h"

#include "AOeventBus.h"

#define EVENT_ASSERT(event, flag) { do { if (!event) { ESP_LOGE(TAG, "Event 0x%04x has not created, call AOeventBus::createEvent() first.", flag); abort(); } } while(0); }

static const char* TAG = "ao_evt_bus";

void AOevent::notify() {
    ESP_LOGD(TAG, "Event received (0x%04x)", this->_flag);

    for (uint32_t i = 0; i < _subscribers.size(); i++) {
        char subsName[20];
        _subscribers[i]->getName(subsName);
        ESP_LOGI(TAG, "Posting (0x%04x) to [%d]%s", this->_flag, i, subsName);
        _subscribers[i]->post(this->_flag, NULL, 0);
    }
}

void AOeventBus::_init() {

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

void AOeventBus::attach(uint32_t flag, std::vector<std::shared_ptr<AOidf>> subscribers) {
    for (uint32_t i = 0; i < subscribers.size(); i++) {
        attach(flag, subscribers[i]);
    }
}