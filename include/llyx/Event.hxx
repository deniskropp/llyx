#pragma once

#include <eventpp/callbacklist.h>

namespace lli {

template <typename... Args>
class Event
{
private:
    std::vector<std::function<void(Args...)>> handlers;
//	eventpp::CallbackList<void (Args...)> callbackList;

public:
    void Attach(std::function<void(Args...)> handler)
    {
        handlers.push_back(handler);
//    	callbackList.append([handler](Args... args) {
//	    	handler(args...);
//	    });
    }

    void Dispatch(Args... args)
    {
//    	callbackList(args...);
        for (auto handler : handlers)
            handler(args...);
    }
};

}