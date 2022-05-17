#pragma once

#include <functional>
#include <set>
#include <vector>


namespace lli {


class EventListener;


class EventBase {
public:
    virtual void Detach(EventListener *listener) = 0;
};


class EventListener
{
private:
    std::set<EventBase*> events;

public:
    ~EventListener()
    {
        while (!events.empty()) {
            auto e = *events.begin();

            e->Detach(this);
        }
    }

    void AddEvent(EventBase* event)
    {
        events.insert(event);
    }

    void RemoveEvent(EventBase* event)
    {
        events.erase(event);
    }
};


template <typename... Args>
class Event : public EventBase
{
private:
    class Handler
    {
    public:
        EventListener *listener;

        std::function<void(Args...)>    func;

        Handler(EventListener* listener, std::function<void(Args...)> func)
            :
            listener(listener),
            func(func)
        {
        }
    };

    std::vector<Handler> handlers;

public:
    void Attach(EventListener *listener, std::function<void(Args...)> func)
    {
        handlers.emplace_back(listener, func);

        listener->AddEvent(this);
    }

    virtual void Detach(EventListener *listener) override
    {
        std::vector<Handler> h = handlers;

        handlers.clear();

        for (size_t i=0; i<h.size(); i++) {
            if (h[i].listener != listener) {
                handlers.push_back(h[i]);
            }
        }

        listener->RemoveEvent(this);
    }

    void Dispatch(Args... args)
    {
        for (auto& handler : handlers)
            handler.func(args...);
    }
};


}