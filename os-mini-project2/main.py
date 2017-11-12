import sys
import common_func
import round_robin as rr
import fcfs as fcfs



def main():
    try:
        file_name = sys.argv[3]
        input_list = common_func.get_input_list(file_name)
        algo_option = sys.argv[2]
        count = sys.argv[1]
        if algo_option == 'rr':
            rr.run_robin(input_list, 3, True, count)
            rr.plot_rr(input_list, count)
        elif algo_option == 'fcfs':
            fcfs.run_fcfs(input_list,True,count)
        elif algo_option == 'sjf':
            # Use SJF
            print 'sjf'
        else:
            sys.exit('Wrong input\nyou can use rr , fcfs and sjf. Please try again')
    except IndexError as e:
        sys.exit(
            'Please follow this format: python main.py <count> <Name of scheduling algo> <File Name>')


if __name__ == '__main__':
    main()
