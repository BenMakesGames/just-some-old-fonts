/*
	FONTDEMO.CPP
	Demo of the ColorFont class

	Written by Nikolai Soumarokov
	Some graphics routines were borrowed from the book
	"Tricks of the Game Programming Gurus" by Andre LaMothe et al.

	Build with Turbo C++ 3.0 or above using LARGE memory model
*/

#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <alloc.h>
#include "cfont.h"

#define VGA256                  0x13
#define TEXT_MODE               0x03
#define PALETTE_MASK            0x3C6
#define PALETTE_REGISTER        0x3C8
#define PALETTE_DATA            0x3C9
#define SCREEN_WIDTH            320
#define SCREEN_HEIGHT           200


typedef unsigned char far * far_pointer;

// pointers to VGA page
far_pointer video_buf = (unsigned char far *)0xA0000000L;
unsigned int far *video_buf_w = (unsigned int far *)0xA0000000L;

// pointer to double buffer
far_pointer doubl_buf;

ColorFont BigFont("bigfont.fnt");
ColorFont SmallFont("3dfont.fnt");


int load_some_palette(void);
void demo();
void page_1();
void page_2();
void page_3();
void page_4();
void page_5();
void page_6();
void page_7();
void page_8();
void transit_1();
void transit_2();
void transit_3a();
void transit_3b();
int  press_a_key();


main() {

    doubl_buf = (far_pointer) farcalloc(1,64000);
    if (!doubl_buf) {
	puts("Not enough memory");
	exit(1);
    }

    asm {				// Switch to VGA 320x200 mode
	mov ah,0
	mov al,VGA256
	int 10h
    }

    if (!load_some_palette()) {
	asm {				// Switch back to text mode
	    mov ah,0
	    mov al,TEXT_MODE
	    int 10h
	}
	puts("Error loading palette");
	exit(1);
    }

    // tell the fonts to print directly to VGA screen
    BigFont.SetVideoAddress(video_buf);
    SmallFont.SetVideoAddress(video_buf);

    // set the character translation tables
    BigFont.SetTranslation("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!:#$%&()-.,'\"");
    SmallFont.SetTranslation("ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!:#$%&()-.,'\"");

    // tell the fonts that the letter '0' should look as 'O'
    BigFont.SetSameChar('0','O');
    SmallFont.SetSameChar('0','O');

    demo();

    asm {				// Switch back to text mode
	mov ah,0
	mov al,TEXT_MODE
	int 10h
    }

    farfree(doubl_buf);
    return 0;
}



void demo() {

    page_1();
    if (press_a_key()) return;
    transit_1();
    page_2();
    if (press_a_key()) return;
    transit_2();
    page_3();
    if (press_a_key()) return;
    transit_1();
    page_4();
    if (press_a_key()) return;
    transit_1();
    page_5();
    if (press_a_key()) return;
    transit_1();
    page_6();
    if (press_a_key()) return;
    transit_3a();
    page_7();
    transit_3b();
    if (press_a_key()) return;
    transit_1();
    page_8();
    if (press_a_key()) return;
    return;
}


void page_1() {
    BigFont.BPrint(35,0,"COLORFONT CLASS");
    SmallFont.Repaint(2,71,103,73,105);
    SmallFont.BPrint(50,20,"DEMONSTRATION PROGRAM");
    SmallFont.Repaint(2,103,55,105,57);
    SmallFont.BPrint(50,34,"BY NIKOLAI SOUMAROKOV");
    SmallFont.Repaint(2,55,167,57,169);
    SmallFont.BPrint(0,55,"- WORKS IN STANDARD 320X200X256\n  GRAPHICS MODE");
    SmallFont.BPrint(0,78,"- CAN PRINT TO SCREEN OR TO ANY");
    SmallFont.BPrint(0,88,"  USER-DEFINED MEMORY BUFFER");
    SmallFont.BPrint(0,101,"- READS FONT FILES CREATED WITH");
    SmallFont.BPrint(0,111,"  'GNOOM II' SPRITE EDITOR");
    SmallFont.BPrint(0,124,"- SUPPORTS UP TO 255 CHARACTERS");
    SmallFont.BPrint(0,134,"  PER FONT. THE NUMBER OF FONTS");
    SmallFont.BPrint(0,144,"  IS LIMITED ONLY BY COMPUTER'S");
    SmallFont.BPrint(0,154,"  MEMORY");
    SmallFont.BPrint(0,167,"- IS ABSOLUTELY FREE!");
    SmallFont.Repaint(2,167,199,169,201);
}

