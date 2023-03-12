#include <zz/zz.h>

using namespace zz::io;
using namespace zz::log;

auto main() -> int
{
    Logger log("test.txt");

    log.Log<Info>("Hello, world!");

    return 0;
}
