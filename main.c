#include "user.h"
#include "menu.h"
int main(int argc, char* argv[]) {
  LOGIN* userlist[100]; // 사용자목록 포인터 배열 (최대 100)
  int is_login=0; // 로그인 여부 (0 NO, 1 Yes)
  int menu_id=-999;
  if (argc != 2) {
    printf("Usage : manager <datafile>\n");
    return 0;
  }
  int count = load_file(userlist, argv[1]);
  if(count==-1) return 0; //해당 이름의 파일이 없는데 사용자가 더 만들지 않겠다 하면 그냥 종료
  
  while(1){
    menu_id = ask_menu(is_login); // 현재 로그인 되었는지의 여부를 파라미터로 알려야 한다.
    if(menu_id==1) count=join(userlist, count);
    else if (menu_id==2) is_login = login(userlist, count);
    else if (menu_id==3) logout(&is_login);
    else if (menu_id==4) list(userlist,count);
    else if (menu_id==-999) ;
    else break;
  }
  save_file(userlist, count, argv[1]);
  return 0;
}

