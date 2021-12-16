//#include "NetConfAgent.hpp"
//#include "MobileClient.hpp"
#include "MobileService.hpp"
#include <string>

/*
commands:
register name number
call number
unregister
rename name
callend
answer
reject
*/

class TerminalRead final {
    public:

    void input(){
        std::cin >> command_;
    }

    std::string getCommand() const {
        return command_;
    }

    private:

    std::string command_;
};

class ProcessingQuery final {
    public:

    void selection(std::string command) {

        if( command == "register"){
            std::string name;
            std::string number;

            std::cin >> name;
            std::cin >> number;

            registers(name, number);
        }

        else if(command == "call"){
            std::string number;

            std::cin >> number;

            call(number);
        }
        
        else if(command == "unregister")
            unregisters();

        else if(command == "rename"){
            std::string name;

            std::cin >> name;

            setName(name);
        }

        else if(command == "callend")
            callEnd();

        else if(command == "answer")
            answer();

        else if(command == "reject")
            reject();
    }

    private:

    bool registers(std::string name, std::string number) const{ 
        std::cout << "register user \n";
        std::cout << "regisrer name: " << name << std::endl;
        std::cout << "register number: " << number << std::endl;
    }

    bool unregisters() const{
        std::cout << "unregister user \n";
    }   

    void setName(std::string name) const{
        std::cout << "setName user \n";
        std::cout << "new name: " << name << std::endl;

    }

    bool call(std::string number) const{
        std::cout << "call user: " << number << std::endl;
    }

    void callEnd() const{
        std::cout << "cellEnd \n";
    }

    void answer() const{
        std::cout << "answer user \n";
    }

    void reject() const{
        std::cout << "reject\n";
    }
};


int main(int argc, char **argv)
{

   /* NetConfAgent A;
    
    TerminalRead read;
    ProcessingQuery process;
    MobileClient B;
    std::string str = "1231312";

    while(read.getCommand() != "end"){

        A.subscribeForModelChange();
        
        read.input();

        process.selection(read.getCommand());

        //A.fethchData("/Network:commutator/subscribers/subscriber[number='Mike']/userName", str);
        

        //A.changeData("/Network:commutator/subscribers/subscriber[number='Mike']/userName", str);
        A.changeData("/Network:commutator/subscribers/subscriber[number='Mike']/state", "121212121");
    
        A.fethchData("/Network:commutator/subscribers/subscriber[number='Mike']/state");
    }*/

    MobileService A;

    A.main();
    return 0;
}