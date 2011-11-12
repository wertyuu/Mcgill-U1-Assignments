#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<string.h>

void producer(FILE *p){
  int i;

  //while not at end of file
  while(!feof(p)){
    char temp[100];
    temp[0]=' ';
    fgets(temp, 99, p);
    
    //the last line is measured twice. this makes sure it happens once
    if(temp[0]==' ')
	break;

    int val=atoi(temp);

    while(1){
      //entering infinite loop
      FILE *q=fopen("values.txt", "rt"); 
    
      if(q==NULL){ //if values.txt does not exist

	if(val<=0)
		break; //if we have a negative value, we go to next value
	
	FILE *q=fopen("values_temp.txt", "wt");
	
	if(val>0){ //if our value is positive
	  for(i=val;i>=0;i--){
	    fprintf(q, "%d", i);
	    fputc(' ', q);
	    }
	}
	fclose(q);
	//Because we want the file to appear instantly (not as we write along), we use values_temp.txt
	system("mv values_temp.txt values.txt"); //we then rename it
        break; //go to next value of data.txt
      }
    }
  }
  fclose(p);
  FILE *done=fopen("DONE.txt", "wt"); 
  //a temp file so consumer knows when producer is done
  fputc('a', done); 
  fclose(done);
}

void consumer(){
  int count=0;
  while(1){
    //wait for values.txt to appear
    FILE *read_values=fopen("values.txt", "rt");
    if(read_values!=NULL){
      count++;
      char temp[100];
      fgets(temp, 99, read_values);
      printf("\nProcessing VALUES.TXT file number %d with values %s \n", count, temp);
      printf("It has %d odd numbers \n", count_odds(temp));
      fclose(read_values);
      system("rm values.txt");
    }
   //check if producer is done.
   //if so, we finish consumer
   FILE *check=fopen("DONE.txt", "rt");
   if(check!=NULL){
     fclose(check);
     system("rm DONE.txt");
     break;}
  }
}

//function to count number of odds in a string
int count_odds(char temp[]){
  int count=0;

  char *token=strtok(temp, " ");
  int num=atoi(token);

  while(num!=0){//when we hit 0, we know we are done
	if(num%2!=0)
		count++;
	token=strtok(NULL, " ");
	num=atoi(token);
  }
  return count;
}

int main(){

  while(1){
    //While enter an infinite loop
    //open the file data.txt to read

    FILE *p=fopen("data.txt", "rt");

    if(p!=NULL){ //if it is present, we do things
     // printf("We found data.txt \n");
      int pid=fork();
	
      if(pid==0){
	producer(p); //the parent does the producer things
      }else if (pid<0){
	printf("Unable to fork properly. \n"); break;
      }
      else{
	consumer(); //child does the consumer things
      }
    break;
    }
    
  }
//printf("We have finished \n");
//system("rm -f data.txt");
return 0;
}
