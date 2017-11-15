import sys            #for reading arguments from input
import math
import common_func   #for using common functions like findavg,sorting,getting input list etc.


def run_sjf(input_list):

    n = len(input_list)  			#store length of i/p list	
    common_func.sort_priority(input_list)	#sort according to priority
    findavgtime(input_list, n)			
	

def findwaitingtime(input_list, n):			
    complete = 0    # total number of processes completed
    t = 0   # current time
    shortest = 0    # index of object  having minimum remaining time
    finish_time = 0 # completion time
    check = False   # false if no process currently being executed

    while complete != n:                           #while list is not iterated move along list
        # minimun remaining time from input list
        minm = float('inf') # initialize minm with infinite
        for j in xrange(0, n):
            if input_list[j].arrival_time <= t and input_list[j].total_remaining_time < minm and input_list[j].total_remaining_time > 0: #check arrival time< total time and time remaining is < max value
                minm = input_list[j].total_remaining_time								
                shortest = j														#find shortest time 
                check = True
        # if no process is found means no process is currently executing then check is False
        if minm == float('inf'):
            check = False
        if check is False:														
            t = t+1
            continue
        input_list[shortest].total_remaining_time = input_list[shortest].total_remaining_time - 1												#decrease time for shortest process by 1
        if input_list[shortest].total_remaining_time > 0 and input_list[shortest].total_remaining_time < 1:
            t += input_list[shortest].total_remaining_time										#if remaining time is is between 0 to 1,add to total time
            input_list[shortest].total_remaining_time = 0										#then make it 0
        if input_list[shortest].total_remaining_time == 0:
            complete += 1														#if shortest process is executed increase complete processes by 1
            finish_time = t + 1
            input_list[shortest].completion_time = finish_time
            input_list[shortest].waiting_time = finish_time - input_list[shortest].total_exec_time - input_list[shortest].arrival_time #wt=ft-total_time-at
            input_list[shortest].turn_around_time = input_list[shortest].total_exec_time + input_list[shortest].waiting_time		#tat=exec_time-wt

        t = t + 1															


def findavgtime(input_list, n):	
    findwaitingtime(input_list, n)                                									#call to find avg waiting time
    print "Processes \t\t" + "Burst time\t\t" +"Waiting Time\t\t" + "Turn around time "
    for i in range(n):
        print input_list[i].name, "\t\t\t", input_list[i].total_exec_time, "\t\t\t", input_list[i].waiting_time, "\t\t\t", input_list[i].turn_around_time		#iterate through list and print attributes
    print "Average waiting time = ", common_func.get_avg([i.waiting_time for i in input_list])										#add waiting time of processes and average them
    print "Average turn around time = ", common_func.get_avg([i.turn_around_time for i in input_list])									#add turn around time of processes and average them
    print "Average Completion time = ", common_func.get_avg([i.completion_time for i in input_list])									#add completion time of processes and average them
