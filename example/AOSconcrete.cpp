#include "esp_log.h"

#include "AOSconcrete.h"

static const char* TAG = "AOSconcrete";

void AOSconcrete::init() {
    ESP_LOGI(TAG, "Initializing AOSconcrete");
}

void AOSconcrete::dispatch(uint32_t sig, void* data) {
    ESP_LOGI(TAG, "%s/event_flag: 0x%02x", name_, sig);
    state_->signalIn(sig);
}