#pragma once

#include "AOSidf.h"

class AOSconcrete : public AOSidf {
 protected:
    void dispatch(uint32_t eventFlag, void* eventData) override;
};