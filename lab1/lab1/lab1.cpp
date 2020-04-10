#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iterator>
#define window_size 80
using namespace std;
vector <string> vec;
void printspace(int i)
{
	for (int k = 0; k < i; k++) cout << " ";
}
void print(int symnum, const char * file)
{
	ofstream stream;
	int len;
	int acc=0;
	int space = (window_size - symnum) / 2;
	stream.open(file);
	printspace(space);
	for (const auto &i:vec)
	{
		len = i.length();
		acc += len+1;
		if ((acc <= symnum + 1) && (i != "\n"))
		{
			cout << i << " ";
			stream << i << " ";
		}
		else if (len > symnum)
			{
				while (len > symnum)
				{
					for (int k = 0; k < symnum; k++)
					{
						cout << i[k];
						stream << i[k];
					}
					cout << endl;
					stream << endl;
					len -= symnum;
					printspace(space);
				}
				for (int k = 0; k < len; k++)
				{
					cout << i[k];
					stream << i[k];
				}
				cout << " ";
				stream << " ";
				acc = 0;
			}
			else
			{
				cout << endl;
				stream << endl;
				printspace(space);
				if (i != "\n")
				{
					cout << i << " ";
					stream << i << " ";
					acc = len + 1;
				}
				else acc = 0;
			}
		}
	cout << endl;
	stream << endl;
	stream.close();
}
void split(string line) 
{
	stringstream ss(line); //делаем поток ввода из строки
	copy //функция
 	(
		istream_iterator<string>(ss), //копирует элемент из диапазона [(ss)..())
		istream_iterator<string>(),
		back_inserter(vec) //кладет его в конец. 3 аргумент - начало целевого диапазона
	);
	vec.push_back("\n");
}
void scan(const char * file, int symnum)
{
	ifstream stream;
	string str;
	stream.open(file);
	while (getline(stream, str)) split(str);
	stream.close();
} 
int main(int argc, char const*argv[])
{
	stringstream ss;
	int symnum;
	if (argc != 4)
	{
		cout << "ERROR\n";
		return -1;
	}
	else
	{
		ss << argv[1]; //так на хабре написано
		ss >> symnum;
		scan(argv[2], symnum);
		print(symnum, argv[3]);
	}
	return 0;
}