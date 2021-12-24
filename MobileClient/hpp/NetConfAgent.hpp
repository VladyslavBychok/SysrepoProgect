#pragma once

#include "INetConfAgent.hpp"

class NetConfAgent : public INetConfAgent
{
    public:
    /**
     * @brief Construct a new Netopeer Config Agent object
     */
    NetConfAgent();
    
    /**
     * @brief Method for subscribe for change model with adress path
     * 
     * @param [in] path Const param, model adress 
     * @param [in] client MobileClient object for calling method handleModuleChange in Call Back
     */
    void subscribeForModelChange(const std::string& path, MobileClient& client) override;
    /**
     * @brief Method for read field in DataBase with adress path
     * 
     * @param [in] path Adress of DataBase
     * @return std::pair<bool,std::string> First - status reading field, second - field in DataBase
     */
    std::pair<bool,std::string> fetchData(const std::string& path) override;
    /**
     * @brief Method for change or set field in DataBase with adress path
     * 
     * @param [in] path Adress of DataBase
     * @param [in] str The value that is set
     */
    void changeData(const std::string& path, const std::string& str) override;
    /**
     * @brief Register operData from user number
     * 
     * @param [in] path Adress in dataBase
     * @param [in] client Client from register 
     */
    void registerOperData(const std::string& path, MobileClient& client) override;    
    /**
     * @brief Delete subscriber from number
     * 
     * @param [in] path Adress in dataBase
     */
    void deleteData(const std::string& path);

    private:

    sysrepo::Connection _conn;
    sysrepo::Session _sess;
    GeneratePath _path;
    //std::atomic<int>  _called = 0;
    std::optional<sysrepo::Subscription> _sub;
    std::optional<sysrepo::Subscription> _subscribeOperData;
    
    
};