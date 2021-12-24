#include "MobileClient.hpp"
#include "NetConfAgent.hpp"
#include "NetConfAgentMock.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace
{
const std::string pathNumberOne = "/Network:commutator/subscribers/subscriber[number = '123']/number";
const std::string pathNumberTwo = "/Network:commutator/subscribers/subscriber[number = '234']/number";
const std::string pathStateTwo = "/Network:commutator/subscribers/subscriber[number = '234']/state";
const std::string name = "John";
const std::string numberOne = "123";
const std::string numberTwo = "234";
}

using testing::StrictMock;
using testing::_;
/*
tests
*/

namespace test
{

class MobileClientTest:public testing::Test
{
protected:
    void SetUp() override
    {
        auto tempMock = std::make_unique<StrictMock<NetConfAgentMock>>();

        _mock = tempMock.get();
        _client = std::make_unique<MobileClient>(std::move(tempMock));
        
        
      
    }

    std::unique_ptr <MobileClient> _client;
    StrictMock <NetConfAgentMock>* _mock;
    
};

TEST_F(MobileClientTest, setNameTest)
{
    EXPECT_CALL(*_mock, changeData(_,_)).Times(1);
    _client->setName(name);
    EXPECT_EQ(_client->getName(), name);
}

TEST_F(MobileClientTest, setIncomingNumberTest)
{
    _client->setIncomingNumber(numberOne);
    EXPECT_EQ(_client->getIncomingNumber(),numberOne);
}

TEST_F(MobileClientTest, RegisterTestTrue)
{
    std::pair<bool,std::string> ans{false, ""};

    EXPECT_CALL(*_mock, fetchData(pathNumberOne))
        .WillOnce(testing::Return(ans));

    EXPECT_CALL(*_mock, changeData(_,_))
        .Times(2);
    EXPECT_CALL(*_mock, subscribeForModelChange(_,_))
        .Times(1);

    EXPECT_TRUE(_client->Register(numberOne));
}

TEST_F(MobileClientTest, RegisterTestFalse)
{
    std::pair<bool,std::string> ans{true, pathNumberOne};

    EXPECT_CALL(*_mock, fetchData(pathNumberOne))
        .WillOnce(testing::Return(ans));

    EXPECT_FALSE(_client->Register(numberOne));
}

TEST_F(MobileClientTest, callTestTrue)
{
    std::pair<bool,std::string> ans{true, "Idle"};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillRepeatedly(testing::Return(ans));
       
    EXPECT_CALL(*_mock, changeData(_,_))
        .Times(4);

    EXPECT_TRUE(_client->call(pathNumberTwo));
}

TEST_F(MobileClientTest, callTestFalse)
{
    std::pair<bool,std::string> ans{false, ""};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillOnce(testing::Return(ans));

    EXPECT_FALSE(_client->call(pathNumberTwo));
}

TEST_F(MobileClientTest, unregisterTestFalse)
{
    std::pair<bool,std::string> ans{false, ""};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillOnce(testing::Return(ans));

    EXPECT_FALSE(_client->unregister(numberOne));
}

TEST_F(MobileClientTest, unregisterTestTrue)
{
    std::pair<bool,std::string> ans{true, ""};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillOnce(testing::Return(ans));

    EXPECT_TRUE(_client->unregister(numberOne));
}

TEST_F(MobileClientTest, rejectTestFalse)
{
    std::pair<bool,std::string> ans{true, "Buzy"};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillOnce(testing::Return(ans));

    EXPECT_FALSE(_client->reject());
}

TEST_F(MobileClientTest, rejectTestTrue)
{
    std::pair<bool,std::string> ans{true, "ActiveIncoming"};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillRepeatedly(testing::Return(ans));

    EXPECT_CALL(*_mock, changeData(_,_))
        .Times(4);

    EXPECT_TRUE(_client->reject());
}

TEST_F(MobileClientTest, answerTestFalse)
{
    std::pair<bool,std::string> ans{true, "Buzy"};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillOnce(testing::Return(ans));

    EXPECT_FALSE(_client->answer());
}

TEST_F(MobileClientTest, answerTestTrue)
{
    std::pair<bool,std::string> ans{true, "ActiveIncoming"};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillRepeatedly(testing::Return(ans));

    EXPECT_CALL(*_mock, changeData(_,_))
        .Times(2);

    EXPECT_TRUE(_client->answer());
}

TEST_F(MobileClientTest, callEndTestFalse)
{
    std::pair<bool,std::string> ans{true, ""};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillOnce(testing::Return(ans));

    EXPECT_FALSE(_client->callEnd());
}

TEST_F(MobileClientTest, callEndTestTrue)
{
    std::pair<bool,std::string> ans{true, "Buzy"};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillOnce(testing::Return(ans));

    EXPECT_CALL(*_mock, changeData(_,_))
        .Times(4);

    EXPECT_TRUE(_client->callEnd());
}
}