#pragma once

#include <memory>

#include "AOidf.h"
#include "HSMidf.h"

#define TRANSITION(stateMachine) _context->transitionTo(std::make_shared<stateMachine>())

class AOSidf : public AOidf {
 protected:
    std::shared_ptr<HSMidf_state> _state;

    virtual void _init();
    virtual void _deinit();
    virtual void dispatch(uint32_t eventFlag, void* eventData) override;

 public:
    void start(
      const char* aoname,
      int32_t queueLen,
      uint8_t priority,
      uint32_t stackSize,
      std::shared_ptr<HSMidf_state> initState
    );

    void stop();

    void transitionTo(std::shared_ptr<HSMidf_state> state);
};