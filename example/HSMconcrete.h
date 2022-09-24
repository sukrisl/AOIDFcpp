#pragma once

#include "HSMidf.h"

class HSMconcreteA : public HSMidf_state {
 protected:
    void entryAct() override;
    void exitAct() override;
 
 public:
    transitionCode_t processEvent(uint32_t eventFlag) override;
};

class HSMconcreteB : public HSMidf_state {
 protected:
    void entryAct() override;
    void exitAct() override;
 
 public:
    transitionCode_t processEvent(uint32_t eventFlag) override;
};

class HSMconcreteC : public HSMidf_state {
 protected:
    void entryAct() override;
    void exitAct() override;
 
 public:
    transitionCode_t processEvent(uint32_t eventFlag) override;
};