#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "AOidf.h"

class AOeventBus : public AOidf {
 private:
    std::vector<std::shared_ptr<AOidf>> _subscribers;

    void _init() override;
    void _deinit() override;
    void dispatch(uint32_t eventFlag, void* eventData) override;

 public:
    void attach(std::shared_ptr<AOidf> subscriber);
    void detach(std::shared_ptr<AOidf> subscriber);
};