#include "sl.h"
#include <iostream>
//SETEAR EN X86 PARA QUE FUNCIONE
struct Jugador
{
	float x;
	float y=300;
	float altura=100;
	float ancho=10;
	int Puntaje = 0;
};
bool Colisionando = false;
bool Colisionando2 = false;
int BolaRadio = 10;
float BolaX = 300;
float BolaY = 200;
float BolaMovX = 4;
float BolaMovY = 4;
Jugador P1;
Jugador P2;
int PantallaAncho = 600;
int PantallaAlto = 400;

int main(int args, char *argv[])
{
	if (P1.Puntaje>=10||P2.Puntaje>=10)
	{
		slClose;
	}
	P1.x = 10;
	P2.x = PantallaAncho - 10;
	slWindow(PantallaAncho, PantallaAlto, "Pong en sigil, masomeno", false);
	double dt=slGetDeltaTime();
	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		if (BolaX + BolaRadio >= P2.x&&BolaX - BolaRadio <= P2.x &&BolaY - BolaRadio <= P2.y + P2.altura / 2 && BolaY + BolaRadio >= P2.y - P2.altura / 2)
		{
			Colisionando = true;
		}
		else
		{
			Colisionando = false;
		}
		if (BolaX - BolaRadio <= P1.x&&BolaX + BolaRadio >= P1.x &&BolaY - BolaRadio <= P1.y + P1.altura / 2 && BolaY + BolaRadio >= P1.y - P1.altura / 2)
		{
			Colisionando2 = true;
		}
		else
		{
			Colisionando2 = false;
		}
		BolaX += BolaMovX;
		BolaY += BolaMovY;
		if (slGetKey(SL_KEY_LEFT_CONTROL) == true)BolaMovY *= -1;
		if (slGetKey(SL_KEY_DOWN)==true && P2.y - P2.altura / 2 > 0)P2.y-=5;
		if (slGetKey(SL_KEY_UP)==true && P2.y+P2.altura/2 < PantallaAlto)P2.y+=5;
		if (slGetKey('S') == true&&P1.y-P1.altura/2>0)P1.y -= 5;
		if (slGetKey('W') == true && P1.y + P1.altura / 2 < PantallaAlto)P1.y += 5;
		if (BolaY+BolaRadio>=PantallaAlto)BolaMovY*=-1;
		if (BolaY - BolaRadio <= 0)BolaMovY *= -1;
		if (BolaX + BolaRadio >= P2.x&&BolaX - BolaRadio <= P2.x &&BolaY - BolaRadio <= P2.y + P2.altura / 2 && BolaY + BolaRadio >= P2.y - P2.altura / 2 &&Colisionando == false)
		{
			if (BolaY < P2.y&&BolaMovY>0)
			{
				BolaMovY *= -1.0f;
			}
			if (BolaY > P2.y&&BolaMovY<0)
			{
				BolaMovY *= -1.0f;
			}
			BolaMovX *= -1;
			//Colisionando = true;//innecesario creo
		}
		if (BolaX - BolaRadio <= P1.x&&BolaX + BolaRadio >= P1.x &&BolaY - BolaRadio <= P1.y + P1.altura / 2 && BolaY + BolaRadio >= P1.y - P1.altura / 2 && Colisionando2 == false)
		{
			if (BolaY < P1.y&&BolaMovY>0)
			{
				BolaMovY *= -1.0f;
			}
			if (BolaY > P1.y&&BolaMovY < 0)
			{
				BolaMovY *= -1.0f;
			}
			BolaMovX *= -1;
			//Colisionando2 = true;//innecesario creo
		}
		if (BolaX + BolaRadio >= PantallaAncho)
		{
			BolaMovX *= -1;
			BolaX = P2.x-10;
			BolaY = P2.y;
			P1.Puntaje += 1;
		}
		if (BolaX - BolaRadio <= 0)
		{
			BolaMovX *= -1;
			BolaX = P1.x + 10;
			BolaY = P1.y;
			P2.Puntaje += 1;
		}
		
		slSetForeColor(0.0, 0.8, 0.2, 1.0);
		slRectangleFill(P1.x, P1.y, P1.ancho, P1.altura);
		slRectangleFill(P2.x, P2.y, P2.ancho, P2.altura);
		slCircleFill(BolaX, BolaY, BolaRadio, 15);
		slRender();
	}
	slClose();
	return 0;
}