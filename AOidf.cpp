#include <cstdint>

#include "esp_event_base.h"
#include "esp_log.h"

#include "AOidf.h"

static const char* TAG = "AOidf";

bool AOidf::checkSignalExist(const uint32_t flag) {
    for (uint32_t i = 0; i < signalList_.size(); i++) {
        if (signalList_[i] == flag) return true;
    }

    return false;
}

void AOidf::eventLoop(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {
    AOidf* self = static_cast<AOidf*>(handler_args);
    self->dispatch(id, event_data);
}

void AOidf::start(const char* name, int32_t queueLen, uint8_t priority, uint32_t stackSize) {
    name_ = name;

    esp_event_loop_args_t evt_loop_args = {
        .queue_size = queueLen,
        .task_name = name,
        .task_priority = priority,
        .task_stack_size = stackSize,
        .task_core_id = tskNO_AFFINITY,
    };

    esp_event_loop_create(&evt_loop_args, &loopHandle_);
    init();
}

void AOidf::stop() {
    deinit();

    for (uint32_t i = 0; i < signalList_.size(); i++) {
        unsubscribe(signalList_[i]);
    }

    esp_event_loop_delete(loopHandle_);
}

void AOidf::post(uint32_t sig, void* data, size_t dataSize) {
    esp_event_post_to(loopHandle_, name_, sig, data, dataSize, portMAX_DELAY);
}

bool AOidf::subscribe(uint32_t sig) {
    bool isSignalAlreadySubscribed = checkSignalExist(sig);

    if (isSignalAlreadySubscribed) {
        ESP_LOGD(TAG, "(%s) Signal 0x%04x has already subscribed", name_, sig);
        return false;
    }

    esp_err_t res = esp_event_handler_instance_register_with(
        loopHandle_, name_, sig, eventLoop, (void*) this, NULL
    );

    if (res == ESP_OK) signalList_.push_back(sig);

    return (res == ESP_OK);
}

bool AOidf::unsubscribe(uint32_t sig) {
    bool isSignalSubscribed = checkSignalExist(sig);

    if (!isSignalSubscribed) {
        ESP_LOGD(TAG, "(%s) Signal 0x%04x has already unsubscribed", name_, sig);
        return false;
    }

    ESP_LOGD(TAG, "(%s) Unsubscribe 0x%04x", name_, sig);
    esp_err_t res = esp_event_handler_unregister_with(loopHandle_, name_, sig, eventLoop);

    return (res == ESP_OK);    
}