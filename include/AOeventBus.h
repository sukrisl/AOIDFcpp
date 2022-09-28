#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "AOidf.h"

class AOevent {
 private:
    std::vector<std::shared_ptr<AOidf>> _subscribers;

 public:
    uint32_t _flag;

    AOevent(uint32_t flag) : _flag(flag) {}

    void attach(std::shared_ptr<AOidf> subscriber) {
        _subscribers.push_back(subscriber);
    }

    void notify();
};

class AOeventBus : public AOidf {
 private:
    std::unordered_map<uint32_t, std::shared_ptr<AOevent>> _eventList;

    void _init() override;
    void dispatch(uint32_t eventFlag, void* eventData) override;

 public:
    void createEvent(uint32_t flag);
    void createEvent(uint32_t flag, std::shared_ptr<AOidf> subscriber);
    void attach(uint32_t flag, std::shared_ptr<AOidf> subscriber);
    void attach(uint32_t flag, std::vector<std::shared_ptr<AOidf>> subscribers);
};