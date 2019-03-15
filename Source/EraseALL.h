#include <iostream>
using namespace std;

class EraseALL {
public:
    void erase();
    EraseALL(string diskname);
    ~EraseALL();

private:
    string disk;
};

