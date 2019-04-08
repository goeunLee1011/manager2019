#include "user.h"

int load_file(LOGIN* list[], char* filename){
  int count=0;
  int anyway=0;
  FILE *datafile = fopen(filename, "rt");
  if(datafile==NULL){
    printf("%s file not exist! make anyway?(Yes 1, No 2) >> ",filename);
    scanf("%d",&anyway);
    if(anyway==1){ 
	datafile = fopen(filename,"wt"); 
	printf("> Welcome!!\n");
	count =0;
	list[0]=malloc(sizeof(LOGIN));
	return count;
    }
    else return -1; 
  }
  while(!feof(datafile)){
    list[count]=(LOGIN*)malloc(sizeof(LOGIN));
    fscanf(datafile,"%s %s",list[count]->id,list[count]->password);
    count++;
  }
  count--;
  printf("%d records read!\n",count);
  fclose(datafile);
  return count;
}

int join(LOGIN* list[], int count){
  char id[20], pass[20];
  while(1){
    printf("Enter new user id >> ");
    scanf("%s", id);
    int dup=0;
    for(int i=0;i<count;i++){
      if(strcmp(id, list[i]->id)==0) {
        dup=1; break;
      }
    }
    if(dup==1){
      printf("Already exist!!\n");
    }
    else{
      printf("Enter password >> ");
      scanf("%s", pass);
      list[count] = (LOGIN*)malloc(sizeof(LOGIN));
      strcpy(list[count]->id, id);
      strcpy(list[count]->password, pass);
      printf("New user added!\n");
      count++;
      break;
    }
  }
  return count;
}

int login(LOGIN* list[], int count){
  char id[20], pass[20];
  printf("Enter user id >> ");
  scanf("%s", id);
  int dup=0, found;
  for(int i=0;i<count;i++){
    if(strcmp(id, list[i]->id)==0) {
      dup=1;
      found = i;
      break;
    }
  }
//만약 id 못찾으면
  if(dup!=1){
    printf("No such user!!\n");
    return 0;
  }
  else{
    printf("Enter password >> ");
    scanf("%s", pass);
    if(strcmp(list[found]->password, pass)==0){
      printf("Welcome %s!!\n", id);
      return 1;
    }
    else{
      printf("Password incorrect!!\n");
      return 0;
    }
  }
}

void logout(int* is_login){
  *is_login = 0;
  printf("Bye!!\n");
}

void save_file(LOGIN* list[], int count, char* filename){
  FILE *datafile = fopen(filename, "w");
  for(int i=0; i<count; i++){
    fprintf(datafile, "%s %s\n", list[i]->id, list[i]->password);
  }
  printf("%s Saved!\n", filename);
  fclose(datafile);
}
void list(LOGIN* userlist[],int count){
  printf("User list (id/password)\n");
  if(count>0)
  	for(int i=0;i<count;i++)
		printf("[%d] %s / %s\n",i+1,userlist[i]->id,userlist[i]->password);
}
