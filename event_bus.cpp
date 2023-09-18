#include <iterator>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "event_bus.h"

static QueueHandle_t eventQueueHandle = NULL;

#define EVENT_POST_TIMEOUT_MS 1000

static void eventPostTask(void* pvParam) {
    EventProcess_t eventToProcess;
    
    while (true) {
        xQueueReceive(eventQueueHandle, &eventToProcess, portMAX_DELAY);
        Event_t event = eventToProcess.event;
        if (eventToProcess.listener->getStatus() == ActiveStatus_ao::ACTIVE_OBJECT_RUNNING) {
            eventToProcess.listener->post(
                event.id, pdMS_TO_TICKS(EVENT_POST_TIMEOUT_MS),
                event.data, event.dataSize
            );
        }
    }
}

void EventBus_ao::start() {
    eventQueueHandle = xQueueCreate(100, sizeof(EventProcess_t));
    xTaskCreate(eventPostTask, "event_bus", 10000, NULL, 10, NULL);
}

void EventBus_ao::attach(Active_ao* subscriber) {
    subscriberList_.push_back(subscriber);
}

void EventBus_ao::detach(Active_ao* subscriber) {
    subscriberList_.erase(std::remove(subscriberList_.begin(), subscriberList_.end(), subscriber), subscriberList_.end());
}

void EventBus_ao::detachAll() {
    std::list<Active_ao*>::iterator i;
    for (i = subscriberList_.begin(); i != subscriberList_.end() && (*i); ++i) {
        subscriberList_.erase(std::remove(subscriberList_.begin(), subscriberList_.end(), (*i)), subscriberList_.end());
    }
}

void EventBus_ao::post(Event_t event) {
    std::list<Active_ao*>::iterator i;
    for (i = subscriberList_.begin(); i != subscriberList_.end() && (*i); ++i) {
        if ((*i)->getStatus() == ActiveStatus_ao::ACTIVE_OBJECT_RUNNING) {
            EventProcess_t eventProcess = { event, (*i) };
            xQueueSend(eventQueueHandle, &eventProcess, EVENT_POST_TIMEOUT_MS);
        }
    }
}