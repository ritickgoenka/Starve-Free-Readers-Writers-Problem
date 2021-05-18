# Starve-Free-Readers-Writers-Problem Solution by Ritick Goenka(1711058)

Problem Statement

There are multiple readers and writers of a particular variable , several readers can read the value of the variable but only a single writer is a present updating the value at a time and no readers can be present when the writer is updating the value, the solution should also avoid the starvation of reader and writers. An example is also run at the end of the this readme

Semaphores
When there exists a requirement of mutual exculsion because of the presence of critical section, a semaphore can be used. It can help us to mantain mutual exclusion by using wait and signal mechanism, in this program we will use 3 binary semaphore.

"cnt_sem" is a semaphore to ensure mutual exclusion when reader_cnt value is updated by different readers
"in" represents that the library is not empty that is someone is inside it is also used to prevent stravation of writers and give equal priority to both readers and writers
"reader_Writer_Sem" this semaphore ensures that no writer can enter when any reader or writer is already reading/updating the value

Other variables

reader_cnt - to maintain the readers currently reading the variable, mutual exclusion of this variable is ensured by cnt_sem
reader_writer_variable- this is the shared variable between reader and writer its value is increased by 10 (just as an example) when the writer updates it


Sample Sequence of Readers and writers
Reader-0 entered 
Reader-1 entered 
Reader-2 entered 
writer-0 entered 
Reader-3 entered 
writer-1 entered 
Reader-4 entered 
Reader-5 entered 
writer-2 entered 
Reader-6 entered 
Reader-7 entered 
writer-3 entered 
Reader-8 entered 
writer-4 entered 
Reader-9 entered 


Sample Output


Reader-0 entered and reader count updated 
Reader-1 entered and reader count updated 
Reader-1 is reading shared variable : 1
Reader-1 exited and reader count updated 
Reader-2 entered and reader count updated 
writer-0 entered 
Reader-0 is reading shared variable : 1
Reader-0 exited and reader count updated 
Reader-2 is reading shared variable : 1
Reader-2 exited and reader count updated 
writer-0 is writing shared value: 11 
writer-0 exited 
Reader-3 entered and reader count updated 
writer-1 entered 
Reader-3 is reading shared variable : 31
Reader-3 exited and reader count updated 
writer-1 is writing shared value: 21 
writer-1 exited 
Reader-4 entered and reader count updated 
Reader-4 is reading shared variable : 11
Reader-5 entered and reader count updated 
Reader-5 is reading shared variable : 41
writer-2 entered 
Reader-4 exited and reader count updated 
Reader-5 exited and reader count updated 
writer-2 is writing shared value: 31 
writer-2 exited 
Reader-6 entered and reader count updated 
Reader-6 is reading shared variable : 21
Reader-7 entered and reader count updated 
Reader-6 exited and reader count updated 
Reader-7 is reading shared variable : 1
writer-3 entered 
Reader-7 exited and reader count updated 
writer-3 is writing shared value: 41 
writer-3 exited
Reader-8 entered and reader count updated 
writer-4 entered 
Reader-8 is reading shared variable : 51
Reader-8 exited and reader count updated 
writer-4 is writing shared value: 21 
writer-4 exited 
Reader-9 entered and reader count updated 
Reader-9 is reading shared variable : 51
Reader-9 exited and reader count updated 


From the output we can see that the neither writer nor the reader is getting any priority and hence the code is stravation free
