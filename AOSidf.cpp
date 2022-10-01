#include "HSMidf.h"
#include "AOSidf.h"

void AOSidf::_init() {
    // Default: do nothing
}

void AOSidf::_deinit() {
    // Default: do nothing
}

void AOSidf::dispatch(uint32_t eventFlag, void* eventData) {
    _state->processEvent(eventFlag);
}

void AOSidf::start(const char* aoname, int32_t queueLen, uint8_t priority, uint32_t stackSize, std::shared_ptr<HSMidf_state> initState) {
    AOidf::start(aoname, queueLen, priority, stackSize);
    this->transitionTo(initState);
}

void AOSidf::stop() {
    this->_state->exit();
    AOidf::stop();
}

void AOSidf::transitionTo(std::shared_ptr<HSMidf_state> state) {
    if (this->_state) {
        this->_state->exit();
    }
    
    this->_state = state;
    this->_state->setContext(this);
    this->_state->init();
}