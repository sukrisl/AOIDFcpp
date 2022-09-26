#include "HSMidf.h"
#include "AOSidf.h"

void AOSidf::_init() {
    // Default: do nothing
}

void AOSidf::start(const char* aoname, int32_t queueLen, uint8_t priority, uint32_t stackSize, std::shared_ptr<HSMidf_state> initState) {
    this->transitionTo(initState);
    AOidf::start(aoname, queueLen, priority, stackSize);
}

void AOSidf::transitionTo(std::shared_ptr<HSMidf_state> state) {
    if (this->_state != NULL) {
        this->_state->exit();
    }
    
    this->_state = state;
    this->_state->setContext(this);
    this->_state->init();
}