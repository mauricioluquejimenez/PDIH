#include <stdio.h>
#include <dos.h>

unsigned char fondo = 0;
unsigned char texto = 15;

void gotoxy(int row, int col){
	union REGS inregs, outregs;

	inregs.h.ah = 2;
	inregs.h.bh = 0;

	inregs.h.dh = col;
	inregs.h.dl = row;

	int86(0x10, &inregs, &outregs);
}

void setcursortype(char tipo){
	union REGS inregs, outregs;

	inregs.h.ah = 1;
	switch(tipo){
		case '0':
			inregs.h.ch = 010;
			inregs.h.cl = 000;
			break;
		case '1':
			inregs.h.ch = 010;
			inregs.h.cl = 010;
			break;
		case '2':
			inregs.h.ch = 000;
			inregs.h.cl = 010;
			break;
	}
	int86(0x10, &inregs, &outregs);
}

void setvideomode(char modo){
	union REGS inregs, outregs;

	inregs.h.ah = 0;
	inregs.h.al = modo;

	int86(0x10, &inregs, &outregs);
}

int getvideomode(){
  union REGS inregs, outregs;

  inregs.h.ah = 15;
  int86(0x10, &inregs, &outregs);

  return outregs.h.al;
}

void textcolor(char color){
  texto = color;
}

void textbackground(char color){
	fondo = color;
}

void clrsrc(){
  union REGS inregs, outregs;

  inregs.h.ah = 6;
  inregs.h.al = 25;

  inregs.h.bh = 0;

  inregs.h.ch = 0;
  inregs.h.cl = 0;

  inregs.h.dh = 335;
  inregs.h.dl = 335;

  int86(0x10, &inregs, &outregs);
}

void cputchar(char c){
  union REGS inregs, outregs;

  inregs.h.ah = 9;
  inregs.h.al = c;

  inregs.h.bh = 0;
  inregs.h.bl = fondo << 4 | texto;

  inregs.x.cx = 1;

  int86(0x10, &inregs, &outregs);
}

/* Mostrando la tecla en el momento en el que se pulsa */

char getche(){
	union REGS inregs, outregs;

	inregs.h.ah = 1;
	int86(0x21, &inregs, &outregs);

	return outregs.h.al;
}

/* Sin mostrar la tecla en el momento en el que se pulsa

char getche(){
  union REGS inregs, outregs;

  inregs.h.ah = 0;

  int86(0x16, &inregs, &outregs);

  return outregs.h.al;
}

*/

void pausa(){
  union REGS inregs, outregs;
  inregs.h.ah = 0;
  int86(0x16, &inregs, &outregs);
}

int main(){

	int funcion;
	char modo, tecla, tipo;

	printf("\n    1: gotoxy()");
	printf("\n    2: setcursortype()");
	printf("\n    3: setvideomode()");
	printf("\n    4: getvideomode()");
	printf("\n    5: textcolor()");
	printf("\n    6: textbackground()");
	printf("\n    7: clrsrc()");
	printf("\n    8: cputchar()");
	printf("\n    9: getche()");
	printf("\n    Otra tecla: finalizar programa \n");

  printf("\n Elija una de las anteriores funciones: ");
  scanf("%d",&funcion);

	switch(funcion){
	  case 1:
	    gotoxy(40,15);
	    printf("*");
	    break;

	  case 2:
	    printf("\n Elija el aspecto del cursor (0, 1 y 2): ");
	    tipo = getche();
	    pausa();

	    setcursortype(tipo);
	    printf("\n Aspecto del cursos cambiado (pulse una tecla para salir): ");
	    pausa();
      break;

	  case 3:
	    printf("\n Seleccione el modo de video: ");
	    scanf("%d", &modo);
      setvideomode(modo);
      printf("\n Modo de video: %d", modo);

	    printf("\n Pulse una tecla para salir: ");
	    tecla = getche();
	    break;

	  case 4:
	    modo = getvideomode();
      printf("\n Modo de video: %d", modo);
      break;

	  case 5:
	    printf("\n Elija un color de texto: ");
	    scanf("%d", &texto);
	    textcolor(texto);

	    printf("\n Color de texto cambiado: ");
	    cputchar('*');
      break;

	  case 6:
	    printf("\n Elija un color de fondo: ");
	    scanf("%d", &fondo);
	    textbackground(fondo);

	    printf("\n Color de fondo cambiado: ");
	    cputchar('*');
      break;

	  case 7:
	    clrsrc();
	    break;

	  case 8:
	    printf("\n Pulse una tecla: ");
	    scanf(" %c", &tecla);

	    printf(" Ha pulsado: ");
	    cputchar(tecla);
	    break;

	  case 9:
	    printf("\n Pulse una tecla: ");
	    tecla = getche();
	    pausa();

	    printf("\n Ha pulsado: %c", tecla);
	    break;
	}

	return 0;
}