//SETEAR EN X86 PARA QUE FUNCIONE
#include "sl.h"
#include <iostream>

struct Jugador
{
	float x;
	float y=300;
	float altura=100;
	float ancho=10;
	int Puntaje = 0;
};
enum Estado
{
	Jugando,
	Menu,
	PantallaFinal,
	Cerrar
};
Estado EstadoJuego = Menu;
bool Colisionando = false;
bool Colisionando2 = false;
int BolaRadio = 10;
float BolaX = 300;
float BolaY = 200;
float BolaMovX = 6;
float BolaMovY = 6;
Jugador P1;
Jugador P2;
int PantallaAncho = 600;
int PantallaAlto = 400;

int main()
{
	P1.x = 10;
	P2.x = PantallaAncho - 10;
	slWindow(PantallaAncho, PantallaAlto, "Pong en sigil-Iñaki Diez", false);
	slSetFont(slLoadFont("ttf/white_rabbit.ttf"), 24);
	slSetFontSize(25);

	while (EstadoJuego==Menu && !slShouldClose())
	{
		if (slGetKey(SL_KEY_ESCAPE)==true)
		{
			EstadoJuego = Cerrar;
			break;
		}
		if (slGetKey(' ') == true)
		{
			EstadoJuego = Jugando;
			break;
		}
		slSetForeColor(0.0, 0.4, 1.0, 1.0);
		slRectangleFill(PantallaAncho / 2, PantallaAlto - PantallaAlto / 3, 400, 50);
		slSetForeColor(1.0, 0.0, 0.0, 1.0);
		slRectangleFill(PantallaAncho / 2, PantallaAlto / 3, 400, 50);
		slSetForeColor(2.5, 2.5, 2.5, 1.0);
		slText(105, 260, "SPACEBAR TO START PLAYING :)");
		slText(105, 125, "ESCAPE TO CLOSE GAME :(");
		slRender();
	}

	while (EstadoJuego==Jugando&&!slShouldClose())
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
		if (slGetKey(SL_KEY_ESCAPE))
		{
			EstadoJuego = Cerrar;
			break;
		}
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
		}
		if (BolaX + BolaRadio >= PantallaAncho)
		{
			BolaMovX *= -1;
			BolaX = P2.x-10;
			BolaY = P2.y;
			P1.Puntaje +=1;
		}
		if (BolaX - BolaRadio <= 0)
		{
			BolaMovX *= -1;
			BolaX = P1.x + 10;
			BolaY = P1.y;
			P2.Puntaje +=1;
		}
		if (P1.Puntaje >= 10 || P2.Puntaje >= 10)
		{
			EstadoJuego = PantallaFinal;
			break;
		}
		slSetForeColor(0.0, 0.0, 1.0, 1.0);
		slRectangleFill(P1.x, P1.y, P1.ancho, P1.altura);
		slSetForeColor(1.0, 0.0, 0.0, 1.0);
		slRectangleFill(P2.x, P2.y, P2.ancho, P2.altura);
		slSetForeColor(0.0, 0.8, 0.2, 1.0);
		slCircleFill(BolaX, BolaY, BolaRadio, 15);
		slRender();
	}

	while (EstadoJuego==PantallaFinal && !slShouldClose())
	{
		if (P1.Puntaje>=10)
		{
			slSetForeColor(0.0, 0.0, 1.0, 1.0);
			slText(105, 260, ":) THE WINNER IS PLAYER 1 :(");
		}
		if (P2.Puntaje>=10)
		{
			slSetForeColor(1.0, 0.0, 0.0, 1.0);
			slText(105, 260, ":( THE WINNER IS PLAYER 2 :)");
		}
		slSetForeColor(2.5, 2.5, 2.5, 1.0);
		slText(100, 30, "ESCAPE TO QUIT.");
		if (slGetKey(SL_KEY_ESCAPE))
		{
			EstadoJuego = Cerrar;
			break;
		}
		slRender();
	}
	slClose();
	return 0;
}