#include<semaphore.h>
#include<pthread.h>
# include<bits/stdc++.h>

using namespace std;

int read_write_variable = 1,reader_cnt = 0; //read write variable stores the value to read and written by readers and writers


void *reader(void *);
void *writer(void *);
pthread_t r[10],w[5]; 


sem_t in,cnt_sem,reader_writer_sem;  //cnt_sem is a semaphore to ensure mutual exclusion when reader_cnt value is updated by different readers
// in represents that the library is not empty that is someone is inside it is also used to prevent stravation of writers and give equal priority to both readers and writers
//reader_Writer_Sem this semaphore ensures that no writer can enter when any reader or writer is already reading/updating the value



//reader part of code, i th reader enter the queue
void *reader(void *i){
     // reader has entered the queue

    
    sem_wait(&in);  //reader has to wait if other reader is updating value of reader_cnt variable or some writer is writing or is infront of the reader in queue

    sem_wait(&cnt_sem); //semaphore to ensure only one reader can update value of reader_Cnt at a time, if other reader is updating then wait
    
    reader_cnt++;   // increase the reader count by 1
    printf("Reader-%d entered and reader count updated \n",i);

    if(reader_cnt==1) 
        sem_wait(&reader_writer_sem); //block any other writer from entering until all the reader who came before him have exited the library

    sem_post(&cnt_sem); //signal cnt_sem
    sem_post(&in);  //signal in


    // Critical section

    printf("Reader-%d is reading shared variable : %d\n",i,read_write_variable);
    


    // when the reader exits then update reader_cnt and check if reader_writer_sem needs to be signaled

    sem_wait(&cnt_sem); //check if reader_cnt can be updated
    reader_cnt--;
    if(reader_cnt==0)
        sem_post(&reader_writer_sem); //signal reader_writer_sem if all the readers have exited
    sem_post(&cnt_sem); //signal cnt_sem

}

void *writer(void *i){
     //enters the queue
    sem_wait(&in); //writer has to wait if other reader is updating value of reader_cnt variable or some writer is writing or is infront of the reader in queue
    
    printf("writer-%d entered \n",i);
    sem_wait(&reader_writer_sem); //wait if some reader is reading or some writer is writing
    

    // updated the shared variable value

    read_write_variable +=10;
     printf("writer-%d is writing shared value: %d \n",i,read_write_variable);
     /*
    --------------------
    EXIT SECTION
    --------------------
    */
     printf("writer-%d exited \n",i);
     sem_post(&reader_writer_sem); //singnal reader_writer_sem
     sem_post(&in);  //signak in
}
int main(){
    //intitialising values of all the semaphores
    sem_init(&in,0,1);
    sem_init(&reader_writer_sem,0,1);
    sem_init(&cnt_sem,0,1);



    //creating threads of various readers and writer
    pthread_create(&r[0],NULL,reader,(void *)0);
    pthread_create(&r[1],NULL,reader,(void *)1);
    pthread_create(&r[2],NULL,reader,(void *)2);
    pthread_create(&w[0],NULL,writer,(void *)0);
    pthread_create(&r[3],NULL,reader,(void *)3);
    pthread_create(&w[1],NULL,writer,(void *)1);
    pthread_create(&r[4],NULL,reader,(void *)4);
    pthread_create(&r[5],NULL,reader,(void *)5);
    pthread_create(&w[2],NULL,writer,(void *)2);
    pthread_create(&r[6],NULL,reader,(void *)6);
    pthread_create(&r[7],NULL,reader,(void *)7);
    pthread_create(&w[3],NULL,writer,(void *)3);
    pthread_create(&r[8],NULL,reader,(void *)8);
    pthread_create(&w[4],NULL,writer,(void *)4);
    pthread_create(&r[9],NULL,reader,(void *)9);
    
    
    pthread_join(r[0],NULL);
    pthread_join(r[1],NULL);
    pthread_join(r[2],NULL);
    pthread_join(w[0],NULL);
    pthread_join(r[3],NULL);
    pthread_join(w[1],NULL);
    pthread_join(r[4],NULL);
    pthread_join(r[5],NULL);
    pthread_join(w[2],NULL);
    pthread_join(r[6],NULL);
    pthread_join(r[7],NULL);
    pthread_join(w[3],NULL);
    pthread_join(r[8],NULL);
    pthread_join(w[4],NULL);
    pthread_join(r[9],NULL);
   
return 0;
}