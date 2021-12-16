#pragma once
#include <gmock/gmock.h>
#include "../../MobileClient/api/INetConfAgent.hpp"

class NetConfAgentMock : INetConfAgent 
{
public:
    void work(){std::cout << "work\n";}


};