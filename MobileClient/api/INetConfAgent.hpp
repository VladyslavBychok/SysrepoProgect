#pragma once

#include <iostream>
#include <atomic>
#include <optional>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Subscription.hpp>
#include <sysrepo-cpp/Connection.hpp>

#include "GeneratePath.hpp"

class MobileClient;

class INetConfAgent {
    public:
    
    virtual ~INetConfAgent() = default;

    virtual void subscribeForModelChange(const std::string& path, MobileClient& client) = 0;
    virtual std::pair<bool,std::string> fetchData(const std::string& path) = 0;
    virtual void changeData(const std::string& path, const std::string& str) = 0;
    virtual void registerOperData(const std::string& path, MobileClient& client) = 0;    
    virtual void deleteData(const std::string& path) = 0;

    
};