import sys
import math


class process(object):

    def __init__(self, name, l):
        self.name = name
        self.arrival_time = l[0]
        self.total_exec_time = l[1]
        self.total_waiting_time = l[2] + l[3]
        self.priority = l[4]


def get_input_list(file_name):
    try:
        file = open(file_name, 'r')
        input_list = []
        for line in file:
            list_line = line.split(' ')
            new_process = process(list_line[0], map(float, list_line[1:]))
            input_list.append(new_process)
    except IOError as e:
        sys.exit(e)
    except ValueError as e:
        sys.exit(e)
    except IndexError as e:
        sys.exit('Incorrect input file')
    return input_list


def get_avg(l):
    return float(sum(l))/ len(l)


def get_std_dev(l):
    avg = get_avg(l)
    std_dev = math.sqrt(sum([(i - avg) ** 2 for i in l]) / (len(l) - 1))
    return std_dev


def sort_arrival_time(inp):
    quick_sort(inp, 0, len(inp) - 1)


def median(a, i, j, k):
    """
    Return median of 3 integers from array a.
    :param a: Iterable of elements
    :param i: start element index
    :param j: end element index
    :param k: middle element index
    :return: return median of values at indices i, j and k.
    """
    ai, aj, ak = a[i], a[j], a[k]
    med_val = ai.arrival_time + aj.arrival_time + ak.arrival_time - \
        max(ai.arrival_time, aj.arrival_time, ak.arrival_time) - \
        min(ai.arrival_time, aj.arrival_time, ak.arrival_time)
    if ai.arrival_time == med_val:
        return i
    elif aj.arrival_time == med_val:
        return j
    return k


def partition(array, l, r):
    """
    Perform Partition Operation on array.
    Time Complexity: Theta(nLogn)
    Auxiliary Space: O(n)
    :param array: Iterable of elements
    :param l: pivot value for array
    :param r: right limit of array
    :return: return q value for function, used in partitioning of array.
    """
    i = l - 1
    pivot_index = median(array, l, r, (l+r) // 2)
    array[pivot_index], array[r] = array[r], array[pivot_index]
    pivot = array[r].arrival_time
    for j in range(l, r):
        if array[j].arrival_time <= pivot:
            i += 1
            array[i], array[j] = array[j], array[i]
    i += 1
    array[r], array[i] = array[i], array[r]
    return i


def quick_sort(array, left, right):
    """
    Perform sort using partition function.
    Time Complexity : O(nlog(n)).
    Space Complexity : O(n).
    :param array: Iterable of elements
    :param left: used as left limit of quick sort4
    :param right: right limit for quick sort
    :return: no returns, sorts array
    """
    if left < right:
        q = partition(array, left, right)
        quick_sort(array, left, q - 1)
        quick_sort(array, q + 1, right)
