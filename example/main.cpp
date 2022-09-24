#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "AOSconcrete.h"
#include "HSMconcrete.h"

extern "C" void app_main(void) {
    // Declare active state objects
    AOSconcrete entity;

    // Start active state objects
    entity.initState(std::make_shared<HSMconcreteA>());
    entity.start("entity", 10, 10, 4096, events);

    while (true) {
        // Simulate posting events from event bus
        for (uint8_t j = 0; j < 3; j++) {
            entity.post((rand() % 3), NULL, 0);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}