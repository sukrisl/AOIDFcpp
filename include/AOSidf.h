#pragma once

#include "AOidf.h"
#include "HSMidf.h"

class AOSidf : public AOidf {
 protected:
    std::shared_ptr<HSMidf_state> _state;

    virtual void dispatch(uint32_t eventFlag, void* eventData) = 0;

 public:
    void initState(std::shared_ptr<HSMidf_state> state);
    void transitionTo(std::shared_ptr<HSMidf_state> state);
};