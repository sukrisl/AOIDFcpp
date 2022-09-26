#include "esp_log.h"

#include "AOSconcrete.h"

static const char* TAG = "AOSconcrete";

void AOSconcrete::_init() {
    ESP_LOGI(TAG, "Initializing AOSconcrete");
}

void AOSconcrete::dispatch(uint32_t eventFlag, void* eventData) {
    ESP_LOGI(TAG, "%s/event_flag: 0x%02x", _eventBase, eventFlag);
    _state->processEvent(eventFlag);
}