#include <stdint.h>
#include "esp_event_base.h"

#include "AOidf.h"

void AOidf::eventLoop(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {
    AOidf* self = static_cast<AOidf*>(handler_args);

    self->dispatch(id, event_data);
}

void AOidf::start(const char* aoname, int32_t queueLen, uint8_t priority, uint32_t stackSize, std::vector<uint32_t>eventSubscriptionList) {
    esp_event_loop_args_t evt_loop_args = {
        .queue_size = queueLen,
        .task_name = aoname,
        .task_priority = priority,
        .task_stack_size = stackSize,
        .task_core_id = tskNO_AFFINITY,
    };

    this->_eventBase = aoname;

    esp_event_loop_create(&evt_loop_args, &_eventLoopHandle);

    subscribe(eventSubscriptionList);
}

void AOidf::stop() {

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
    esp_err_t res = esp_event_handler_instance_register_with(
        this->_eventLoopHandle,
        this->_eventBase,
        eventFlag,
        this->eventLoop,
        (void*) this,
        NULL
    );

    if (res == ESP_OK) {
        _eventSubscriptionList.push_back(eventFlag);
        _eventSubscriptionCount++;
        return true;
    }

    return false;
}

void AOidf::subscribe(std::vector<uint32_t>eventSubscriptionList) {
    for (uint32_t i = 0; i < eventSubscriptionList.size(); i++) {
        subscribe(eventSubscriptionList[i]);
    }
}