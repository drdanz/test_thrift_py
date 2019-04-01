// copyright

#include <yarp/os/Network.h>
#include <yarp/os/RpcServer.h>

#include <TaskPlanning.h>

#include <iostream>

class TextTaskPlanningServer : public TaskPlanning
{
    bool stepTo(const double x, const double y, const double theta) override
    {
        std::cout << "stepTo called\n";
        return true;
    }

    bool grasp(const std::int32_t blockId) override
    {
        std::cout << "grasp called\n";
        return true;
    }

    bool place(const std::int32_t blockId, const std::int32_t objId) override
    {
        std::cout << "place called\n";
        return true;
    }
};

int main()
{
    yarp::os::Network yarp;
    TextTaskPlanningServer textTaskPlanningServer;
    yarp::os::RpcServer port;
    textTaskPlanningServer.yarp().attachAsServer(port);
    if (!port.open("/textTaskPlanningServer")) { return 1; }
    while (true) {
        printf("Server running happily\n");
        yarp::os::Time::delay(10);
    }
    port.close();
    return 0;
}
