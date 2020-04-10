#include "stdafx.h"
#include "module.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iterator>
#pragma warning (disable:4996)
using namespace std;
class Window
{
private:
	int x, y;
	int color[COLOR_PAR];
	int myatoi(string line)
	{
		stringstream acc;
		int ans;
		acc << line;
		acc >> ans;
		return ans;
	}
public:
	void changepos(string xx, string yy)
	{
		x = myatoi(xx);
		y = myatoi(yy);
	}
	void changecolor(string r, string g, string b)
	{
		color[0] = myatoi(r);
		color[1] = myatoi(g);
		color[2] = myatoi(b);
	}
	void display(HDC hdc)
	{
		HBRUSH hBrush;
		HGDIOBJ hOldPen;
		hBrush = CreateSolidBrush(RGB(color[0], color[1], color[2]));
		SelectObject(hdc, hBrush);
		hOldPen = SelectObject(hdc, hBrush);
		Rectangle(hdc, x, y, x + W_X, y + W_Y);
	}
};

class Button
{
private:
	int x, y;
	int color[COLOR_PAR];
	int h_color[COLOR_PAR];
	string name;
	int sel;
	int myatoi(string line)
	{
		stringstream acc;
		int ans;
		acc << line;
		acc >> ans;
		return ans;
	}
public:
	Button()
	{
		sel = 0;
	}
	void changepos(string xx, string yy)
	{
		x = myatoi(xx);
		y = myatoi(yy);
	}
	void changecolor(string r, string g, string b)
	{
		color[0] = myatoi(r);
		color[1] = myatoi(g);
		color[2] = myatoi(b);
	}
	void changeh_color(string r, string g, string b)
	{
		color[0] = myatoi(r);
		color[1] = myatoi(g);
		color[2] = myatoi(b);
	}
	void changename(string n)
	{
		name = n;
	}
	void display(HDC hdc)
	{
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(RGB(color[0], color[1], color[2]));
		RECT r = {x, y, x + B_SIZE * 4, y + B_SIZE};
		FillRect(hdc, &r, hBrush);
		TextOutA(hdc, x / 2 + B_SIZE * 5, y + B_Y, name.c_str(), name.length());
	}
	void displaypressed(HDC hdc)
	{
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(RGB(h_color[0], h_color[1], h_color[2]));
		RECT l = {x, y, x + B_SIZE * 4, y + B_SIZE };
		FillRect(hdc, &l, hBrush);
		TextOutA(hdc, x / 2 + B_SIZE * 5, y + B_Y, name.c_str(), name.length());
	}
	int returny()
	{
		return y;
	}
	int returnx()
	{
		return x;
	}
	void changesel(int i)
	{
		sel = i;
	}
	int returnsel()
	{
		return sel;
	}
	string returnname()
	{
		return name;
	}
};

vector <Window> w;
vector <Button> b;

void SystemClose()
{
	w.clear();
	b.clear();
}

int but_num = 0;
int new_but = 0;

vector <string> buff;
void split(string line)
{
	stringstream ss(line);
	copy
	(
		istream_iterator<string>(ss),
		istream_iterator<string>(),
		back_inserter(buff)
	);
}
void SystemInit(const char* file_name)
{
	ifstream stream;
	string buf;
	int i_b = 0, i_w = 0, w_win = 0;
	stream.open(file_name);
	string command;
	while (!stream.eof())
	{
		getline(stream, buf);
		split(buf);
		command = buff[0];
		if (command == "MenuGo")
		{
			while (command != "MenuEnd")
			{
				buff.clear();
				getline(stream, buf);
				split(buf);
				command = buff[0];
				if (command == "WinGo")
				{
					Window win;
					w.push_back(win);
					while (command != "WinEnd")
					{
						buff.clear();
						getline(stream, buf);
						split(buf);
						command = buff[0];
						if (command == "Pos") w[i_w].changepos(buff[1], buff[2]);
						if (command == "Color") w[i_w].changecolor(buff[1], buff[2], buff[3]);
					}
					i_w++;
				}
				if (command == "ButtonGo")
				{
					Button but;
					b.push_back(but);
					while (command != "ButtonEnd")
					{
						buff.clear();
						getline(stream, buf);
						split(buf);
						command = buff[0];
						if (command == "Pos")  b[i_b].changepos(buff[1], buff[2]);
						if (command == "Color") b[i_b].changecolor(buff[1], buff[2], buff[3]);
						if (command == "Higlight") b[i_b].changeh_color(buff[1], buff[2], buff[3]);
						if (command == "Name") b[i_b].changename(buff[1]);
					}
					i_b++;
				}
			}
		}
	}
}

void Print_new_button(HDC hdc, vector <Button> parm, int num, int flag) //ok
{
	if (flag == 1) parm[num].displaypressed(hdc);
	else parm[num].display(hdc);
}

void Print_wind(HDC hdc, vector <Window> parm, int num) //ok
{
	parm[num].display(hdc);
}

int find_but(int up_down)
{
	int min = 3000;
	unsigned int k = 0;
	int f = 0;
	while (k < b.size())
	{
		int dif = 0;
		if (up_down == 0) dif = (b[k].returny() - b[but_num].returny()); //down
		if (up_down == 1) dif = (b[but_num].returny() - b[k].returny()); //up
		if ((k != but_num) && (dif > 0) && (dif < min))
		{
			new_but = k;
			min = dif;
			f = 1;
		}
		k++;
	}
	return f;
}

int SystemUpdate(HWND hWnd, UINT message, WPARAM wParam, char* name) //??
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		HDC hdc = GetDC(hWnd);

		switch (wParam)
		{
		case VK_DOWN:
		{
			int f = find_but(0);
			b[but_num].changesel(0);
			b[new_but].changesel(1);
			unsigned int i = 0;
			while (i < b.size())
			{
				Print_new_button(hdc, b, i, b[i].returnsel());
				i++;
			}
			but_num = new_but;
		}
		break;

		case VK_UP:
		{
			int f = find_but(1);
			b[but_num].changesel(0);
			b[new_but].changesel(1);
			unsigned int i = 0;
			while (i < b.size())
			{
				Print_new_button(hdc, b, i, b[i].returnsel());
				i++;
			}
			but_num = new_but;
		}
		break;

		case VK_RETURN:
		{
			strcpy(name, b[but_num].returnname().c_str());
			return -1;
		}
		break;
		case VK_ESCAPE:
		{
			exit(1);
		}
		break;
		};
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...

		unsigned int j = 0;
		while (j < w.size())
		{
			Print_wind(hdc, w, j);
			j++;
		}

		unsigned int i = 0;

		while (i < b.size())
		{
			Print_new_button(hdc, b, i, 0);
			i++;
		}
		Print_new_button(hdc, b, 0, 1);
		EndPaint(hWnd, &ps);
	}
	break;
	}
	return 0;
}

