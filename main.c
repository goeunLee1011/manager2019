#include "user.h"
#include "menu.h"

int load_file(LOGIN* list[], char* filename){
  int count=0;
  int anyway=0;
  FILE *datafile = fopen(filename, "r");
  if(datafile==NULL){
    printf("%s file not exist! make anyway?(Yes 1, No 2) >> ",filename);
    scanf("%d",&anyway);
    if(anyway==1){ 
	datafile = fopen(filename,"w"); 
	printf(">Welcome!!\n");
    }
    else return -1; 
}
  while(!feof(datafile)){
    list[count]=(LOGIN*)malloc(sizeof(LOGIN));
    fscanf(datafile,"%s %s",list[count]->id,list[count]->password);
    count++;
  }
  printf("%d records read!\n",count);\
  fclose(datafile);
  return count;
}

void join(LOGIN* list[], int count){
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
      break;
    }
  }
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
  if(dup!=1){
    printf("No such user!!\n");
    return -1;
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
  printf("Logout!!\n");
}

void save_file(LOGIN* list[], int count, char* filename){
  FILE *datafile = fopen(filename, "w");
  for(int i=0; i<count; i++){
    fprintf(datafile, "%s %s\n", list[i]->id, list[i]->password);
  }
  printf("%s Saved!\n", filename);
  fclose(datafile);
}


int ask_menu(int is_login){
// 파라미터 : 로그인여부 (0 No, 1Yes)
// 리턴값 : 선택한 메뉴번호
// 메뉴번호 : 1. Sign up 2. Log in 3. Log out 0. Exit
  char label;
  int menu;
  char input_order[20];
  if(is_login==0) label='>';
  else label='#';
  printf("%c",label);
  scanf("%s",&input_order);
//로그인이 안되어있는 상태인데 login을 input_order에 넣으면 login함수 실행
  if(login==0){
	if(!strcmp(input_order,"list")) menu=4; 
	else if(!strcmp(input_order,"login")) menu=2;
 	else if(!strcmp(input_order,"join")) menu=1;
	else if(!strcmp(input_order,"exit")) menu=0;
  }
  else{
	if(!strcmp(input_order,"logout")) menu=3;
  }
  return menu;
}



int main(int argc, char* argv[]) {
  LOGIN* userlist[100]; // 사용자목록 포인터 배열 (최대 100)
  int is_login=0; // 로그인 여부 (0 NO, 1 Yes)
  int menu_id;
  if (argc != 2) {
    printf("Usage : manager <datafile>\n");
    return 0;
  }
//일단 사용자가 입력한 파일을 열고... 프로그램을 시작함
  int count = load_file(userlist, argv[1]);
  if(count==-1) return 0; //해당 이름의 파일이 없는데 사용자가 더 만들지 않겠다 하면 그냥 종료
  while(1){
    if(is_login==0) is_login = login(userlist, count);
    menu_id = ask_menu(is_login); // 현재 로그인 되었는지의 여부를 파라미터로 알려야 한다.
    if(menu_id==1) join(userlist, count);
    else if (menu_id==2) is_login = login(userlist, count);
    else if (menu_id==3) logout(&is_login);
    else break;
  }
  save_file(userlist, count, argv[1]);
  return 0;
}
