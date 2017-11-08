import sys

def get_input_list(file_name):
	try:
		file = open(file_name, 'r')
		input_list = [] 
		for line in file:
			l = map(float, line.split(' '))
			if len(l) != 6:
				raise IOError("Incorrect input line")
			input_list.append(l)
	except IOError as e:
		sys.exit(e)
	except ValueError as e:
		sys.exit(e)
	return input_list

def get_avg(l):
	return sum(l)/len(l)

def get_standard_dev(l):
	avg = get_avg(l)
	std_dev = sum([(i - avg) ** 2 for i in l ]) / (len(l) -1)
	return std_dev