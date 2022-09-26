#pragma once

#include "AOidf.h"
#include "HSMidf.h"

class AOSidf : public AOidf {
 protected:
    std::shared_ptr<HSMidf_state> _state;

    virtual void _init();
    virtual void dispatch(uint32_t eventFlag, void* eventData) = 0;

 public:
    void start(
      const char* aoname,
      int32_t queueLen,
      uint8_t priority,
      uint32_t stackSize,
      std::shared_ptr<HSMidf_state> initState
    );

    void transitionTo(std::shared_ptr<HSMidf_state> state);
};