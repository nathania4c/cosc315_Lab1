# cosc315_Lab1

##### Members: 
* Ethan Frigon
* Ryan Lam
* Siying Wu
* Nathania Hendradjaja

## Design Choices:
### For Sequential:
* The process id will be stored in 1 int variable since we will only require 1 pid at a time because only 1 process running at a time
* The child process will be the one executing the program using execvp() system call
* The parent will wait for the child using waitpid() system call
* The parent process will be suspended for the specified timeout period using sleep() system call 
* To execute the program count number of times only, parent will not execute (since child already did) 
* Parent will isntead be killed using kill() system call
### For Parallel: 
* The process ids will be stored in an array of pid_t (type for process ids) since multiple pids can be referenced because mutiple proccesses can be running at a time
* The child process will be executing the program
* To further show that multiple processes can run simultaneously, if no child process is currently executing, a string will be printed, and when (after or before a child process) this string is printed may vary
* The sleep() system call is implemented in order to suspend (delay) the next (killing) process by the specified timeout period
#### Note: The exit(0) is placed at the end of the while loop to exit and avoid running the closh again
