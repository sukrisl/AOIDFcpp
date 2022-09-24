#include "esp_log.h"

#include "AOSidf.h"
#include "HSMconcrete.h"

static const char* TAG = "hsm";

void HSMconcreteA::entryAct() {
    ESP_LOGI(TAG, "entry concrete state A");
}

void HSMconcreteA::exitAct() {
    ESP_LOGI(TAG, "exit concrete state A");
}

void HSMconcreteB::entryAct() {
    ESP_LOGI(TAG, "entry concrete state B");
}

void HSMconcreteB::exitAct() {
    ESP_LOGI(TAG, "exit concrete state B");
}

void HSMconcreteC::entryAct() {
    ESP_LOGI(TAG, "entry concrete state C");
}

void HSMconcreteC::exitAct() {
    ESP_LOGI(TAG, "exit concrete state C");
}

transitionCode_t HSMconcreteA::processEvent(uint32_t eventFlag) {
    switch (eventFlag) {
        case 0:
            _context->transitionTo(std::make_shared<HSMconcreteB>());
            return TRANSITION_OK;
        case 1:
            _context->transitionTo(std::make_shared<HSMconcreteC>());
            return TRANSITION_OK;
        case 2:
            _context->transitionTo(std::make_shared<HSMconcreteA>());
            return TRANSITION_OK;
        default:
            ESP_LOGW(TAG, "Ignore transition");
            return TRANSITION_IGNORE;
    }
}

transitionCode_t HSMconcreteB::processEvent(uint32_t eventFlag) {
    switch (eventFlag) {
        case 0:
            _context->transitionTo(std::make_shared<HSMconcreteC>());
            return TRANSITION_OK;
        case 1:
            _context->transitionTo(std::make_shared<HSMconcreteA>());
            return TRANSITION_OK;
        case 2:
            _context->transitionTo(std::make_shared<HSMconcreteB>());
            return TRANSITION_OK;
        default:
            ESP_LOGW(TAG, "Ignore transition");
            return TRANSITION_IGNORE;
    }
}

transitionCode_t HSMconcreteC::processEvent(uint32_t eventFlag) {
    switch (eventFlag) {
        case 0:
            _context->transitionTo(std::make_shared<HSMconcreteA>());
            return TRANSITION_OK;
        case 1:
            _context->transitionTo(std::make_shared<HSMconcreteB>());
            return TRANSITION_OK;
        case 2:
            _context->transitionTo(std::make_shared<HSMconcreteC>());
            return TRANSITION_OK;
        default:
            ESP_LOGW(TAG, "Ignore transition");
            return TRANSITION_IGNORE;
    }
}