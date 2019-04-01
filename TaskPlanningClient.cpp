#include <yarp/os/Network.h>
#include <yarp/os/RpcClient.h>

#include <TaskPlanning.h>

#include <iostream>


int main(int argc, char *argv[])
{
    yarp::os::Network yarp;
    yarp::os::RpcClient client_port;

    client_port.open("/taskPlanningClient");
    if (!yarp.connect(client_port.getName(), "/textTaskPlanningServer"))
    {
        std::cout << "Error! Could not connect to server /textTaskPlanningServer\n";
        return 1;
    }

    TaskPlanning taskPlanning;
    taskPlanning.yarp().attachAsClient(client_port);
// ---------------------

    bool ret = taskPlanning.stepTo(3.4, 5.3, 2.1);

// ---------------------

    return 0;
}
