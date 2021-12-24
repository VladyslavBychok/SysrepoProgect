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
    /**
     * @brief Get the Path object
     * 
     * @param [in] number 
     * @param [in] path 
     * @return std::string Generete path
     */
    std::string getPath(std::string number, VariantsPath path);
    
    /**
     * @brief Return model name
     * 
     */
    const std::string _model = "Network";

private:
    std::string _path;
    
    
    const std::string _subscriber         = "/Network:commutator/subscribers/subscriber[number = 'KEY']";
    const std::string _pathName           = "/Network:commutator/subscribers/subscriber[number = 'KEY']/userName";
    const std::string _pathIncomingNumber = "/Network:commutator/subscribers/subscriber[number = 'KEY']/incomingNumber";
    const std::string _pathNumber         = "/Network:commutator/subscribers/subscriber[number = 'KEY']/number";
    const std::string _pathState          = "/Network:commutator/subscribers/subscriber[number = 'KEY']/state";
};
