#ifndef bindings_hpp
#define bindings_hpp

#include <unordered_map>
#include <string>

struct VariableData{
    std::string type;
    int stackPosition;
};

class Bindings{
private:
    std::unordered_map<std::string, VariableData> bindings_;

    int stackPos_;
    int tempStackPos_;

public:
    Bindings();

    void insertBindings(std::string id, std::string type);

    int getStackPos();
    int getStackPos(std::string id);
    void increaseStackPos(int n);
    void increaseStackPos();
    void setStackPos(int n);

    void nextTempPos();
    void setTempPos(int n);
    int getTempPos();

};

#endif