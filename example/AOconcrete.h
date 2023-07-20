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