import random

FILENAME = 'graph_big.txt'

NODE_COUNT = 20
BRANCH_COUNT = 40

arr = [(i % NODE_COUNT + 1, i // NODE_COUNT + 1, random.randint(-50, 50))  for i in range(0, NODE_COUNT ** 2)]

random.shuffle(arr)

with open(FILENAME, "w") as file:
    for i in range(BRANCH_COUNT):
        file.write("%d %d %d\n" % (arr[i][0], arr[i][1], arr[i][2]))
