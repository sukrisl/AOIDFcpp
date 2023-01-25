#pragma once

#include "HSMidf.h"

class HSMconcreteA : public HSMidf_state {
 protected:
    void entry() override;
    void exit() override;
 
 public:
    void signalIn(uint32_t sig) override;
};

class HSMconcreteB : public HSMidf_state {
 protected:
    void entry() override;
    void exit() override;
 
 public:
    void signalIn(uint32_t sig) override;
};

class HSMconcreteC : public HSMidf_state {
 protected:
    void entry() override;
    void exit() override;
 
 public:
    void signalIn(uint32_t sig) override;
};