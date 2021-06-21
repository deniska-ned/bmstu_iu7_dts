import random

FILENAME = "5_num.txt" 

NUM_COUNT = 5
MIN_VALUE = -1000
MAX_VALUE = 1000

with open(FILENAME, "w") as file:
    for i in range(NUM_COUNT):
        file.write(str(random.randint(MIN_VALUE, MAX_VALUE)) + "\n")