void page_2() {
    BigFont.Repaint(2,68,36,72,40);
    BigFont.BPrint(50,0,"LOADING FONTS");
    SmallFont.Repaint(2,199,71,201,73);
    SmallFont.BPrint(60,20,"COULD NOT BE EASIER");

    SmallFont.Repaint(2,71,167,73,171);
    SmallFont.BPrint(10,55,"    CREATE YOUR FONT WITH   ");
    SmallFont.BPrint(15,65,"THE 'GNOOM II' SPRITE EDITOR");
    SmallFont.BPrint(15,75,"(AVAILABLE ON X2FTP.OULU.FI)");
    SmallFont.BPrint(10,85,"AND LOAD IT INTO YOUR PROGRAM");
    SmallFont.BPrint(15,95," WITH A SINGLE DECLARATION:");
    SmallFont.Repaint(2,167,105,171,107);
    SmallFont.BPrint(15,115,"COLORFONT BIGFONT(FILE_NAME)");
    SmallFont.Repaint(2,105,167,107,171);
    SmallFont.BPrint(25,135,"YOU CAN OPEN AS MANY FONTS");
    SmallFont.BPrint(25,145,"       AS YOU WANT!       ");
    SmallFont.Repaint(2,167,199,171,201);
}


void page_3() {
    SmallFont.Repaint(2,199,167,201,171);
    SmallFont.BPrint(10,55,"USE THE");
    SmallFont.BPrint(30,65,"FUNCTION TO DEFINE STRING");
    SmallFont.BPrint(70,75,"TRANSLATION RULES");
    SmallFont.BPrint(5,95,"USE THE");
    SmallFont.BPrint(10,105,"FUNCTION TO SET UP CHARACTERS");
    SmallFont.BPrint(30,115,"WHICH LOOK THE SAME - FOR");
    SmallFont.BPrint(10,125,"EXAMPLE, O-DIGIT AND O-LETTER");
    SmallFont.Repaint(2,167,105,171,107);
    SmallFont.BPrint(90,55,"SETTRANSLATION(\"...\")");
    SmallFont.BPrint(85,95,"SETSAMECHAR('C1','C2')");
    SmallFont.Repaint(2,105,199,107,201);
}


void page_4() {
    unsigned int i;

    BigFont.BPrint(48,0,"PRINTING FONTS");

    for (i=30; i<78; i++) _fmemset(video_buf_w+i*160,i+82,320);

    SmallFont.Repaint(2,199,167,201,171);
    SmallFont.BPrint(145,35,"- PRINTS A STRING");
    SmallFont.Print (145,45,"- PRINTS A STRING");
    SmallFont.Print (145,55,"  PRESERVING THE\n  BACKGROUND");
    SmallFont.BPrint(150,85,"AND");
    SmallFont.BPrint(10,95,"ARE ANALOGOUS BUT ALSO SUPPORT");
    SmallFont.BPrint(120,105,"CLIPPING");
    SmallFont.BPrint(0,125,"USE");
    SmallFont.BPrint(150,135,"AND");
    SmallFont.BPrint(30,145,"TO PRINT SINGLE CHARACTERS");
    SmallFont.Repaint(2,167,105,171,107);
    SmallFont.Print(5,35,"BPRINT(X,Y,S)");
    SmallFont.Print(5,45," PRINT(X,Y,S)");
    SmallFont.BPrint(0,85,"CBPRINT(X,Y,S)     CPRINT(X,Y,S)");
    SmallFont.BPrint(0,125,"    BPUTCH(X,Y,C), PUTCH(X,Y,C),");
    SmallFont.BPrint(0,135,"CBPUTCH(X,Y,C)     CPUTCH(X,Y,C)");

    SmallFont.Repaint(2,105,199,107,201);
}


