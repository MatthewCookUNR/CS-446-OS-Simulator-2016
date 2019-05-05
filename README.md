## Project Overview
The simulator was created throughout the semester in different stages. The program accepted both a configuration file and a meta-data file. The given files were used to simulate OS functions and process scheduling algorithms.
 
Sample configuration file (from final version):
```
Start Simulator Configuration File
Version/Phase: 3.0
File Path: Test_3.mdf
CPU Scheduling Code: RR
Quantum Time (cycles): 3
Processor cycle time (msec): 10
Monitor display time (msec): 20
Hard drive cycle time (msec): 15
Printer cycle time (msec): 25
Keyboard cycle time (msec): 50
Log: Log to Both
Log File Path: logfile_1.lgf
End Simulator Configuration File
 ```
 
 Sample meta-data file
 ```
 Start Program Meta-Data Code:
S(start)0; A(start)0; I(keyboard)5; O(hard drive)14; P(run)11;
P(run)11; I(hard drive)14; A(end)0; A(start)0; P(run)8; 
O(monitor)8; I(keyboard)7; P(run)13; O(hard drive)6; A(end)0; 
A(start)0; I(hard drive)5; P(run)5; O(hard drive)5; 
I(keyboard)15; O(hard drive)10; A(end)0; A(start)0; P(run)7; 
P(run)15; I(hard drive)14; O(monitor)5; P(run)13; A(end)0; 
A(start)0; I(keyboard)10; O(monitor)11; I(hard drive)10; 
O(monitor)13; I(hard drive)14; A(end)0; S(end)0.
End Program Meta-Data Code.
 ```
 * S: Operating System
 * A: Application / Process
 * P: Processor operation
 * I: Input operation
 * O: Output operation
 
### Features Implemented:
- Process control block
- Threading for I/O operations
- Mutex locks 
- Adding, scheduling, and running processes
- Memory caching
