#pragma once

class HSMidf_state {
 protected:
    void* context_;

 public:
    virtual void entry() = 0;
    virtual void exit() = 0;
    void setContext(void* context) { this->context_ = context; }

    virtual void signalIn(uint32_t sig, void* data) = 0;
};