import sys
import common_func
import round_robin as rr
import fcfs
import sjf

#in main we have imported all the other scheduling processes i.e we have imported round robin, fcfs and rr
#now in main we will be doing error handling i.e if the try block does not run ,then exception such as INDEX ERROR, VALUE ERROR
#arises
def main():
  #now sys.argv represents the array of arguments taken in the input and similarly we will take count as 2nd argument and file name
  #fourth argument
    try:
        file_name = sys.argv[3]
        count = int(sys.argv[1])
        
        if count < 0 or count > 1:
            raise ValueError("Invalid Integer, Please write either 0 or 1")
        #now we will call get_input_list function from the common_func module to create the list of objects
        
        input_list = common_func.get_input_list(file_name, count)
        #now third argument is taken as algo_option which u want to choose
        algo_option = sys.argv[2]
        if algo_option == 'rr':
            rr.run_robin(input_list, 3, True)
            rr.plot_rr(input_list)
        elif algo_option == 'fcfs':
            fcfs.run_fcfs(input_list)
        elif algo_option == 'sjf':
            sjf.run_sjf(input_list)   
        else:
            sys.exit('Wrong input\nyou can use rr , fcfs and sjf. Please try again')
          
    except IndexError as e:
        sys.exit(
           'Please follow this format: python main.py <count> <Name of scheduling algo> <File Name>')
    except ValueError as e:
        sys.exit(e)


if __name__ == '__main__':
    main()
