#include <gba.h>

#define W 240
#define H 160
#define WHITE RGB5(31,31,31)
#define BLACK RGB5(1,5,3)
#define GREEN RGB5(7,22,10)
#define LIME RGB5(20,31,12)
#define DARK RGB5(3,10,6)
#define BROWN RGB5(18,12,5)
#define BLUE RGB5(5,16,25)

static volatile u16 *const fb = (u16 *)VRAM;
static int choice = 0;
static int confirmed = 0;
static const char *names[] = {"FERNLING", "CINDRAKE", "BROOKIT"};
static const u16 colors[] = {RGB5(10,27,9), RGB5(31,13,3), RGB5(5,18,31)};

static const char glyphs[26][7] = {
{14,17,17,31,17,17,17},{30,17,17,30,17,17,30},{14,17,16,16,16,17,14},
{30,17,17,17,17,17,30},{31,16,16,30,16,16,31},{31,16,16,30,16,16,16},
{14,17,16,23,17,17,15},{17,17,17,31,17,17,17},{14,4,4,4,4,4,14},
{7,2,2,2,18,18,12},{17,18,20,24,20,18,17},{16,16,16,16,16,16,31},
{17,27,21,21,17,17,17},{17,25,21,19,17,17,17},{14,17,17,17,17,17,14},
{30,17,17,30,16,16,16},{14,17,17,17,21,18,13},{30,17,17,30,20,18,17},
{15,16,16,14,1,1,30},{31,4,4,4,4,4,4},{17,17,17,17,17,17,14},
{17,17,17,17,17,10,4},{17,17,17,21,21,21,10},{17,17,10,4,10,17,17},
{17,17,10,4,4,4,4},{31,1,2,4,8,16,31}
};
static void pixel(int x,int y,u16 c){if(x>=0&&x<W&&y>=0&&y<H)fb[y*W+x]=c;}
static void rect(int x,int y,int w,int h,u16 c){for(int yy=y;yy<y+h;yy++)for(int xx=x;xx<x+w;xx++)pixel(xx,yy,c);}
static void text(int x,int y,const char *s,u16 c,int scale){
 for(;*s;s++){char ch=*s;if(ch>='a'&&ch<='z')ch-=32;
 if(ch>='A'&&ch<='Z'){const char *g=(const char*)glyphs[ch-'A'];for(int yy=0;yy<7;yy++)for(int xx=0;xx<5;xx++)if(g[yy]&(1<<(4-xx)))rect(x+xx*scale,y+yy*scale,scale,scale,c);}
 else if(ch>='0'&&ch<='9'){int n=ch-'0';static const u8 nums[10][7]={{14,17,19,21,25,17,14},{4,12,4,4,4,4,14},{14,17,1,2,4,8,31},{30,1,1,14,1,1,30},{2,6,10,18,31,2,2},{31,16,16,30,1,1,30},{14,16,16,30,17,17,14},{31,1,2,4,8,8,8},{14,17,17,14,17,17,14},{14,17,17,15,1,1,14}};for(int yy=0;yy<7;yy++)for(int xx=0;xx<5;xx++)if(nums[n][yy]&(1<<(4-xx)))rect(x+xx*scale,y+yy*scale,scale,scale,c);}
 x+=6*scale;
 }
}
static void creature(int cx,int cy,u16 c,int type){
 rect(cx-15,cy-11,30,22,c);rect(cx-10,cy-16,20,8,c);rect(cx-21,cy-5,7,13,c);rect(cx+14,cy-5,7,13,c);
 rect(cx-9,cy-4,4,5,WHITE);rect(cx+5,cy-4,4,5,WHITE);pixel(cx-7,cy-2,BLACK);pixel(cx+7,cy-2,BLACK);
 rect(cx-5,cy+6,10,2,DARK);
 if(type==0){rect(cx-25,cy-24,9,14,GREEN);rect(cx-31,cy-27,11,6,LIME);rect(cx-19,cy-30,10,7,LIME);}
 if(type==1){rect(cx+15,cy-25,8,10,BROWN);rect(cx+19,cy-32,7,10,RGB5(31,10,2));}
 if(type==2){rect(cx-6,cy-27,12,10,BLUE);rect(cx-3,cy-33,6,7,RGB5(10,23,31));}
}
static int screen = 0; /* 0 starter, 1 confirmed, 2 overworld, 3 battle */
static int px = 1, py = 2, playerHp = 24, enemyHp = 18, wins = 0;
static const char mapdata[5][9] = {
  "TTGGGTTT",
  "TGPPPGGT",
  "TPPGPPGT",
  "TTGPPPGT",
  "TTTTGGGT"
};
static void drawMap(void) {
  int x,y;
  for(y=0;y<5;y++) for(x=0;x<8;x++) {
    int tx=8+x*28, ty=36+y*20; char t=mapdata[y][x]; u16 c=GREEN;
    if(t=='T') c=RGB5(3,12,5);
    if(t=='G') c=RGB5(8,24,8);
    if(t=='P') c=BROWN;
    rect(tx,ty,26,18,c);
    if(t=='T'){rect(tx+8,ty+3,10,9,RGB5(6,20,7));rect(tx+11,ty+12,4,5,BROWN);}
    if(t=='G'){rect(tx+5,ty+5,2,7,LIME);rect(tx+16,ty+3,2,9,LIME);}
    if(t=='P') rect(tx+5,ty+8,14,2,RGB5(23,18,9));
    if(x==px&&y==py){rect(tx+8,ty+3,10,11,WHITE);rect(tx+10,ty+5,6,3,BLUE);rect(tx+10,ty+10,6,3,RGB5(2,4,7));}
  }
}
static void draw(void){
 SetMode(MODE_3|BG2_ENABLE);
 rect(0,0,W,H,DARK);rect(0,0,W,30,GREEN);rect(0,27,W,3,LIME);
 text(8,8,"LEAF BLACK",WHITE,2);
 if(screen==0 || screen==1){
   if(screen==1){
     text(36,45,"STARTER CHOSEN",LIME,1);
     creature(120,83,colors[choice],choice);
     text(120-(int)(sizeof("FERNLING")-1)*3,108,names[choice],WHITE,1);
     if(choice==0) text(82,121,"PLANT TYPE",LIME,1);
     if(choice==1) text(91,121,"FIRE TYPE",LIME,1);
     if(choice==2) text(88,121,"WATER TYPE",LIME,1);
     rect(0,145,W,15,GREEN);text(8,149,"A START B BACK",WHITE,1);
   } else {
     text(14,43,"CHOOSE STARTER",LIME,1);
     rect(9,64,68,69,choice==0?RGB5(8,18,7):RGB5(5,12,8));rect(86,64,68,69,choice==1?RGB5(23,9,4):RGB5(5,12,8));rect(163,64,68,69,choice==2?RGB5(4,12,23):RGB5(5,12,8));
     creature(43,88,colors[0],0);creature(120,88,colors[1],1);creature(197,88,colors[2],2);
     text(14,114,"FERN",WHITE,1);text(91,114,"CIND",WHITE,1);text(168,114,"BROOK",WHITE,1);
     rect(0,145,W,15,GREEN);text(8,149,"LEFT RIGHT A SELECT",WHITE,1);
   }
   return;
 }
 if(screen==2){
   text(8,36,"ROUTE 01",LIME,1);drawMap();
   rect(0,140,W,20,GREEN);
   text(5,144,"HP",WHITE,1);text(24,144,playerHp>=20?"24":playerHp>=10?"18":"06",WHITE,1);
   text(61,144,"WINS",WHITE,1);text(98,144,wins==0?"0":wins<10?(wins==1?"1":wins==2?"2":"3"):"9",WHITE,1);
   text(128,144,"A GRASS",WHITE,1);
   return;
 }
 if(screen==3){
   text(8,36,"WILD BATTLE",LIME,1);
   creature(62,74,colors[choice],choice);
   creature(178,68,RGB5(18,15,8),0);
   text(15,99,names[choice],WHITE,1);
   text(143,91,"MUSHBUD",WHITE,1);
   text(15,112,"YOUR HP",LIME,1);rect(15,123,92,7,RGB5(18,5,5));rect(15,123,92*playerHp/24,7,LIME);
   text(137,112,"FOE HP",LIME,1);rect(137,123,88,7,RGB5(18,5,5));rect(137,123,88*enemyHp/18,7,RGB5(31,17,4));
   rect(0,140,W,20,GREEN);text(5,145,"A QUICK L SPECIAL B RUN",WHITE,1);
   return;
 }
}
int main(void){
 irqInit();irqEnable(IRQ_VBLANK);SetMode(MODE_3|BG2_ENABLE);
 while(1){
   VBlankIntrWait();scanKeys();u16 keys=keysDown();
   if(screen==0){
     if(keys&KEY_LEFT)choice=(choice+2)%3;
     if(keys&KEY_RIGHT)choice=(choice+1)%3;
     if(keys&KEY_A){confirmed=1;screen=1;playerHp=(choice==2?26:choice==1?22:24);}
   } else if(screen==1){
     if(keys&KEY_B){screen=0;confirmed=0;}
     if(keys&KEY_A){screen=2;px=1;py=2;}
   } else if(screen==2){
     if(keys&KEY_LEFT&&px>0)px--;
     if(keys&KEY_RIGHT&&px<7)px++;
     if(keys&KEY_UP&&py>0)py--;
     if(keys&KEY_DOWN&&py<4)py++;
     if(keys&KEY_B){screen=0;confirmed=0;}
     if(keys&KEY_A){
       if(mapdata[py][px]=='G'){screen=3;enemyHp=18;}
       else if(playerHp<(choice==2?26:choice==1?22:24))playerHp+=2;
       if(playerHp>(choice==2?26:choice==1?22:24))playerHp=(choice==2?26:choice==1?22:24);
     }
   } else if(screen==3){
     if(keys&KEY_B)screen=2;
     if(keys&(KEY_A|KEY_L)){
       int damage=(keys&KEY_L)?10:6;
       enemyHp-=damage;
       if(enemyHp<=0){
         wins++;screen=2;playerHp+=(choice==2?4:3);
         if(playerHp>(choice==2?26:choice==1?22:24))playerHp=(choice==2?26:choice==1?22:24);
       } else {
         playerHp-=4;
         if(playerHp<=0){playerHp=(choice==2?26:choice==1?22:24);screen=2;}
       }
     }
   }
   draw();
 }
 return 0;
}
