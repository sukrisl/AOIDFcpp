#pragma once

#include "AOSidf.h"

class AOSconcrete : public AOSidf {
 protected:
    void init() override;
    void dispatch(uint32_t sig, void* data) override;
};