import sys
import math
import common_func

#In fcfs ,it will be based on first come first serve .the process which comes first will be executed first without preemption 
#and then another process will be executed . so first we have calculated the completion time of each process by summing the previous total execution time and respectively waiting time and turn around time are calculated.
#function is defined
def run_fcfs(input_list1):

    sum = 0
    # initialize flag with arrival time of first process
    flag = input_list1[0].arrival_time
    #lenght is taken
    n = len(input_list1)
  #loop is run to calculate Sthe completion time by incrementing the flag by previous total execution time
    for j in range(0, n):
        # if arrival time of next process is greater than flag(current time) than we increase flag 
        if flag < input_list1[j].arrival_time:
            # shifts code to next arrival time
            flag = input_list1[j].arrival_time
        flag = flag + input_list1[j].total_exec_time
        input_list1[j].completion_time = flag
#here waiting time and turn around time are calculated by using the below formulae:
#turn_around_time=completion_time-arrival_time
#waiting_time=turn_around_time-total_exec_time
    for j in range(0, n):
        input_list1[j].turn_around_time = input_list1[j].completion_time - input_list1[j].arrival_time
        input_list1[j].waiting_time = input_list1[j].turn_around_time - input_list1[j].total_exec_time
#here we have find the average of each of time calculated by calling the get_avg from the common_func module and then passing
#the values fo each of the following time in the for loop
    waiting_time = [i.waiting_time for i in input_list1]
    turn_around_time = [i.turn_around_time for i in input_list1]
    avg_waiting_time = common_func.get_avg(waiting_time)
    avg_turn_around_time = common_func.get_avg(turn_around_time)
    avg_completion_time = common_func.get_avg([i.completion_time for i in input_list1])
 #here we print the whole output table i.e. process name ,then turn around time, followed by waiting time respectively
    print 'process Name\tTurn Around Time\tWaiting Time'
    for i in range(0, n):
        print input_list1[i].name, '\t\t', input_list1[i].turn_around_time, '\t\t\t', input_list1[i].waiting_time

    print 'Average Waiting Time is:', avg_waiting_time
    print 'Average Turn Around Time is:', avg_turn_around_time
    print 'Average completion Time is:', avg_completion_time
    print 'Standard Deviation of waiting time', common_func.get_std_dev(waiting_time)
    print 'Standard Deviation of turn around time', common_func.get_std_dev(turn_around_time)