#include "MobileService.hpp"

int MobileService::main()
{
    while (_command != "end")
    {
        if (std::cin.peek() == '\0')
        {
            //TODO: output message and system notification
        }
        else
        {
            std::cin >> _command;
            processingCommand();
        }
    }
}

void MobileService::processingCommand()
{

    if (_command == "register")
    {
        std::string number;
        std::cin >> number;

        Register(number);
    }

    else if (_command == "call")
    {
        std::string number;
        std::cin >> number;

        call(number);
    }

    else if (_command == "unregister")
        unregister();

    else if (_command == "rename")
    {
        std::string name;
        std::cin >> name;

        setName(name);
    }

    else if (_command == "callend")
        callEnd();

    else if (_command == "answer")
        answer();

    else if (_command == "reject")
        reject();
}

bool MobileService::Register(std::string& number)
{
    
    bool result = _mobClient.Register(number);

    std::cout << ">> register\n";
    return result;
}

bool MobileService::unregister(){return true;}

void MobileService::setName(std::string& name)
{
    _mobClient.setName(name);
}

bool MobileService::call(std::string& number)
{
    bool result = _mobClient.call(number);
    return result;
}

void MobileService::callEnd()
{
    _mobClient.callEnd();
}

void MobileService::answer()
{
    _mobClient.answer();
}
 
void MobileService::reject()
{
    _mobClient.reject();
}