#pragma once

#include <memory>

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
    void* context_;
    std::shared_ptr<HSMidf_state> super_ = NULL;

    virtual void entryAct() = 0;
    virtual void exitAct() = 0;

 private:
    stateCond_t cond_ = STATE_COND_OUT_OF_SERVICE;

    void setStateCondition(stateCond_t cond) { cond_ = cond; };

 public:
    void init();
    void exit();
    void setContext(void* context) { this->context_ = context; }
    void* getContext() { return context_; }

    virtual transitionCode_t signalIn(uint32_t sig) = 0;
};