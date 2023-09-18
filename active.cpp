#include <cstdint>

#include "esp_event_base.h"
#include "esp_log.h"

#include "active.h"

#define EVENT_POST_TIMEOUT_MS 200

void Active_ao::eventLoop(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {
    Active_ao* self = static_cast<Active_ao*>(handler_args);

    // Dispatch event signal and and event data to the dispatch function
    // for custom handling 
    self->dispatch(id, event_data); /* ! NO BLOCKING ! */

    // Dispatch event signal and and event data to the state handler
    if (self->state_ != NULL) {
        self->state_->signalIn(id, event_data); /* ! NO BLOCKING ! */
    }
}

uint8_t Active_ao::start(const char* name, State_ao* entryState, int32_t queueLen, uint8_t priority, uint32_t stackSize) {
    name_ = name;

    esp_event_loop_args_t evt_loop_args = {
        .queue_size = queueLen,
        .task_name = name,
        .task_priority = priority,
        .task_stack_size = stackSize,
        .task_core_id = tskNO_AFFINITY,
    };

    ESP_ERROR_CHECK(esp_event_loop_create(&evt_loop_args, &loopHandle_));
    ESP_ERROR_CHECK(esp_event_handler_instance_register_with(
        loopHandle_, name_, ESP_EVENT_ANY_ID, eventLoop, (void*) this, NULL
    ));
    
    if (!initialization()) {
        status_ = ActiveStatus_ao::ACTIVE_OBJECT_ERROR;
        ESP_LOGE(name_, "Failed to start active object due to user initialization failure");
        return false;
    }

    if (entryState != NULL) transitionTo(entryState);

    status_ = ActiveStatus_ao::ACTIVE_OBJECT_RUNNING;
    return true;
}

uint8_t Active_ao::stop() {
    if (!deinitialization()) {
        status_ = ActiveStatus_ao::ACTIVE_OBJECT_ERROR;
        ESP_LOGE(name_, "Failed to stop active object due to user deinitialization failure");
        return false;
    }

    ESP_ERROR_CHECK(esp_event_loop_delete(loopHandle_));
    status_ = ActiveStatus_ao::ACTIVE_OBJECT_UNINITIALIZED;
    return true;
}

bool Active_ao::post(uint32_t sig, uint32_t waitTime_ms, void* data, size_t dataSize) {
    esp_err_t err = esp_event_post_to(
        loopHandle_, name_, sig, data, dataSize,
        pdMS_TO_TICKS(waitTime_ms));

    if (err != ESP_OK) {
        ESP_LOGE(name_, "Failed to post event, err: %s", esp_err_to_name(err));
        // ESP_ERROR_CHECK(err);
        return false;
    }
    return true;
}

void Active_ao::transitionTo(State_ao* state) {
    if (state_ != NULL) {
        state_->exit();
        delete state_;
    }

    state->context = this;
    state->entry();
    state_ = state;
}