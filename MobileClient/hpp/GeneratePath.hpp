#pragma once

#include <iostream>
#include <string>

enum VariantsPath
{
    Name,
    IncomingNumber,
    State,
    Number,
    Subscriber
};

class GeneratePath final
{
public:
    std::string getPath(std::string number, VariantsPath path);
    const std::string _model = "/Network";
private:
    std::string _path;
    
    
    const std::string _subscriber = _model + ":commutator/subscribers/subscriber[number = 'KEY']";
    const std::string _pathName = _model + ":commutator/subscribers/subscriber[number = 'KEY']/userName";
    const std::string _pathIncomingNumber = _model + ":commutator/subscribers/subscriber[number = 'KEY']/incomingNumber";
    const std::string _pathState = _model + ":commutator/subscribers/subscriber[number = 'KEY']/state";
    const std::string _pathNumber = _model + ":commutator/subscribers/subscriber[number = 'KEY']/number";
};
