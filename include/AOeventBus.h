#pragma once

#include <algorithm>
#include <list>

#include "AOidf.h"

class AOeventBus : public AOidf {
 protected:
    void dispatch(uint32_t sig, void* data) override;

 private:
    std::list<std::shared_ptr<AOidf>> subscriberList_;

 public:
    void attach(std::shared_ptr<AOidf> subscriber);
    void detach(std::shared_ptr<AOidf> subscriber);
};