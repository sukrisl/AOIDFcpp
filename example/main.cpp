#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "event_bus.h"
#include "AOconcrete.h"

// Declare event bus object
EventBus_ao eventBus(1024);

// Declare active state object
AOconcrete aoConcrete;

extern "C" void app_main(void) {
    // Start active state objects
    aoConcrete.start("aoConcrete", 10, 10, 4096);

    while (true) {
        eventBus.post(0);
        vTaskDelay(pdMS_TO_TICKS(500));
        eventBus.post(1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}