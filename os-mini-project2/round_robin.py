import common_func
import matplotlib.pyplot as plt


def run_robin(inp_list, q, wanna_print):
    ready_queue = []
    curr_time = 0
    i = -1
    n = len(inp_list)
    all_arrived = False
    while all_arrived is False or ready_queue != []:
        while i <= n-2 and inp_list[i + 1].arrival_time < curr_time + q:
            ready_queue.insert(0, inp_list[i + 1])
            i += 1
            if i == n - 1:
                all_arrived = True

        process = ready_queue.pop()
        if process.total_remaining_time <= q:
            curr_time += process.total_remaining_time
            process.total_remaining_time = 0
            process.completion_time = curr_time
            process.turn_around_time = process.completion_time - process.arrival_time
            process.waiting_time = process.turn_around_time - process.arrival_time
        else:
            curr_time += q
            process.total_remaining_time -= q
            ready_queue.insert(0, process)

    turn_around_time = [i.turn_around_time for i in inp_list]
    avg_turn_around_time = common_func.get_avg(turn_around_time)
    waiting_time = [i.waiting_time for i in inp_list]
    avg_waiting_around_time = common_func.get_avg(waiting_time)
    if wanna_print is True:
        print 'process Name\tTurn Around Time\tWaiting Time'
        for i in inp_list:
            print i.name, '\t\t', i.turn_around_time, '\t\t\t', i.waiting_time
        print 'Average Waiting Time', avg_waiting_around_time
        print 'Average Turn Around Time', avg_turn_around_time
    restore_data(inp_list)
    return avg_waiting_around_time, avg_turn_around_time


def plot_rr(input_list):
    q = [i for i in xrange(1, 11)]
    waiting_time, turn_around_time = zip(
        *[run_robin(list(input_list), i, False) for i in q])
    waiting_time = list(waiting_time)
    turn_around_time = list(turn_around_time)
    plt.figure(figsize=(8, 6), dpi=80)
    plt.subplot(211)
    plt.plot(q, waiting_time, 'ro')
    plt.ylabel('Avg Waiting time')
    plt.xlabel('quantum')
    plt.subplot(212)
    plt.plot(q, turn_around_time, 'ro')
    plt.ylabel('Avg Turn Around time')
    plt.xlabel('quantum')
    plt.show()


def restore_data(input_list):
    for i in input_list:
        i.total_remaining_time = i.total_exec_time
        i.turn_around_time = None
        i.waiting_time = None
