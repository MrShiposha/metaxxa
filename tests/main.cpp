#include <vector>

#include "TestMetaxxa.h"
#include "TestFunction.h"
#include "TestMoveFunctionArgumentTypes.h"
#include "TestTuple.h"
#include "TestType.h"

int main(int argc, char **argv)
{
    std::vector<std::shared_ptr<TestMetaxxa>> tests = 
    {
        std::make_shared<TestFunction>(),
        std::make_shared<TestMoveFunctionArgumentTypes>(),
        std::make_shared<TestTuple>(),
        std::make_shared<TestType>()  
    };

    for(auto &&test : tests)
        if(!test->test())
            return -1;

    std::cout << "All test succeeded" << std::endl;

    return 0;
}
