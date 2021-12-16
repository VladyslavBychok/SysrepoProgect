#include "NetConfAgent.hpp"
#include "MobileClient.hpp"

NetConfAgent::NetConfAgent() : _conn(), _sess(_conn.sessionStart())
{
    _sess.copyConfig(sysrepo::Datastore::Running, "Network");
}

std::pair<bool, std::string> NetConfAgent::fetchData(const std::string& path)
{
    std::optional<libyang::DataNode> data = _sess.getData(path.c_str());
    std::pair<bool, std::string> dataFetch;

    if (data)
    {
        dataFetch.second = data->findPath(path.c_str()).value().asTerm().valueStr();
        dataFetch.first = true;
    }
    else
    {
        dataFetch.second = {};
        dataFetch.first = false;
    }

    return dataFetch;
}

void NetConfAgent::changeData(const std::string& path, const std::string& str)
{
    if (!path.empty())
    {
        _sess.setItem(path.c_str(), str.c_str());
        _sess.applyChanges();
    }

}

void NetConfAgent::subscribeForModelChange(const std::string& path, MobileClient& client)
{    
  
    sysrepo::ModuleChangeCb moduleChangeCb = [&](sysrepo::Session session, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode
    {
        auto changeCollection = session.getChanges();

        for(auto entry : changeCollection)
        {
            if(entry.node.schema().nodeType() == libyang::NodeType::Leaf)
            {
                client.handleModuleChange(
                    static_cast<std::string>(entry.node.asTerm().valueStr()), 
                    static_cast<std::string>(entry.node.path()));
            }
        }

        return sysrepo::ErrorCode::Ok;
    };

    _sub = _sess.onModuleChange("Network", moduleChangeCb, path.c_str(), 0, sysrepo::SubscribeOptions::DoneOnly);
    
}

void NetConfAgent::registerOperData(const std::string& path, MobileClient& client)
{
    sysrepo::ErrorCode statusError;

    sysrepo::OperGetItemsCb operGetItemCb = [&](sysrepo::Session session, auto, auto, auto, auto, auto, auto) -> sysrepo::ErrorCode
    {
        std::string value = client.getName();
        auto parent = session.getContext().newPath(path.c_str(), value.c_str());
        statusError = sysrepo::ErrorCode::Ok;
        return statusError;
    };

    _subscribeOperData = _sess.onOperGetItems(_path._model.c_str(), operGetItemCb, path.c_str());
    //sysrepo::OperGetItemsCb 
}
