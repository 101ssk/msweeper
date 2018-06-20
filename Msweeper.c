#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HIGHT 8 //縦
#define LENGTH 8 //横

#define TRUE 1
#define FALSE 0

#define CLEAR 100 //クリアの定数
#define NCLEAR 99 //未クリアの定数

#define BOMB -1 //ボムの定数

void game_start(void);
void game_clear(void);
void game_over(void);
void disp_length(void);
void disp_hight(int high);
void map_bomb_init(char map[][LENGTH], int bomb[][LENGTH]);
void shuffle_bomb(int bomb[][LENGTH]);
void bomb_around_num(int bomb[][LENGTH]);
void disp(char map[][LENGTH]);
int insert_num(int num);
int check_map(char map[][LENGTH],int count);
void open_map_info(int bomb[][LENGTH]);
void end_open(int bomb[][LENGTH],int clear_flag);
int count_bomb(int bomb[][LENGTH]);

int main(void)
{
  srand((unsigned)time(NULL));

  game_start();

  return 0;
}

void game_start(void)
{
  char map[HIGHT][LENGTH];
  int bomb[HIGHT][LENGTH],x,y,count=0,clear_flag=NCLEAR;

  map_bomb_init(map,bomb); //ボムと表示マップの初期化
  shuffle_bomb(bomb); //ボムの位置をシャッフル
  bomb_around_num(bomb); //ボムの周りに数字を代入
  count = count_bomb(bomb); //ボムの数をカウント

    while(TRUE) {
      printf("bomb:%d\n",count);
      printf("\n");
      disp(map); //画面表示
      while(TRUE){
        printf("Select x,y >0-7\n");
        scanf("%d %d", &x,&y);
        if(x >= 0 && x <= 7)
        if(y >= 0 && y <= 7) break;
      }
      if(bomb[y][x] == BOMB) break; //選択したマスがボムだったら終了
      else {
        map[y][x] = insert_num(bomb[y][x]); //マップに数字を代入
        clear_flag = check_map(map,count); //残りのマスが全てボムかどうか確認
      }
      if(clear_flag == CLEAR) break;
    }
    end_open(bomb,clear_flag); //最後の画面を表示
}

void game_clear(void) //クリア画面の表示
{
  printf("-----------------------------------------\n");
  printf("               GAME CLEAR                \n");
  printf("-----------------------------------------\n");
  printf("\n");
}

void game_over(void) //ゲームオーバーの画面表示
{
  printf("-----------------------------------------\n");
  printf("               GAME OVER                 \n");
  printf("-----------------------------------------\n");
  printf("\n");
}

void map_bomb_init(char map[][LENGTH], int bomb[][LENGTH]) //マップとボムの配列の初期化
{
  int i,j;

  for(i=0;i<HIGHT;i++) {
    for(j=0;j<LENGTH;j++) {
      map[i][j] = '*';
      if(i == 0) {
        bomb[i][j] = BOMB;
      } else {
        bomb[i][j] = 0;
      }
    }
  }
}

void shuffle_bomb(int bomb[][HIGHT]) //ボムの位置をシャッフル
{
  int i,j,x,y,swap;

  for(i=0;i<HIGHT;i++) {
    for(j=0;j<LENGTH;j++) {
      x = rand() % HIGHT;
      y = rand() % LENGTH;
      swap = bomb[i][j];
      bomb[i][j] = bomb[x][y];
      bomb[x][y] = swap;
    }
  }
}

int count_bomb(int bomb[][LENGTH]) //ボムの数をシャッフル
{
  int i,j,tmp = 0;

  for(i=0;i<HIGHT;i++) {
    for(j=0;j<LENGTH;j++) {
      if(bomb[i][j] == BOMB) tmp++;
    }
  }
  return tmp;
}

void disp(char map[][LENGTH]) //画面にマップ表示
{
  int i,j;

  disp_length();
  for(i=0;i<HIGHT;i++) {
    for(j=0;j<LENGTH;j++) {
      if(j == 0) disp_hight(i);
      printf("%c ",map[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void disp_length(void) //横の数字と壁の表示
{
  int j;
  printf("  ");

  for(j=0;j<LENGTH;j++){
    printf("%d ",j);
  }
  printf("\n");

  printf("  ");
  for(j=0;j<LENGTH;j++){
    if(j == 7) printf("-");
    else printf("--");
  }
  printf("\n");
}

void disp_hight(int high) //縦の数字と壁の表示
{
  printf("%d|",high);
}

void bomb_around_num(int bomb[][LENGTH]) //ボムの周りに数字を代入
{
  int x,y;

  for(x=0;x<HIGHT;x++) {
    for(y=0;y<LENGTH;y++) {
      if(bomb[x][y] == BOMB) {
        if(bomb[x-1][y-1] != BOMB) bomb[x-1][y-1] += 1;
        if(bomb[x][y-1] != BOMB)   bomb[x][y-1] += 1;
        if(bomb[x+1][y-1] != BOMB) bomb[x+1][y-1] += 1;
        if(bomb[x-1][y] != BOMB)   bomb[x-1][y] += 1;
        if(bomb[x+1][y] != BOMB)   bomb[x+1][y] += 1;
        if(bomb[x-1][y+1] != BOMB) bomb[x-1][y+1] += 1;
        if(bomb[x][y+1] != BOMB)   bomb[x][y+1] += 1;
        if(bomb[x+1][y+1] != BOMB) bomb[x+1][y+1] += 1;
      }
    }
  }
}
void open_map_info(int bomb[][LENGTH]) //マップの詳細を表示
{
  int i,j;

  disp_length();
  for(i=0;i<HIGHT;i++) {
    for(j=0;j<LENGTH;j++) {
      if(j == 0) disp_hight(i);
      if(bomb[i][j] == BOMB) printf("M ");
      else printf("%d ",bomb[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

int insert_num(int num) //マップに数字を代入
{
  char number;

  number = '0' + num;

  return number;
}

int check_map(char map[][LENGTH],int count) //残りのマップが全てボムかどうか確認
{
  int i,j,check=0;

  for(i=0;i<HIGHT;i++) {
    for(j=0;j<LENGTH;j++) {
      if(map[i][j] == '*' || map[i][j] == '+' || map[i][j] == ',') check++;
    }
  }
  if(check == count) return CLEAR;
  else return NCLEAR;
}

void end_open(int bomb[][LENGTH],int clear_flag) //ゲームクリア、ゲームオーバー画面の表示
{
  if(clear_flag != CLEAR) {
    game_over();
    open_map_info(bomb);
  } else {
    game_clear();
  }
}
