# AliTraceSimulator

AliTrace Simulator is a simulator that could simulate events of tasks or severs in
the Aliyun's cluster using the 24 hours' trace data, ClusterData201708 （https://goo.gl/forms/eOoe6DwZQpd2H5n53）.
The events contain
the addition, deletions or failures of batch instance or servers.
Now it could successfully output the number of batch tasks in the cluster at a specified time. Plus, it could record the changes of 
the number of tasks and used CPU or memory of each machine at a specified time, which is as real as described in the trace data.
### The class diagram of AliTraceSimualtor is as following:

![这里写图片描述](http://7xtc7i.com1.z0.glb.clouddn.com/Snip20171227_2.png)

![这里写图片描述](http://7xtc7i.com1.z0.glb.clouddn.com/Snip20171227_6.png)


--trace_path=/home/lilelr/trace_201710/ \
--log_dir=/home/lilelr/trace_201710/log