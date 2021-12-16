#pragma once

#include "NetConfAgent.hpp"
#include "MobileClient.hpp"
#include "GeneratePath.hpp"

class MobileService final
{
public:

    /**
     * @brief main function
     *
     * @return int 0
     */
    int main();

    /**
     * @brief register number in DataBase
     *
     * @param number [in] number from writing in DataBase
     * @return true successful registration
     * @return false unsuccessful registration
     */
    bool Register(std::string& number);

    /**
     * @brief unregister number in DataBase
     *
     * @return true successful unregistration
     * @return false unsuccessful unregistration
     */
    bool unregister();

    /**
     * @brief Set the Name object
     *
     * @param name [in] name from set
     */
    void setName(std::string& name);

    /**
     * @brief call another user
     *
     * @param number [in] user number from call
     * @return true successful call
     * @return false unsuccessful call
     */
    bool call(std::string& number);

    /**
     * @brief end call with another number
     */
    void callEnd();

    /**
     * @brief answer on incoming call
     */
    void answer();

    /**
     * @brief reject on incoming call
     */
    void reject();

private:

    /**
     * @brief processing user command and call methods
     */
    void processingCommand();

    NetConfAgent _netAgent;
    MobileClient _mobClient;
    GeneratePath _path;

    std::string _command;
};