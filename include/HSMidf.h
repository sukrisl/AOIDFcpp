#pragma once

#include <memory>

class AOSidf;

typedef enum {
    STATE_COND_OUT_OF_SERVICE = 0,
    STATE_COND_ENTRY,
    STATE_COND_IDLE,
    STATE_COND_EXIT,
} stateCond_t;

typedef enum {
    TRANSITION_OK = 0,
    TRANSITION_FAIL,
    TRANSITION_IGNORE,
} transitionCode_t;

class HSMidf_state {
 protected:
    AOSidf* _context;
    std::shared_ptr<HSMidf_state> _superstate = NULL;

    virtual void entryAct() = 0;
    virtual void exitAct() = 0;

 private:
    stateCond_t _cond = STATE_COND_OUT_OF_SERVICE;

    void setStateCondition(stateCond_t cond);

 public:
    void init();
    void exit();
    void setContext(AOSidf* context);

    virtual transitionCode_t processEvent(uint32_t eventFlag) = 0;
};