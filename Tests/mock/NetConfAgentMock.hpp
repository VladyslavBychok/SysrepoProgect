#pragma once
#include <gmock/gmock.h>
#include "INetConfAgent.hpp"

class NetConfAgentMock : public INetConfAgent
{
public:
    MOCK_METHOD2(subscribeForModelChange,void (const std::string& path, MobileClient &client));
    MOCK_METHOD1(fetchData,std::pair<bool, std::string> (const std::string& path));
    MOCK_METHOD2(registerOperData,void (const std::string& path, MobileClient &client));
    MOCK_METHOD2(changeData,void (const std::string& path, const std::string& str));
    MOCK_METHOD1(deleteData, void(const std::string& path));
};