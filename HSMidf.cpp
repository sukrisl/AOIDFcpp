#include "HSMidf.h"

void HSMidf_state::setStateCondition(stateCond_t cond) {
    _cond = cond;
}

void HSMidf_state::init() {
    if (_cond == STATE_COND_OUT_OF_SERVICE) {
        setStateCondition(STATE_COND_ENTRY);
        entryAct();
        setStateCondition(STATE_COND_IDLE);
    } else { // Reinit state if state already active
        exit();
        init();
    }
}

void HSMidf_state::exit() {
    setStateCondition(STATE_COND_EXIT);
    exitAct();
    setStateCondition(STATE_COND_OUT_OF_SERVICE);
}

void HSMidf_state::setContext(void* context) {
    this->_context = context;
}