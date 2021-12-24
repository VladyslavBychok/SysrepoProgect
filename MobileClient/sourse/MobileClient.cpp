#include "MobileClient.hpp"

MobileClient::MobileClient() : MobileClient(std::make_unique<NetConfAgent>()){}

MobileClient::MobileClient(std::unique_ptr<INetConfAgent> NetConf) : _agent{std::move(NetConf)}{}

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

bool MobileClient::unregister(const std::string& number)
{
    if(_agent->fetchData(_path.getPath(number, Number)).first)
    {
        _name.clear();
        _number.clear();
        _incomingNumber.clear();

        return true;
    }

    return false;
}

void MobileClient::handleModuleChange(const std::string& value,const std::string& path)
{
    static std::string lastValue;

    if(value == "ActiveIncoming")
        std::cout << ">> Incoming call ..." << std::endl;

    else if(value == "Buzy")
        std::cout << ">> Start call" << std::endl;

    else if(value == "Idle" && lastValue == "Buzy")
        std::cout << ">> Finish call" << std::endl;

    lastValue = value;        
}

void MobileClient::setName(const std::string& name)
{
    _name = name;
    std::string path = _path.getPath(name, Name);
    _agent->changeData(path, name);
}

void MobileClient::setIncomingNumber(const std::string& incomingNumber)
{
    _incomingNumber = incomingNumber;
}

bool MobileClient::call(const std::string& number)
{
    if (!_agent->fetchData(_path.getPath(number, Number)).first)
        return false;

    if (_agent->fetchData(_path.getPath(number, State)).second == "Idle")
    {
        _incomingNumber = number;

        _agent->changeData(_path.getPath(_incomingNumber, IncomingNumber), _number);
        _agent->changeData(_path.getPath(_incomingNumber, State), "ActiveIncoming");

        _agent->changeData(_path.getPath(_number, IncomingNumber), number);
        _agent->changeData(_path.getPath(_number, State), "ActiveOutcoming");

        std::cout << ">> Call number: " << _incomingNumber << std::endl;

        return true;
    }

    return false;
}

bool MobileClient::Register(const std::string& number)
{   
    if (!_agent->fetchData(_path.getPath(number, Number)).first)
    {
        _agent->changeData(_path.getPath(number, Number), number);
        _agent->changeData(_path.getPath(number, State), "Idle");
        

        _number = number;
        _incomingNumber = "\0";
        _state = Idle;

        std::string path = _path.getPath(_number, Subscriber);

        _agent->subscribeForModelChange(path, *this);

        //_agent->registerOperData(_path.getPath(number, Name), *this);

        std::cout << ">> Register number: " << _number << std::endl;

        return true;
    }
 
    return false;
}

bool MobileClient::reject()
{
    if (_agent->fetchData(_path.getPath(_number, State)).second == "ActiveIncoming")
    {
        _incomingNumber = _agent->fetchData(_path.getPath(_number, IncomingNumber)).second;

        _agent->changeData(_path.getPath(_number, State), "Idle");
        _agent->changeData(_path.getPath(_number, IncomingNumber), "\0");

        _agent->changeData(_path.getPath(_incomingNumber, State), "Idle");
        _agent->changeData(_path.getPath(_incomingNumber, IncomingNumber), "\0");

        _incomingNumber = "\0";
        _state = Idle;

        std::cout << ">> Reject call." << std::endl;

        return true;
    }

    return false;
}

bool MobileClient::answer()
{
    if (_agent->fetchData(_path.getPath(_number, State)).second == "ActiveIncoming")
    {
        _incomingNumber = _agent->fetchData(_path.getPath(_number, IncomingNumber)).second;

        _agent->changeData(_path.getPath(_incomingNumber, State), "Buzy");
        _agent->changeData(_path.getPath(_number, State), "Buzy");

        _state = Buzy;

        return true;
    }

    return false;
}

bool MobileClient::callEnd()
{
    if (_agent->fetchData(_path.getPath(_number, State)).second == "Buzy")
    {
        _agent->changeData(_path.getPath(_number, State), "Idle");
        _agent->changeData(_path.getPath(_number, IncomingNumber), "\0");

        _agent->changeData(_path.getPath(_incomingNumber, State), "Idle");
        _agent->changeData(_path.getPath(_incomingNumber, IncomingNumber), "\0");

        _incomingNumber = "\0";
        _state = Idle;

        return true;
    }

    return false;
}