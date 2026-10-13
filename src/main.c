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
static void draw(void){
 SetMode(MODE_3|BG2_ENABLE);
 rect(0,0,W,H,DARK);rect(0,0,W,47,GREEN);rect(0,43,W,4,LIME);
 text(12,10,"LEAF BLACK",WHITE,2);
 if(confirmed){
   text(36,57,"STARTER CHOSEN",LIME,1);
   creature(120,94,colors[choice],choice);
   text(120-(int)(sizeof("FERNLING")-1)*3,121,names[choice],WHITE,1);
   if(choice==0) text(82,134,"PLANT TYPE",LIME,1);
   if(choice==1) text(91,134,"FIRE TYPE",LIME,1);
   if(choice==2) text(88,134,"WATER TYPE",LIME,1);
   rect(0,145,W,15,GREEN);text(8,149,"B BACK",WHITE,1);
   return;
 }
 text(14,58,"CHOOSE STARTER",LIME,1);
 rect(9,78,68,62,choice==0?RGB5(8,18,7):RGB5(5,12,8));rect(86,78,68,62,choice==1?RGB5(23,9,4):RGB5(5,12,8));rect(163,78,68,62,choice==2?RGB5(4,12,23):RGB5(5,12,8));
 rect(9,78,68,2,choice==0?LIME:GREEN);rect(86,78,68,2,choice==1?LIME:GREEN);rect(163,78,68,2,choice==2?LIME:GREEN);
 creature(43,101,colors[0],0);creature(120,101,colors[1],1);creature(197,101,colors[2],2);
 text(14,126,"FERN",WHITE,1);text(91,126,"CIND",WHITE,1);text(168,126,"BROOK",WHITE,1);
 rect(0,145,W,15,GREEN);text(8,149,"LEFT RIGHT A SELECT",WHITE,1);
}
int main(void){
 irqInit();irqEnable(IRQ_VBLANK);SetMode(MODE_3|BG2_ENABLE);
 while(1){
   VBlankIntrWait();scanKeys();u16 keys=keysDown();
   if(confirmed){if(keys&KEY_B)confirmed=0;}
   else{
     if(keys&KEY_LEFT)choice=(choice+2)%3;
     if(keys&KEY_RIGHT)choice=(choice+1)%3;
     if(keys&KEY_A)confirmed=1;
   }
   draw();
 }
 return 0;
}