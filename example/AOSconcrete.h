#pragma once

#include "AOSidf.h"

class AOSconcrete : public AOSidf {
 protected:
    void _init() override;
    void dispatch(uint32_t eventFlag, void* eventData) override;
};