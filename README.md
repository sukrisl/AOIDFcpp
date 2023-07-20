# AOIDFcpp Library

AOIDFcpp is an C++ framework library to work with ESP-IDF. The library provide an interface class for implementing active object design pattern and event bus architecture.

There are 2 main classes in the library:
- `Active_ao` Active object interface class
- `EventBus_ao` Event bus class

## Adding component to your ESP-IDF project
To use the library you can manually clone the repo or add component as a submodule. Go to your project directory on the terminal and add repo as a git submodule:
```
git submodule add https://github.com/sukrisl/AOIDFcpp.git components/AOIDFcpp
```

Currently unstable and has very limited functionality, use at your own risk.

## Application Example
##### AOconcrete.h
``` C++
#pragma once

#include "Active.h"
#include "event_bus.h"

extern EventBus_ao eventBus;

class AOconcrete : public Active_ao {
 private:
    uint8_t init() override;
    uint8_t deinit() override;
    void dispatch(uint32_t sig, void* data) override;
};
```
##### AOconcrete.cpp
``` C++
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
```
##### main.cpp
``` C++
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
```