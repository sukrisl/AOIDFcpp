#pragma once

#include "HSMidf.h"

class HSMconcreteA : public HSMidf_state {
 protected:
    void entryAct() override;
    void exitAct() override;
 
 public:
    transitionCode_t signalIn(uint32_t sig) override;
};

class HSMconcreteB : public HSMidf_state {
 protected:
    void entryAct() override;
    void exitAct() override;
 
 public:
    transitionCode_t signalIn(uint32_t sig) override;
};

class HSMconcreteC : public HSMidf_state {
 protected:
    void entryAct() override;
    void exitAct() override;
 
 public:
    transitionCode_t signalIn(uint32_t sig) override;
};