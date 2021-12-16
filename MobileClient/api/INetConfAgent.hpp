#pragma once

#include <iostream>
#include <atomic>
#include <optional>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Subscription.hpp>
#include <sysrepo-cpp/Connection.hpp>

#include "../hpp/GeneratePath.hpp"

class INetConfAgent {
    public:
    INetConfAgent();
    virtual void subscribeForModelChange(const std::string& path, MobileClient& client);
    virtual std::pair<bool,std::string> fetchData(const std::string& path);
    virtual void changeData(const std::string& path, const std::string& str);
    virtual void registerOperData(const std::string& path, MobileClient& client);    

    private:

    sysrepo::Connection _conn;
    sysrepo::Session _sess;
    GeneratePath _path;
    std::optional<sysrepo::Subscription> _sub;
    std::optional<sysrepo::Subscription> _subscribeOperData;
};