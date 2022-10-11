#include "HSMidf.h"

void HSMidf_state::init() {
    if (cond_ == STATE_COND_OUT_OF_SERVICE) {
        setStateCondition(STATE_COND_ENTRY);
        entryAct();
        setStateCondition(STATE_COND_IDLE);
    } else { // Reinit state if state already active
        exit();
        init();
    }
}

void HSMidf_state::exit() {
    if (cond_ != STATE_COND_OUT_OF_SERVICE) {
        setStateCondition(STATE_COND_EXIT);
        exitAct();
        setStateCondition(STATE_COND_OUT_OF_SERVICE);
    }
}