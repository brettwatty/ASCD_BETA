#include <Arduino.h>
#include <structVariables.h>
class returnCodes
{

private:
    byte codeID;
    bool debugMode;

public:
    returnCodes(byte codeID, bool debugMode);
    void process();
    void init();
};