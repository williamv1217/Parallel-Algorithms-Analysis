CC = g++
CFLAGS = -O2 -I../c++ -mcx16 -march=native -DCILK -fcilkplus -std=c++11

all:	reduce scan qsort scan_sequential reduce_seq reduce_thresh scan_opt mmul

reduce:	reduce.cpp
	$(CC) $(CFLAGS) -DNDEBUG reduce.cpp -o reduce
	
scan:	scan.cpp scan.h
	$(CC) $(CFLAGS) -DNDEBUG scan.cpp -o scan

qsort:	quicksort.cpp qsort.h
	$(CC) $(CFLAGS) -DNDEBUG quicksort.cpp -o qsort

scan_sequential: scan_sequential.cpp scan_sequential.h
	$(CC) $(CFLAGS) -DNDEBUG scan_sequential.cpp -o scan_sequential
	
reduce_seq: reduce_seq.cpp
	$(CC) $(CFLAGS) -DNDEBUG reduce_seq.cpp -o reduce_seq

reduce_thresh: reduce_thresh.cpp
	$(CC) $(CFLAGS) -DNDEBUG reduce_thresh.cpp -o reduce_thresh

scan_opt: scan_opt.cpp scan_opt.h
	$(CC) $(CFLAGS) -DNDEBUG scan_opt.cpp -o scan_opt

mmul:	mmul.cpp
	$(CC) $(CFLAGS)	-DNDEBUG mmul.cpp -o mmul

clean:
	rm -f reduce scan qsort scan_sequential reduce_seq reduce_thresh scan_opt mmul
