#pragma once

#include "AOidf.h"
#include "HSMidf.h"

#define TRANSITION(stateMachine, stateData) \
    static_cast<AOSidf*>(context_)->transitionTo(std::make_shared<stateMachine>(stateData))

#define START_AOS(handler, queueLen, priority, stackSize, initialState, stateData) \
    handler->start(#handler, queueLen, priority, stackSize);\
    handler->transitionTo(std::make_shared<initialState>(stateData))

#define STOP_AOS(handler) \
    handler->getCurrentState()->exit();\
    handler->stop()

class AOSidf : public AOidf {
 protected:
    std::shared_ptr<HSMidf_state> _state;

    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void dispatch(uint32_t sig, void* data) override;

 public:
    void transitionTo(std::shared_ptr<HSMidf_state> state);
    std::shared_ptr<HSMidf_state> getCurrentState() { return _state; }
};