void page_5() {

    int oldc1, oldc2;
    unsigned char i;

    BigFont.BPrint(48,0,"PRINTING FONTS");

    SmallFont.Repaint(2,199,167,201,171);
    SmallFont.BPrint(0,25,"USE THE");
    SmallFont.BPrint(10,35, "FUNCTION TO DEFINE HORIZONTAL");
    SmallFont.BPrint(5,45,"AND VERTICAL CHARACTER SPACING");
    SmallFont.BPrint(240,135,"AND");
    SmallFont.BPrint(190,145,"FUNCTIONS");
    SmallFont.BPrint(5,155,"ALLOW YOU TO CHANGE FONT COLORS");
    SmallFont.Repaint(2,167,105,171,107);
    SmallFont.BPrint(80,25,"SETSPACING(HSPAC,VSPAC)");
    SmallFont.BPrint(50,135,"CHANGECOLOR(C1,C2)");
    SmallFont.BPrint(40,145,"REPAINT(N,...)");
    SmallFont.Repaint(2,105,71,107,75);
    SmallFont.SetSpacing(10);
    SmallFont.BPrint(0,65,"ABCDEFGHIJKLMNOP");
    SmallFont.SetSpacing(11);
    SmallFont.BPrint(0,75,"ABCDEFGHIJKLMNOP");
    SmallFont.SetSpacing(12);
    SmallFont.BPrint(0,85,"ABCDEFGHIJKLMNOP");
    SmallFont.SetSpacing(13);
    SmallFont.BPrint(0,95,"ABCDEFGHIJKLMNOP");
    SmallFont.SetSpacing(14,12);
    SmallFont.BPrint(0,105,"ABCDEFGHIJKLMNOP\nABCDEFGHIJKLMNOP");
    oldc1 = 71;
    oldc2 = 75;
    for (i=0; i<32; i++) {
	SmallFont.ChangeColor(oldc1,16 + i*4);
	SmallFont.ChangeColor(oldc2,17 + i*4);
	SmallFont.BPutCh(i*10,167,i);
	oldc1 = 16+i*4;
	oldc2 = 17+i*4;
    }
    SmallFont.SetSpacing();			// restore default spacing
    SmallFont.Repaint(2,oldc1,199,oldc2,201);
}


void page_6() {
    unsigned int i, j;
    char TestStr[53] = "COLORFONT COLORFONT COLORFONT COLORFONT COLORFONT CO";
    char DispStr[33];

    BigFont.BPrint(48,0,"   CLIPPING");

    _fmemset(video_buf_w+9620,255,239);
    _fmemset(video_buf_w+28020,255,239);
    for (i=61; i<175; i++) {
       _fmemset(video_buf_w+i*160+20,255,1);
       _fmemset(video_buf_w+i*160+139,255,1);
    }

    SmallFont.Repaint(2,199,167,201,171);
    SmallFont.BPrint(10,25,"DEFINE CLIPPING AREA USING THE");
    SmallFont.BPrint(10,45,"           FUNCTION           ");
    SmallFont.Repaint(2,167,105,171,107);
    SmallFont.BPrint(20,35,"SETCLIPAREA(LFT,RGH,TOP,BOT)");
    SmallFont.Repaint(2,105,71,107,74);
    SmallFont.SetClipArea(41,279,61,174);
    for (i=0; i<20; i++) {
	for (j=0; j<32; j++) DispStr[j] = TestStr[j+i];
	SmallFont.CBPrint(0,i*10,DispStr);
    }
    SmallFont.SetClipArea();
    SmallFont.Repaint(2,71,199,74,201);
}


void page_7() {

    SmallFont.SetVideoAddress(doubl_buf);
    BigFont.SetVideoAddress(doubl_buf);
    BigFont.BPrint(34,0,"DOUBLE BUFFERING");

    SmallFont.Repaint(2,199,167,201,171);
    SmallFont.BPrint(30,45,"THIS PAGE WAS CREATED IN A");
    SmallFont.BPrint(45,55,"DOUBLE BUFFER USING THE");
    SmallFont.BPrint(25,75,"FUNCTION AND THEN COPIED TO");
    SmallFont.BPrint(100,85,"VGA SCREEN");
    SmallFont.BPrint(60,105,"WITH THE HELP OF THE");
    SmallFont.BPrint(15,125,"FUNCTION, TEXT CAN BE PRINTED");
    SmallFont.BPrint(35,135,"ON VIRTUAL PAGES SIZES OF");
    SmallFont.BPrint(20,145,"WHICH EXCEED THE SIZE OF THE");
    SmallFont.BPrint(65,155,"STANDARD VGA SCREEN");
    SmallFont.Repaint(2,167,105,171,107);
    SmallFont.BPrint(60,65,"SETVIDEOADDRESS(PTR)");
    SmallFont.BPrint(25,115,"SETVSCREENDIM(WIDTH,HEIGHT)");
    SmallFont.Repaint(2,105,199,107,201);
    SmallFont.SetVideoAddress();
    BigFont.SetVideoAddress();
}


