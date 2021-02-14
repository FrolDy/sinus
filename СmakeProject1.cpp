// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "CMakeProject1.h"
#include <fstream>
#define S_RATE  (44100)
#define BUF_SIZE (S_RATE*2)
using namespace std;

int main()
{
	int i;
	float t;
	int16_t buffer[BUF_SIZE];
	float amplitude = 32000;
	
	float freq_Hz = 1000;
	float phase = 0;
	ofstream test;
	test.open("D:\\test.pcm");
	for (i = 0; i < BUF_SIZE; i++)
	{
		
		buffer[i] = (int)(amplitude * sin((float)(2 * 3.14 * i * freq_Hz / S_RATE)));
		test <<hex<< buffer[i];
		cout <<hex<< buffer[i] << endl;
	}
	
	return 0;
}
