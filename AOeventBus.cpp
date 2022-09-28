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
    std::shared_ptr<AOevent> eventBuf = this->lookupEvent(eventFlag);
    EVENT_ASSERT(eventBuf, eventFlag);
    eventBuf->notify();
}

std::shared_ptr<AOevent> AOeventBus::lookupEvent(uint32_t flag) {
    std::shared_ptr<AOevent> eventBuf;

    for (uint32_t i = 0; i < _eventList.size(); i++) {
            if (_eventList[i]->_flag == flag) {
                eventBuf = _eventList[i];
                break;
            }
    }

    return eventBuf;
}

void AOeventBus::createEvent(uint32_t flag) {
    std::shared_ptr<AOevent> eventBuf = std::make_shared<AOevent>(flag);
    this->subscribe(flag);
    _eventList.push_back(eventBuf);
}

void AOeventBus::createEvent(uint32_t flag, std::shared_ptr<AOidf> subscriber) {
    this->createEvent(flag);
    this->registerSubscriber(flag, subscriber);
}

void AOeventBus::createEvent(uint32_t flag, std::vector<std::shared_ptr<AOidf>> subscribers) {
    this->createEvent(flag);
    this->registerSubscriber(flag, subscribers);
}

void AOeventBus::registerSubscriber(uint32_t flag, std::shared_ptr<AOidf> subscriber) {
    std::shared_ptr<AOevent> eventBuf = this->lookupEvent(flag);
    EVENT_ASSERT(eventBuf, flag);

    eventBuf->registerSubscriber(subscriber);
    subscriber->subscribe(flag);
}

void AOeventBus::registerSubscriber(uint32_t flag, std::vector<std::shared_ptr<AOidf>> subscribers) {
    for (uint32_t i = 0; i < subscribers.size(); i++) {
        registerSubscriber(flag, subscribers[i]);
    }
}