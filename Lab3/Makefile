ALL: helloworld task2a task2b task3 task4 task5 serial_pi

helloworld: helloworld.c
	mpicc -o helloworld helloworld.c

task2a: task2a.c
	mpicc -o task2a task2a.c

task2b: task2b.c
	mpicc -o task2b task2b.c

task3: task3.c
	mpicc -o task3 task3.c

task4: task4.c
	mpicc -o task4 task4.c

task5: task5.c
	mpicc -o task5 task5.c -lm

serial_pi: serial_pi.c
	gcc -o serial_pi serial_pi.c -lm

clean:
	/bin/rm -f helloworld task2a task2b task3 task4 task5 serial_pi *.o
