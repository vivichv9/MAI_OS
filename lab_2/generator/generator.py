import random

N = 800

with open("/home/kirill/Desktop/study/MAI_OS/lab_2/files/input.txt", "w") as f:
    f.write(str(N) + "\n")
    for i in range(N):
        if i % 800 == 0:
            print(str(i / 1_000_000) + " millions")
        f.write(str(random.randint(1, 2**30)) + " " + str(random.randint(1, 2**30)) + " " + str(random.randint(1, 2**30)) + "\n")