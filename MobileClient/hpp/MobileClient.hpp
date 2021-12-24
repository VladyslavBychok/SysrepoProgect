#pragma once

#include "NetConfAgent.hpp"

enum stateEnum
{
    Idle,
    ActiveIncoming,
    ActiveOutcoming,
    Buzy
};

class MobileClient final
{
public:
    MobileClient();

    MobileClient(std::unique_ptr<INetConfAgent> NetConf);
    /**
     * @brief Get the Name object
     * 
     * @return std::string Name object
     */
    std::string getName();

    /**
     * @brief Get the Number object
     * 
     * @return std::string Number
     */
    std::string getNumber();

    /**
     * @brief Get the Incoming Number object
     * 
     * @return std::string Incoming number
     */
    std::string getIncomingNumber();

    /**
     * @brief Get the State object
     * 
     * @return stateEnum State object
     */
    stateEnum getState();

    /**
     * @brief Set the Name object
     * 
     * @param [in] name Name from set
     */
    void setName(const std::string& name);

    /**
     * @brief Set the Incoming Number object
     *  
     * @param [in] incomingNumber  Field from set Incoming number object
     */
    void setIncomingNumber(const std::string& incomingNumber);

    /**
     * @brief Register number in DataBase
     * 
     * @param [in] number  Number from writing in DataBase
     * @return true Successful registration
     * @return false Unsuccessful registration
     */
    bool Register(const std::string& number);

    /**
     * @brief Call another user
     * 
     * @param [in] number  User number from call
     * @return true Successful call
     * @return false Unsuccessful call
     */
    bool call(const std::string& number);

    /**
     * @brief Answer on incoming call
     */
    bool answer(); 

    /**
     * @brief Reject on incoming call
     */
    bool reject();

    /**
     * @brief End call with another number
     */
    bool callEnd();
    
    /**
     * @brief Reaction to changes
     * 
     * @param [in] value Change value
     * @param [in] path Adress change data
     */
    void handleModuleChange(const std::string& value,const std::string& path);
    
    /**
     * @brief Unregister user
     * 
     * @param [in] number User number from unregister
     * @return true Successful unregister
     * @return false Unsuccessful unregister
     */
    bool unregister(const std::string& number);

private:
    std::unique_ptr<INetConfAgent> _agent;
    //NetConfAgent _agent;
    GeneratePath _path;
    
    std::string _name;
    std::string _number;
    std::string _incomingNumber;
    stateEnum _state;
};