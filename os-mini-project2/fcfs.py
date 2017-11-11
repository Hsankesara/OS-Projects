import sys
import math
import common_func


def run_fcfs(input_list1,write):
      
	    sum =0
	    flag=0
	   
		n=len(input_list1)

		for i in range(0,n):
	       input_list1[i].total_exec_time=input_list[i].total_exec_time+input_list[i].elapsed_time
	    
		for j in range(0,n):	
			input_list1[j].arrival_time
			
		for k in range(0,n):
			input_list1[k].name=k
	
			
		for j in range(0,n):
			flag=flag+input_list[j].total_exec_time
			input_list[j].completion_time=flag
			
		for j in range(0,n):
            input_list1[j].turn_around_time=input_list1[j].completion_time-input_list1[j].arrival_time
            input_list1[j].waiting_time=input_list[j].turn_around_time-input_list1[j].total_exec_time
            
        
        average_waiting_time=common_func.get_avg(waiting_time)
        average_turnaround_time=common_func.get_avg(turn_around_time)
        average_completion_time=common_func.get_avg(completion_time)
        
        if write is True:
			print 'process Name\tTurn Around Time\tWaiting Time'
			for i in range(o,n):
				print input_list1[i].name,'\t\t',input_list[i].turn_around_time,'\t\t',input_list[i].waiting_time
			
			
		print 'The Average Waiting Time is:', avg_waiting_time
        print 'Average Turn Around Time is:', avg_turn_around_time
        print 'Average completion Time is:', avg_completion_time
       
    	
			
	   return average_waitng_time,average_turnaround_time,average_completion_time
			
			
			
			
        
        
        
        
        
    
			
				    
	     
	     
	   
	       
	    
