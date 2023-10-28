import matplotlib.pyplot as plt
import csv

X = []
Y = []

with open('/home/kirill/Desktop/study/MAI_OS/lab_2/files/metrics.txt', 'r') as datafile:
    plotting = csv.reader(datafile, delimiter=' ')
    
    for ROWS in plotting:
        X.append(float(ROWS[1]))
        Y.append(float(ROWS[0]))

plt.plot(X, Y)
plt.title('Time of workers stat')
plt.xlabel('Count of workers')
plt.ylabel('Time,[ms]')
plt.grid()
plt.show()