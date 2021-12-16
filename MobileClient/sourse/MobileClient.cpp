#include "MobileClient.hpp"

std::string MobileClient::getName()
{
    return _name;
}

std::string MobileClient::getNumber()
{
    return _number;
}

std::string MobileClient::getIncomingNumber()
{
    return _incomingNumber;
}

stateEnum MobileClient::getState()
{
    return _state;
}

void MobileClient::handleModuleChange(const std::string& value,const std::string& path)
{
    if(value == "ActiveIncoming"){
        std::cout << ">> Incoming call ..." << std::endl;
    }
}

void MobileClient::setName(const std::string& name)
{
    _name = name;
    std::string path = _path.getPath(name, Name);
    _agent.changeData(path, name);
}

void MobileClient::setIncomingNumber(const std::string& incomingNumber)
{
    _incomingNumber = incomingNumber;
}

bool MobileClient::call(std::string& number)
{
    if (!_agent.fetchData(_path.getPath(number, Number)).first)
        return false;

    if (_agent.fetchData(_path.getPath(number, State)).second == "Idle")
    {
        _incomingNumber = number;

        _agent.changeData(_path.getPath(_incomingNumber, IncomingNumber), _number);
        _agent.changeData(_path.getPath(_incomingNumber, State), "ActiveIncoming");

        _agent.changeData(_path.getPath(_number, IncomingNumber), number);
        _agent.changeData(_path.getPath(_number, State), "ActiveOutcoming");

        std::cout << ">> Call number: " << _incomingNumber << std::endl;

        return true;
    }
}

bool MobileClient::Register(std::string& number)
{
    if (!_agent.fetchData(_path.getPath(number, Number)).first)
    {

        _agent.changeData(_path.getPath(number, Number), number);
        _agent.changeData(_path.getPath(number, State), "Idle");
        

        _number = number;
        _incomingNumber = "\0";
        _state = Idle;

        std::string path = _path.getPath(_number, Subscriber);

        _agent.subscribeForModelChange(path, *this);

        _agent.registerOperData(_path.getPath(number, Name), *this);

        std::cout << ">> Register number: " << _number << std::endl;

        return true;
    }

    return false;
}

void MobileClient::reject()
{
    if (_agent.fetchData(_path.getPath(_number, State)).second == "ActiveIncoming")
    {
        _incomingNumber = _agent.fetchData(_path.getPath(_number, IncomingNumber)).second;

        _agent.changeData(_path.getPath(_number, State), "Idle");
        _agent.changeData(_path.getPath(_number, IncomingNumber), "\0");

        _agent.changeData(_path.getPath(_incomingNumber, State), "Idle");
        _agent.changeData(_path.getPath(_incomingNumber, IncomingNumber), "\0");

        _incomingNumber = "\0";
        _state = Idle;

        std::cout << ">> Reject call." << std::endl;
    }
}

void MobileClient::answer()
{
    if (_agent.fetchData(_path.getPath(_number, State)).second == "ActiveIncoming")
    {
        _incomingNumber = _agent.fetchData(_path.getPath(_number, IncomingNumber)).second;

        _agent.changeData(_path.getPath(_incomingNumber, State), "Buzy");
        _agent.changeData(_path.getPath(_number, State), "Buzy");

        _state = Buzy;

        std::cout << ">> Answer call." << std::endl;
    }
}

void MobileClient::callEnd()
{
    if (_agent.fetchData(_path.getPath(_number, State)).second == "Buzy")
    {
        _agent.changeData(_path.getPath(_number, State), "Idle");
        _agent.changeData(_path.getPath(_number, IncomingNumber), "\0");

        _agent.changeData(_path.getPath(_incomingNumber, State), "Idle");
        _agent.changeData(_path.getPath(_incomingNumber, IncomingNumber), "\0");

        _incomingNumber = "\0";
        _state = Idle;

        std::cout << ">> End call." << std::endl;
    }
}