#include <string.h>
#include <stdint.h>

#include "esp_event_base.h"
#include "esp_log.h"

#include "AOidf.h"

static const char* TAG = "AOidf";

bool AOidf::checkEventExist(const uint32_t flag) {
    for (uint32_t i = 0; i < _eventList.size(); i++) {
        if (_eventList[i] == flag) return true;
    }

    return false;
}

void AOidf::_init() {
    // Default action do nothing
}

void AOidf::_deinit() {
    // Default action do nothing
}

void AOidf::eventLoop(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {
    AOidf* self = static_cast<AOidf*>(handler_args);

    self->dispatch(id, event_data);
}

void AOidf::start(const char* aoname, int32_t queueLen, uint8_t priority, uint32_t stackSize) {
    esp_event_loop_args_t evt_loop_args = {
        .queue_size = queueLen,
        .task_name = aoname,
        .task_priority = priority,
        .task_stack_size = stackSize,
        .task_core_id = tskNO_AFFINITY,
    };

    this->_eventBase = aoname;

    esp_event_loop_create(&evt_loop_args, &_eventLoopHandle);

    _init();
}

void AOidf::stop() {
    _deinit();

    for (uint32_t i = 0; i < _eventList.size(); i++) {
        unsubscribe(_eventList[i]);
    }

    esp_event_loop_delete(_eventLoopHandle);
}

void AOidf::post(uint32_t eventFlag, void* eventData, size_t dataSize) {
    esp_event_post_to(
        this->_eventLoopHandle,
        this->_eventBase,
        eventFlag,
        eventData,
        dataSize,
        portMAX_DELAY
    );
}

bool AOidf::subscribe(uint32_t eventFlag) {
    bool isEventDuplicate = checkEventExist(eventFlag);

    if (isEventDuplicate) {
        ESP_LOGW(TAG, "(%s) Event 0x%04x has already subscribed", _eventBase, eventFlag);
        return false;
    }

    esp_err_t res = esp_event_handler_instance_register_with(
        this->_eventLoopHandle,
        this->_eventBase,
        eventFlag,
        this->eventLoop,
        (void*) this,
        NULL
    );

    if (res == ESP_OK) {
        _eventList.push_back(eventFlag);
        return true;
    }

    return false;
}

bool AOidf::unsubscribe(uint32_t eventFlag) {
    bool isEventExist = checkEventExist(eventFlag);

    if (!isEventExist) {
        ESP_LOGW(TAG, "(%s) Event 0x%04x has already unsubscribed", _eventBase, eventFlag);
        return false;
    }

    ESP_LOGD(TAG, "(%s) Unsubscribe 0x%04x", _eventBase, eventFlag);

    esp_err_t res = esp_event_handler_unregister_with(
        this->_eventLoopHandle,
        this->_eventBase,
        eventFlag,
        this->eventLoop
    );

    return (res == ESP_OK);    
}

void AOidf::getName(char* dest) {
    strcpy(dest, _eventBase);
}