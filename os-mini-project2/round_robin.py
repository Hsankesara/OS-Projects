import common_func
import matplotlib.pyplot as plt


def run_robin(inp_list, q, wanna_print):
    """
    Here implemented round robin algo which is scheduling algorithm
    It is one of the most commonly used technique in CPU scheduling as a core.
    It is preemptive as processes are assigned CPU only for a fixed slice of time at most.
    Algo:-  we are gonna iterate through list of objects and push all the objects in ready queue
            whose arrival time is less then current time. Then we pop out a process and run it for
            time q(quantum) units. if total remaining time of that process is less than q units than we completed that process else
            we deduct q units of time from its total remaining time and pushed it back to ready queue.We repeat the above
            process untill all the processes are executed.
    :param inp_list: List of process objects
    :param  q : quantum of given process
    :param  q : do you wanna print?
    """
    ready_queue = []    # ready queue which store process
    curr_time = 0       # current time
    i = -1
    n = len(inp_list)
    all_arrived = False
    while all_arrived is False or ready_queue != []:    # while all the processes are not arrived or ready queue is non-empty 
        while i <= n-2 and inp_list[i + 1].arrival_time < curr_time + q:    # while i  < n-2 as we are using i + 1 and arrival time of (i+1)th process is less than current time
            ready_queue.insert(0, inp_list[i + 1])  # adding process to queue
            i += 1
            if i == n - 1:
                all_arrived = True  # if i is equal to n-1 then alll process are arrived

        process = ready_queue.pop() # popping a process
        if process.total_remaining_time <= q:   # if remaining time of the proces is less than q then execute the whole process  
            curr_time += process.total_remaining_time
            process.total_remaining_time = 0
            process.completion_time = curr_time # calculating completion time
            process.turn_around_time = process.completion_time - process.arrival_time # calculating turn around time : TAT = Commpletion time - arrival time
            process.waiting_time = process.turn_around_time - process.arrival_time  # calculating total  waiting time : waiting time = turn around time - arrival time
        else:   # else deduct q from total remaining time of the process
            curr_time += q
            process.total_remaining_time -= q
            ready_queue.insert(0, process) # then push it again

    turn_around_time = [i.turn_around_time for i in inp_list]       # list of turn around time of every process
    avg_turn_around_time = common_func.get_avg(turn_around_time)    # calculating average turn around time 
    waiting_time = [i.waiting_time for i in inp_list]               # list of waiting time of every process
    avg_waiting_around_time = common_func.get_avg(waiting_time)     # calculating avg waiting time
    # printing everything
    if wanna_print is True:
        print 'process Name\tTurn Around Time\tWaiting Time'
        for i in inp_list:
            print i.name, '\t\t', i.turn_around_time, '\t\t\t', i.waiting_time
        print 'Average Waiting Time', avg_waiting_around_time
        print 'Average Turn Around Time', avg_turn_around_time
    restore_data(inp_list) # restore all data as we also have to plot graph
    return avg_waiting_around_time, avg_turn_around_time


def plot_rr(input_list):
    """
    To plot Waiting Time vs quantum and turn around time vs quantum
    :param input_list: list of objects
    """
    q = [i for i in xrange(1, 11)] # q = [1,10]
    waiting_time, turn_around_time = zip(*[run_robin(list(input_list), i, False) for i in q]) # returns tuple of waiting list and turn around time
    waiting_time = list(waiting_time) # convert tuple to list
    turn_around_time = list(turn_around_time) # convert tuple to list
    # Plotting session
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
    """
    To restore essential data
    """
    for i in input_list:
        i.total_remaining_time = i.total_exec_time
        i.turn_around_time = None
        i.waiting_time = None
