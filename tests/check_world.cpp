#include <bandit/bandit.h>

#include "world.h"

using namespace std;
using namespace bandit;
using namespace Splash;

go_bandit([]() {
    /*********/
    describe("World class", []() {
        int argc = 2;
        char* argv[2] {"-f", "../data/config.json"};

        it("should load the configuration correctly", [&]() {
            World world(argc, argv); 
            world.run();
            AssertThat(world.getStatus(), Equals(true));
        });
    });

});

/*************/
int main(int argc, char** argv)
{
    SLog::log.setVerbosity(Log::NONE);
    return bandit::run(argc, argv);
}
