#include "AOSidf.h"

void AOSidf::dispatch(uint32_t sig, void* data) {
    _state->signalIn(sig, data);
}

void AOSidf::transitionTo(std::shared_ptr<HSMidf_state> state) {
    if (_state) _state->exit();
    state->setContext(this);
    state->entry();
    _state = state;
}