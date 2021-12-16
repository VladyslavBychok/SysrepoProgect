#pragma once
#include <gmock/gmock.h>
#include "../../MobileClient/api/INetConfAgent.hpp"

class NetConfAgentMock : public INetConfAgent
{
public:
    MOCK_METHOD3( subscribeForModelChanges,bool (std::string modelName, std::string path, MobileClient &client));
    MOCK_METHOD2(fetchData,bool(std::string path, std::string &str));
    MOCK_METHOD3(registerOperData,bool(std::string modelName, std::string path, MobileClient &client));
    MOCK_METHOD2(changeData,void (const std::string path, std::string value));
    MOCK_METHOD1(deleteData, void(const std::string path));
};