// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "CMakeProject1.h"
#include <fstream>
#include <iostream>
#include <cmath>
#define S_RATE  (8000)
#define BUF_SIZE (S_RATE*2)
using namespace std;
const double PI = 3.14159265359;
int main()
{
	int i;
	float t;
	int16_t buffer[BUF_SIZE];
	float amplitude = 32000;
	
	float freq_Hz = 100;
	float phase = 0;
	ofstream test;
	test.open("test.pcm");
	for (i = 0; i < BUF_SIZE; i++)
	{
		
		buffer[i] = (int)(amplitude * sin((float)(2 * PI * i * freq_Hz / S_RATE)));
		int buf = buffer[i] % 256;
		buffer[i] -= buf;
		buffer[i] /= 256;

		unsigned char a = (unsigned char)buf;
		unsigned char b = (unsigned char)buffer[i];

		test << a << b;
		cout << a << b << endl;
	}
	
	return 0;
}
