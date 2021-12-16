#pragma once

#include <iostream>
#include <atomic>
#include <optional>
#include <sysrepo-cpp/Session.hpp>
#include <sysrepo-cpp/Subscription.hpp>
#include <sysrepo-cpp/Connection.hpp>

#include "GeneratePath.hpp"
#include "../api/INetConfAgent.hpp"

class MobileClient;

class NetConfAgent : public INetConfAgent
{
    public:
    /**
     * @brief Construct a new Netopeer Config Agent object
     */
    NetConfAgent();
    /**
     * @brief method for subscribe for change model with adress path
     * 
     * @param path [in] const param, model adress 
     * @param client [in] MobileClient object for calling method handleModuleChange in Call Back
     */
    void subscribeForModelChange(const std::string& path, MobileClient& client) override;
    /**
     * @brief method for read field in DataBase with adress path
     * 
     * @param path [in] adress of DataBase
     * @return std::pair<bool,std::string> first - status reading field, second - field in DataBase
     */
    std::pair<bool,std::string> fetchData(const std::string& path) override;
    /**
     * @brief method for change or set field in DataBase with adress path
     * 
     * @param path [in] adress of DataBase
     * @param str [in] the value that is set
     */
    void changeData(const std::string& path, const std::string& str) override;

    void registerOperData(const std::string& path, MobileClient& client) override;    

    private:

    sysrepo::Connection _conn;
    sysrepo::Session _sess;
    GeneratePath _path;
    //std::atomic<int>  _called = 0;
    std::optional<sysrepo::Subscription> _sub;
    std::optional<sysrepo::Subscription> _subscribeOperData;
    
};