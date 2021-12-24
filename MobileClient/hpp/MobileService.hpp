#pragma once

#include "NetConfAgent.hpp"
#include "MobileClient.hpp"
#include "GeneratePath.hpp"

class MobileService final
{
public:

    /**
     * @brief Main function
     *
     * @return int 0
     */
    int main();

    /**
     * @brief Register number in DataBase
     *
     * @param [in] number Number from writing in DataBase
     * @return true Successful registration
     * @return false Unsuccessful registration
     */
    bool Register(std::string& number);

    /**
     * @brief Unregister number in DataBase
     *
     * @return true Successful unregistration
     * @return false Unsuccessful unregistration
     */
    bool unregister();

    /**
     * @brief Set the Name object
     *
     * @param [in] name Name from set
     */
    void setName(std::string& name);

    /**
     * @brief Call another user
     *
     * @param [in] number User number from call
     * @return true Successful call
     * @return false Unsuccessful call
     */
    bool call(std::string& number);

    /**
     * @brief End call with another number
     */
    void callEnd();

    /**
     * @brief Answer on incoming call
     */
    void answer();

    /**
     * @brief Reject on incoming call
     */
    void reject();

private:

    /**
     * @brief Processing user command and call methods
     */
    void processingCommand();

    NetConfAgent _netAgent;
    MobileClient _mobClient;
    GeneratePath _path;

    std::string _command;
};