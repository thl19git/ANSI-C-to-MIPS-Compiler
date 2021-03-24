#ifndef parameter_hpp
#define parameter_hpp

#include "node.hpp"

class Parameter;

typedef Parameter* ParameterPtr;

class Parameter : public Node {
protected:
    std::string type_;
    std::string id_;

    ParameterPtr nextParameter_;

public:
    Parameter(std::string type, std::string id);
    void linkParameter(ParameterPtr parameter);
    Bindings printParameterASM(Bindings bindings, int mem, int num);
    int countParameters();
    void print();
    Bindings printASM(Bindings bindings);
};

#endif