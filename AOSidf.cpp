#include "HSMidf.h"
#include "AOSidf.h"

void AOSidf::_init() {
    // Default: do nothing
}

void AOSidf::initState(std::shared_ptr<HSMidf_state> state) {
    this->transitionTo(state);
}

void AOSidf::transitionTo(std::shared_ptr<HSMidf_state> state) {
    if (this->_state != NULL) {
        this->_state->exit();
    }
    
    this->_state = state;
    this->_state->setContext(this);
    this->_state->init();
}