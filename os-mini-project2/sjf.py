import sys
import math
import common_func


def run_sjf(input_list):

    n = len(input_list)
    common_func.sort_priority(input_list)
    findavgtime(input_list, n)


def findwaitingtime(input_list, n):
    complete = 0
    t = 0
    minm = 1000000000
    shortest = 0
    finish_time = 0
    check = False

    while complete != n:
        for j in xrange(0, n):
            if input_list[j].arrival_time <= t and input_list[j].total_remaining_time < minm and input_list[j].total_remaining_time > 0:
                minm = input_list[j].total_remaining_time
                shortest = j
                check = True
        if check is False:
            t = t+1
            continue
        input_list[shortest].total_remaining_time = input_list[
            shortest].total_remaining_time - 1
        if input_list[shortest].total_remaining_time > 0 and input_list[shortest].total_remaining_time <= 1:
            t += input_list[shortest].total_remaining_time
            input_list[shortest].total_remaining_time = 0
        minm = input_list[shortest].total_remaining_time
        if minm == 0:
            minm = 1000000000
        if input_list[shortest].total_remaining_time == 0:
            complete += 1
            finish_time = t + 1
            input_list[shortest].completion_time = finish_time
            input_list[shortest].waiting_time = finish_time - input_list[shortest].total_exec_time - input_list[shortest].arrival_time
            input_list[shortest].turn_around_time = input_list[shortest].total_exec_time + input_list[shortest].waiting_time

        t = t + 1


def findavgtime(input_list, n):
    findwaitingtime(input_list, n)
    print "Processes \t\t" + "Burst time\t\t" +"Waiting Time\t\t" + "Turn around time "
    for i in range(n):
        print input_list[i].name, "\t\t\t", input_list[i].total_exec_time, "\t\t\t", input_list[i].waiting_time, "\t\t\t", input_list[i].turn_around_time
    print "Average waiting time = ", common_func.get_avg([i.waiting_time for i in input_list])
    print "Average turn around time = ", common_func.get_avg([i.turn_around_time for i in input_list])
    print "Average Completion time = ", common_func.get_avg([i.completion_time for i in input_list])
