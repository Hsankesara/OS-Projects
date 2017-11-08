import sys
import common_func


def main():
    try:
        file_name = sys.argv[2]
        input_list = common_func.get_input_list(file_name)
        common_func.sort_arrival_time(input_list)
        algo_option = sys.argv[1]
        if algo_option == 'rr':
            # Use Round Robin
            print 'rr'
        elif algo_option == 'fcfs':
            # Use FCFS
            print 'fcfs'
        elif algo_option == 'sjf':
            # Use SJF
            print 'sjf'
        else:
            sys.exit('Wrong input\nyou can use rr , fcfs and sjf. Please try again')
    except IndexError as e:
        sys.exit(
            'Please follow the format: python main.py <Name of scheduling algo> <File Name>')


if __name__ == '__main__':
    main()
