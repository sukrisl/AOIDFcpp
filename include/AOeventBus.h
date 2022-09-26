#pragma once

#include "AOidf.h"

class AOevent {
 private:
    std::vector<std::shared_ptr<AOidf>> _subscribers;

 public:
    uint32_t _flag;

    AOevent(uint32_t flag) : _flag(flag) {
        
    }

    void registerSubscriber(std::shared_ptr<AOidf> subscriber) {
        _subscribers.push_back(subscriber);
    }

    void notify();
};

class AOeventBus : public AOidf {
 private:
    std::vector<std::shared_ptr<AOevent>> _eventList;

    void _init() override;
    void dispatch(uint32_t eventFlag, void* eventData) override;

    std::shared_ptr<AOevent> lookupEvent(uint32_t flag);

 public:
    void createEvent(uint32_t flag);
    void createEvent(uint32_t flag, std::vector<std::shared_ptr<AOidf>> subscribers);
    void registerSubscriber(uint32_t flag, std::shared_ptr<AOidf> subscriber);
    void registerSubscriber(uint32_t flag, std::vector<std::shared_ptr<AOidf>> subscribers);
};