#include "AOSidf.h"

void AOSidf::dispatch(uint32_t sig, void* data) {
    _state->signalIn(sig);
}

void AOSidf::transitionTo(std::shared_ptr<HSMidf_state> state) {
    if (_state) _state->exit();
    _state = state;
    _state->setContext(this);
    _state->init();
}