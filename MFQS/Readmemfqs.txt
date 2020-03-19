I have tried to implement Multilevel Feedback Queue Scheduling in C.
The program uses a file named mfqs.txt for the inputs. 

About the Program:
1.It uses three queues q1,q2 and q3 with decreasing priority.
2.Each of the queue has a fixed quantum time. 
3.If a process is in queue q1 and it doesnot gets terminated within the quantum time
  of q1 then the process will be demoted to the lower queue q2.
4.Similarly the queue q2 is implemented.
5.The maximum number of processes allowed in my program is 100
6.To save the processes in q3 from starvation after every 50 sec all the processes will
  be moved to q1.
7.I have not considered any I/O requirements or any Interupts or timeout.
