#!/usr/bin/python3

# Copyright

import yarp
import TaskPlanning

yarp.Network.init()

p = yarp.RpcClient()
p.open("/test")

yarp.Network.connect(p.getName(), "/textTaskPlanningServer")

tp = TaskPlanning.TaskPlanning()
tp.yarp().attachAsClient(p)

print(tp.help())
print(tp.help("stepTo"))
print(tp.help("grasp"))
print(tp.help("place"))
print(tp.help("help"))
tp.stepTo(1.0, 2.0, 3.0)
tp.grasp(1)
tp.place(2, 3)
