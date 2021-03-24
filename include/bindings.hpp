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
    int functionEndLabel_;

    std::string breakLabel_;
    std::string continueLabel_;

public:
    Bindings();

    void insertBindings(std::string id, std::string type, int stackPosition = -1);

    int getStackPos();
    int getStackPos(std::string id);
    void increaseStackPos(int n);
    void increaseStackPos();
    void setStackPos(int n);

    void nextTempPos();
    void setTempPos(int n);
    int getTempPos();

    void setFunctionEndLabel(int n);
    int getFunctionEndLabel();

    void setBreakLabel(std::string label);
    void setContinueLabel(std::string label);

    std::string getBreakLabel();
    std::string getContinueLabel();

};

#endif