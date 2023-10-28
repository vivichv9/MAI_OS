import random

N = 800

with open("/home/kirill/Desktop/study/MAI_OS/lab_2/files/input.txt", "w") as f:
    for i in range(N):
        f.write(str(random.randint(1, 2**30)) + " " + str(random.randint(1, 2**30)) + " " + str(random.randint(1, 2**30)) + "\n")