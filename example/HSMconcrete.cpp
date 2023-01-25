#include "esp_log.h"

#include "AOSidf.h"
#include "HSMconcrete.h"

static const char* TAG = "hsm";

void HSMconcreteA::entry() {
    ESP_LOGI(TAG, "entry concrete state A");
}

void HSMconcreteA::exit() {
    ESP_LOGI(TAG, "exit concrete state A");
}

void HSMconcreteB::entry() {
    ESP_LOGI(TAG, "entry concrete state B");
}

void HSMconcreteB::exit() {
    ESP_LOGI(TAG, "exit concrete state B");
}

void HSMconcreteC::entry() {
    ESP_LOGI(TAG, "entry concrete state C");
}

void HSMconcreteC::exit() {
    ESP_LOGI(TAG, "exit concrete state C");
}

void HSMconcreteA::signalIn(uint32_t sig) {
    switch (sig) {
        case 0:
            context_->transitionTo(std::make_shared<HSMconcreteB>());
            break;
        case 1:
            context_->transitionTo(std::make_shared<HSMconcreteC>());
            break;
        case 2:
            context_->transitionTo(std::make_shared<HSMconcreteA>());
            break;
        default:
            ESP_LOGW(TAG, "Ignore transition");
            break;
    }
}

void HSMconcreteB::signalIn(uint32_t sig) {
    switch (sig) {
        case 0:
            context_->transitionTo(std::make_shared<HSMconcreteC>());
            break;
        case 1:
            context_->transitionTo(std::make_shared<HSMconcreteA>());
            break;
        case 2:
            context_->transitionTo(std::make_shared<HSMconcreteB>());
            break;
        default:
            ESP_LOGW(TAG, "Ignore transition");
            break;
    }
}

void HSMconcreteC::signalIn(uint32_t sig) {
    switch (sig) {
        case 0:
            context_->transitionTo(std::make_shared<HSMconcreteA>());
            break;
        case 1:
            context_->transitionTo(std::make_shared<HSMconcreteB>());
            break;
        case 2:
            context_->transitionTo(std::make_shared<HSMconcreteC>());
            break;
        default:
            ESP_LOGW(TAG, "Ignore transition");
            break;
    }
}