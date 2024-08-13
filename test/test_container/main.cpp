#include "sync_queue.h"

class TestClass
{
public:
    TestClass(int n) : val(n){};
    ~TestClass(){};

private:
    int val;
};

int main(int argc, char *argv[])
{
    kgr::container::SyncQueue<TestClass *> queue;
    for (int i = 0; i < 10; i++) {
        auto obj = new TestClass(i);
        queue.push_back(obj);
    }
    queue.shutdown();
    return 0;
}
