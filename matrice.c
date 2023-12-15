//section include..



//define
#define N ... // places dans le buffer

//variable globales 
//les matrices
B,C,A
//le tampon
T

//pour la synchronisation 
pthread_mutex_t mutex;
sem_t empty;
sem_t full;

// Producteur
void producer(void)
{
  int item;
//pour chaque ligne 
//for....
  {
    item=produce(item);
    sem_wait(&empty); // attente d'une place libre
    pthread_mutex_lock(&mutex);
     // section critique
     insert_item();
    pthread_mutex_unlock(&mutex);
    sem_post(&full); // il y a une place remplie en plus
  }
}

void consumer(void)
{
 int item;
 while(true)
 {
   sem_wait(&full); // attente d'une place remplie
   pthread_mutex_lock(&mutex);
    // section critique
    item=remove(item);
   pthread_mutex_unlock(&mutex);
   sem_post(&empty); // il y a une place libre en plus
 }
}

int Main ()
{
// Initialisation
sem_init(&mutex,0,1);//exclusion mutuelle 
sem_init(&empty, 0 , N);  // buffer vide
sem_init(&full, 0 , 0);   // buffer vide
//creation des threads



//attente des threads




//destruction...



return 0;
}
