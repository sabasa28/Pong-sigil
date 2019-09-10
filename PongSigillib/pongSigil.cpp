#include "sl.h"
#include <iostream>
struct Paleta
{
	float x;
	float y=300;
	float altura=100;
	float ancho=10;
	bool enPantalla = true;
};
int BolaRadio = 10;
float BolaX = 300;
float BolaY = 200;
float BolaMovX = 4;
float BolaMovY = 4;
Paleta P1;
Paleta P2;
int PantallaAncho = 600;
int PantallaAlto = 400;

int main(int args, char *argv[])
{
	P1.x = 10;
	P2.x = PantallaAncho - 10;
	// set up our window and a few resources we need
	slWindow(PantallaAncho, PantallaAlto, "Pong en sigil, masomeno", false);
	double dt=slGetDeltaTime();
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		BolaX += BolaMovX;
		BolaY += BolaMovY;
		if (BolaY+BolaRadio>=PantallaAlto)BolaMovY*=-1;
		if (BolaY - BolaRadio <= 0)BolaMovY *= -1;
		if (BolaX + BolaRadio >= P2.x&&BolaY<=P2.y+P2.altura/2&&BolaY>=P2.y-P2.altura)BolaMovX *= -1;//QUE NO SEA MAYOR O IGUAL SINO MAYOR AL PRINCIPIO DE LA X Y DE LA X MAS EL ANCHO
		if (BolaX - BolaRadio <= P1.x)BolaMovX *= -1;
		if (P1.y>=0&&P1.y<=PantallaAlto)
		{
			P1.enPantalla = true;
		}
		else
		{
			P1.enPantalla = false;
		}
		//input
		if (slGetKey(SL_KEY_DOWN)==true && P2.y - P2.altura / 2 > 0)P2.y-=5;
		if (slGetKey(SL_KEY_UP)==true && P2.y+P2.altura/2 < PantallaAlto)P2.y+=5;
		if (slGetKey('S') == true&&P1.y-P1.altura/2>0)P1.y -= 5;
		if (slGetKey('W') == true && P1.y + P1.altura / 2 < PantallaAlto)P1.y += 5;
		// large text and fat line
		slSetForeColor(0.0, 0.8, 0.2, 1.0);
		slRectangleFill(P1.x, P1.y, P1.ancho, P1.altura);
		slRectangleFill(P2.x, P2.y, P2.ancho, P2.altura);
		slCircleFill(BolaX, BolaY, BolaRadio, 15);
		// smaller subtext
		slSetFontSize(14);
		slText(200, 220, "Sprites, text, sound, input, and more!");
		slLine(300, 400, 300, 0);
		slRender();// draw everything
	}
	slClose();// close the window and shut down SIGIL
	return 0;
}