void page_8() {
    BigFont.Repaint(2,36,132,40,136);
    BigFont.BPrint(100,80,"THE END");
    SmallFont.Repaint(2,199,71,201,73);
}


int press_a_key() {
    int ch;

    SmallFont.BPrint(90,189,"PRESS ANY KEY");
    while (kbhit()) getch();
    ch = getch();
    if (ch==27) return 1;		// ESC is pressed -> quit
    return 0;
}

void transit_1() {
    int i;

    for (i=1; i<=100; i++) {
	_fmemset(video_buf_w+i*160,0xFFFF,320);
	_fmemset(video_buf_w+i*160-160,0x0000,320);
	_fmemset(video_buf_w+(199-i)*160,0xFFFF,320);
	_fmemset(video_buf_w+(199-i)*160+160,0x0000,320);
	delay(10);
    }
    for (i=100; i>=1; i--) {
	_fmemset(video_buf_w+i*160,0x0000,320);
	_fmemset(video_buf_w+i*160-160,0xFFFF,320);
	_fmemset(video_buf_w+(199-i)*160,0x0000,320);
	_fmemset(video_buf_w+(199-i)*160+160,0xFFFF,320);
	delay(10);
    }
    _fmemset(video_buf_w,0x0000,320);
    _fmemset(video_buf_w+160*199,0x0000,320);
}


void transit_2() {
    int i,j;
    long pos;

    for (i=1; i<320; i++) {
	pos = 15999+i;
	for (j=50; j<161; j++) {
	    *(video_buf+pos) = 255;
	    *(video_buf+pos-1) = 0;
	    pos += 320;
	}
	delay(5);
    }
    pos = 16318;
    for (j=50; j<161; j++) {
	*(video_buf+pos) = 0;
	pos += 320;
    }
}


void transit_3a() {
    int i;

    for (i=1; i<=100; i++) {
	_fmemset(video_buf_w+i*160,0xFFFF,320);
	_fmemset(video_buf_w+i*160-160,0x0000,320);
	_fmemset(video_buf_w+(199-i)*160,0xFFFF,320);
	_fmemset(video_buf_w+(199-i)*160+160,0x0000,320);
	delay(10);
    }
}

void transit_3b() {
    int i;

    for (i=100; i>=1; i--) {
	_fmemcpy(video_buf_w+i*160,doubl_buf+i*320,320);
	_fmemset(video_buf_w+i*160-160,0xFFFF,320);
	_fmemcpy(video_buf_w+(199-i)*160,doubl_buf+(199-i)*320,320);
	_fmemset(video_buf_w+(199-i)*160+160,0xFFFF,320);
	delay(10);
    }
    _fmemcpy(video_buf_w,doubl_buf,320);
    _fmemcpy(video_buf_w+160*199,doubl_buf+320*199,320);
}


int load_some_palette() {

    FILE *fhandle;
    int index;
    unsigned char c_red, c_green, c_blue;

    if ((fhandle = fopen("default.pal", "rb")) == NULL)
	return 0;

    for (index = 0; index <= 255; index++) {
	if (fscanf(fhandle,"%c%c%c",&c_red,&c_green,&c_blue) != 3)
	    return 0;

	outportb(PALETTE_MASK, 0xff);
	outportb(PALETTE_REGISTER, index);
	outportb(PALETTE_DATA, c_red);
	outportb(PALETTE_DATA, c_green);
	outportb(PALETTE_DATA, c_blue);
    }

    if (fclose(fhandle) == EOF)
	return 0;
    return 1;
}



