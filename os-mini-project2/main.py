import sys
import common_func
import round_robin as rr
import fcfs



def main():
    try:
        file_name = sys.argv[3]
        count = int(sys.argv[1])
        if count  < 0 or count > 1:
            raise ValueError("Invalid Integer, Please write either 0 or 1")
        input_list = common_func.get_input_list(file_name, count)
        algo_option = sys.argv[2]
        if algo_option == 'rr':
            rr.run_robin(input_list, 3, True)
            rr.plot_rr(input_list)
        elif algo_option == 'fcfs':
            fcfs.run_fcfs(input_list,True)
        elif algo_option == 'sjf':
            # Use SJF
            print 'sjf'
        else:
            sys.exit('Wrong input\nyou can use rr , fcfs and sjf. Please try again')
    except IndexError as e:
        sys.exit(
            'Please follow this format: python main.py <count> <Name of scheduling algo> <File Name>')
    except ValueError as e:
        sys.exit(e)

if __name__ == '__main__':
    main()
