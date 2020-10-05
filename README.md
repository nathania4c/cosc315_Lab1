# cosc315_Lab1

##### Members + Contributions: 
* Ethan Frigon --- figured out the logic for sequential and parallel and worked on the code
* Ryan Lam --- helped figure out the logic for sequential and parallel and worked on the code
* Siying Wu --- worked on the code
* Nathania Hendradjaja --- worked on the code, wrote the design document, created sample output file

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
* The sleep() system call is implemented in order to suspend (delay) the next (killing) process by the specified timeout period
#### Note: The exit(0) is placed at the end of the while loop to exit and avoid running the closh again
