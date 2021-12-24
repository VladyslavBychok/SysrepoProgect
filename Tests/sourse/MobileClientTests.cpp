#include "MobileClient.hpp"
#include "NetConfAgent.hpp"
#include "NetConfAgentMock.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace
{
const std::string PATH_NUMBER_ONE = "/Network:commutator/subscribers/subscriber[number = '123']/number";
const std::string PATH_NUMBER_TWO = "/Network:commutator/subscribers/subscriber[number = '234']/number";
const std::string PATH_STATE_TWO = "/Network:commutator/subscribers/subscriber[number = '234']/state";
const std::string NAME = "John";
const std::string NUMBER_ONE = "123";
const std::string NUMBER_TWO = "234";
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

TEST_F(MobileClientTest, setNAMETest)
{
    EXPECT_CALL(*_mock, changeData(_,_)).Times(1);
    _client->setName(NAME);
    EXPECT_EQ(_client->getName(), NAME);
}

TEST_F(MobileClientTest, setIncomingNumberTest)
{
    _client->setIncomingNumber(NUMBER_ONE);
    EXPECT_EQ(_client->getIncomingNumber(),NUMBER_ONE);
}

TEST_F(MobileClientTest, RegisterTestTrue)
{
    std::pair<bool,std::string> ans{false, ""};

    EXPECT_CALL(*_mock, fetchData(PATH_NUMBER_ONE))
        .WillOnce(testing::Return(ans));

    EXPECT_CALL(*_mock, changeData(_,_))
        .Times(2);
    EXPECT_CALL(*_mock, subscribeForModelChange(_,_))
        .Times(1);

    EXPECT_TRUE(_client->Register(NUMBER_ONE));
}

TEST_F(MobileClientTest, RegisterTestFalse)
{
    std::pair<bool,std::string> ans{true, PATH_NUMBER_ONE};

    EXPECT_CALL(*_mock, fetchData(PATH_NUMBER_ONE))
        .WillOnce(testing::Return(ans));

    EXPECT_FALSE(_client->Register(NUMBER_ONE));
}

TEST_F(MobileClientTest, callTestTrue)
{
    std::pair<bool,std::string> ans{true, "Idle"};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillRepeatedly(testing::Return(ans));
       
    EXPECT_CALL(*_mock, changeData(_,_))
        .Times(4);

    EXPECT_TRUE(_client->call(PATH_NUMBER_TWO));
}

TEST_F(MobileClientTest, callTestFalse)
{
    std::pair<bool,std::string> ans{false, ""};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillOnce(testing::Return(ans));

    EXPECT_FALSE(_client->call(PATH_NUMBER_TWO));
}

TEST_F(MobileClientTest, unregisterTestFalse)
{
    std::pair<bool,std::string> ans{false, ""};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillOnce(testing::Return(ans));

    EXPECT_FALSE(_client->unregister(NUMBER_ONE));
}

TEST_F(MobileClientTest, unregisterTestTrue)
{
    std::pair<bool,std::string> ans{true, ""};

    EXPECT_CALL(*_mock, fetchData(_))
        .WillOnce(testing::Return(ans));

    EXPECT_TRUE(_client->unregister(NUMBER_ONE));
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