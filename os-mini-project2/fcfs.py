import sys
import math
import common_func


def run_fcfs(input_list1, write):

    sum = 0
    flag = 0
    n = len(input_list1)

    for j in range(0, n):
        flag = flag+input_list1[j].total_exec_time
        input_list1[j].completion_time = flag

    for j in range(0, n):
        input_list1[j].turn_around_time = input_list1[
            j].completion_time-input_list1[j].arrival_time
        input_list1[j].waiting_time = input_list1[
            j].turn_around_time-input_list1[j].total_exec_time

    avg_waiting_time = common_func.get_avg([i.waiting_time for i in input_list1])
    avg_turn_around_time = common_func.get_avg([i.turn_around_time for i in input_list1])
    avg_completion_time = common_func.get_avg([i.completion_time for i in input_list1])
    if write is True:
        print 'process Name\tTurn Around Time\tWaiting Time'
        for i in range(0, n):
            print input_list1[i].name, '\t\t', input_list1[i].turn_around_time, '\t\t\t', input_list1[i].waiting_time

    print 'The Average Waiting Time is:', avg_waiting_time
    print 'Average Turn Around Time is:', avg_turn_around_time
    print 'Average completion Time is:', avg_completion_time
    return avg_waiting_time, avg_turn_around_time, avg_completion_time
