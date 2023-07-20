#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"

#include "AOconcrete.h"

static const char* TAG = "AOconcrete";

uint8_t AOconcrete::init() {
    ESP_LOGI(TAG, "Starting AOconcrete active object");

    eventBus.attach(this);

    return true;
}

uint8_t AOconcrete::deinit() {
    eventBus.detach(this);

    return true;
}

void AOconcrete::dispatch(uint32_t sig, void* data) {
    switch (sig) {
        case 0:
            ESP_LOGI(TAG, "Event 0 received");
            break;
        case 1:
            ESP_LOGI(TAG, "Event 1 received");
            break;
        default: break;
    }
}