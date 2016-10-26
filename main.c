#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>

#include <errno.h>
#include <string.h>

void rndInt(int * loc);

int main(){
  srand(time(NULL));
  int ary[10];
  printf("Generating Random Numbers:\n");
  int i =0;
  rndInt(ary);
  for(;i<10;i++){
    //ary[i]= rand();
    printf("\tRandom %d: %d\n",i,ary[i]);
  }
  
  printf("Creating file.txt\n");
  int fd = open("file.txt", O_CREAT | O_EXCL | O_RDWR, 0644);
  printf("File Descriptor:[%d]\n",fd);
  if( fd < 0){
    printf("Error found while attempting to create file\n");
  }
  printf("Writing into file\n");
  int err = write( fd, ary, sizeof(ary));
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

void rndInt(int * loc){
  int fd = open("/dev/urandom", O_RDONLY);
  read(fd,loc,40);
}
