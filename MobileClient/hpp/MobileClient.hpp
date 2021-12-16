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

    /**
     * @brief Get the Name object
     * 
     * @return std::string name object
     */
    std::string getName();

    /**
     * @brief Get the Number object
     * 
     * @return std::string number
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
     * @return stateEnum state object
     */
    stateEnum getState();

    /**
     * @brief Set the Name object
     * 
     * @param name [in] name from set
     */
    void setName(const std::string& name);

    /**
     * @brief Set the Incoming Number object
     *  
     * @param incomingNumber [in] field from set Incoming number object
     */
    void setIncomingNumber(const std::string& incomingNumber);

    /**
     * @brief register number in DataBase
     * 
     * @param number [in] number from writing in DataBase
     * @return true successful registration
     * @return false unsuccessful registration
     */
    bool Register(std::string& number);

    /**
     * @brief call another user
     * 
     * @param number [in] user number from call
     * @return true successful call
     * @return false unsuccessful call
     */
    bool call(std::string& number);

    /**
     * @brief answer on incoming call
     */
    void answer(); 

    /**
     * @brief reject on incoming call
     */
    void reject();

    /**
     * @brief end call with another number
     */
    void callEnd();

    void handleModuleChange(const std::string& value,const std::string& path);
private:
    NetConfAgent _agent;
    GeneratePath _path;
    
    std::string _name;
    std::string _number;
    std::string _incomingNumber;
    stateEnum _state;
};