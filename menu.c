#include "menu.h"
int ask_menu(int is_login){
// 파라미터 : 로그인여부 (0 No, 1Yes)
// 리턴값 : 선택한 메뉴번호
// 메뉴번호 : 1. Sign up 2. Log in 3. Log out 0. Exit
  char label;
  int menu=-999;
  char input_order[20];
  if(is_login==0) label='>';
  else label='#';
  printf("%c ",label);
  scanf("%s",input_order);
//로그인이 안되어있는 상태인데 login을 input_order에 넣으면 login함수 실행
  if(is_login==0){
	if(strcmp(input_order,"list")==0) menu=4; 
	else if(strcmp(input_order,"login")==0) menu=2;
 	else if(strcmp(input_order,"join")==0) menu=1;
	else if(strcmp(input_order,"exit")==0) menu=0;
  }
  else{
	if(strcmp(input_order,"logout")==0) menu=3;
  }
  if(menu==-999){
	if(is_login==0) printf("No such command!\n");
	else		printf("%s\n",input_order);
  }
  return menu;
}

