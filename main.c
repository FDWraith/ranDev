#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int rndInt(int rnd);

int main(){
  
  int rndSeed = open("/dev/urandom", O_RDONLY);
  /*
  printf("Testing rndInt\n");
  int p = rndInt(rndSeed);
  printf("RandomInteger:[%d]\n",p);
  int q[2];
  q[0] = rndInt(rndSeed);
  q[1] = rndInt(rndSeed);
  printf("RandomArray:[%p]\n",q);
  printf("First Element:[%d]\n",q[0]);
  printf("Second Element:[%d]\n",q[1]);
  */
  //printf("something happened\n");
  
  //srand(time(NULL));
  int ary[10];
  printf("Generating Random Numbers:\n");
  int i =0;
  //rndInt(ary);
  for(;i<10;i++){
    //ary[i]= rand();
    ary[i] = rndInt(rndSeed);
    printf("\tRandom %d: %d\n",i,ary[i]);
  }
  
  printf("Creating file.txt\n");
  //umask(0);
  int fd = open("file.txt", O_CREAT | O_WRONLY, 0666);
  printf("File Descriptor:[%d]\n",fd);
  if( fd < 0){
    printf("Error found while attempting to create file\n");
  }
  if( fd < 0){
    printf("Error found while attempting to open file\n");
  }
  printf("Writing into file\n");
  //printf("File Descriptor:[%d]\n",fd);
  //printf("Array Pointer:[%p]\n",ary);
  //printf("Array First Element:[%d]\n",ary[0]);
  //printf("Array Last Element[%d]\n", ary[9]);
  //printf("Size of Array:[%lu]\n",sizeof(ary));
  int err = write(fd,ary,sizeof(ary));
  //printf("Segmentation fault (core dumped)\n");
  //printf("Error\n");
  if( err < 0){
    printf("Error found: %s\n",strerror(errno));
  }
  err = 0;
  close(fd);
  printf("Reading file into new array\n");
  int ary2[10];
  fd = open("file.txt", O_RDWR);
  err = read(fd,ary2,sizeof(ary2));
  if(err < 0){
    printf("Error found: %s\n",strerror(errno));
  }
  printf("Verification of Array:\n");
  for( i =0; i< 10; i++){
    printf("\tRandom %d: %d\n",i,ary2[i]);
  }
  close(fd);
  return 0;
}

int rndInt(int fd){
  //
  if(fd < 0){
    printf("Invalid file descriptor\n");
    return -1;
  }else{
    int * p = malloc(sizeof(int));
    int err = read(fd,p,4);
    if( err < 0){
      printf("Error while getting random integers\n");
    }
    //close(fd);
    return *p;
  }
}
