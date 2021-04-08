// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "CMakeProject1.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::vector;
using std::string;
using std::ios;

const float M_PI = 3.14159265359;

class SinusWave
{
	static void longWrite(long x, ofstream& myfile)
	{
		myfile << static_cast<uint8_t>(x & 0xff); 
		x >>= 8; // эквивалетно / 256
		myfile << static_cast<uint8_t>(x & 0xff);
		x >>= 8;
		myfile << static_cast<uint8_t>(x & 0xff);
		x >>= 8;
		myfile << static_cast<uint8_t>(x & 0xff);
	}

	static void integerWrite(unsigned int x, ofstream& myfile)
	{
		myfile << static_cast<uint8_t>(x & 0xff); 
		x >>= 8; 
		myfile << static_cast<uint8_t>(x & 0xff);
	}

	float Frequency; 
	float Duration; 
	float SampleRate; 
	float Volume; 

public:
	SinusWave(string FileName, float SampleRate, float Frequency, float Duration, float Volume) : Frequency{ Frequency },
		Duration{ Duration }, SampleRate{ SampleRate }, Volume{ Volume }
	{
		ofstream myfile;
		myfile.open(FileName.c_str(), ios::out | ios::binary);
		if (!myfile.is_open())
		{
			cout << "Error with opening file.\n";
			return;
		}
		long DataLeng = static_cast<long>(SampleRate* this->Duration);
		longWrite(DataLeng, myfile);
		for (float m = 0; m <= DataLeng; m++)
		{
			// harmonic wave formula
			// y(t) = A * sin(2 * PI * f * t )
			float result = this->Volume * sinf(2 * M_PI * this->Frequency * (m / SampleRate));
			integerWrite(static_cast<int>(result), myfile);
		}
		cout << "The wave has been successful generated in " << FileName << endl;
		myfile.close();
	}
	static void generateSin(string FileName, float SampleRate, float Frequency, float Duration, float Volume)
	{
		ofstream myfile;
		myfile.open(FileName.c_str(), ios::out | ios::binary);
		if (!myfile.is_open())
		{
			cout << "Error with opening file.\n";
			return;
		}
		long DataLeng = static_cast<long>(SampleRate * Duration);
		longWrite(DataLeng, myfile);
		for (float m = 0; m <= DataLeng; m++)
		{
			// harmonic wave formula
			// y(t) = A * sin(2 * PI * f * t )
			float result = Volume * sinf(2 * M_PI * Frequency * (m / SampleRate));
			integerWrite(static_cast<int>(result), myfile);
		}
		cout << "The wave has been successful generated in " << FileName << endl;
		myfile.close();
	}
};

int main(int argc, const char** argv)
{
	// parse args
	cout << "commands: \n"
		<< "-s 44100 -f 1000 -d 10 -v 32767\n";
	vector<string> args(argv, argv + argc);
	for (int i = 0; i < argc; i++)
		cout << "argument [" << i << "] : " << args[i] << endl;
	vector<string> commands{ "-fn","-s","-f","-d","-v" };

	// default values
	string filename = "MyTest.pcm";
	float sampleRate = 44100;
	float frequency = 1000;
	float duration = 10;
	float volume = 32767;

	if (argc != 1) // если мы имеем аргументы
	{
		string buf;
		for (auto& arg : args)
			buf += arg;
		int countCmd = std::count(buf.begin(), buf.end(), '-');
		int countArgs = argc - countCmd - 1;
		if ((countCmd == countArgs) <= 5)
		{
			// continue parse
			// parse from 1 index
			std::pair<string, string> keys;
			for (int i = 1; i < (countCmd + countArgs); i += 2)
			{
				// составляем пары (ключ + аргумент)
				keys = std::make_pair(args.at(i), args.at(i + 1));
				auto it = std::find(commands.begin(), commands.end(), keys.first);
				if (it != commands.end())
				{
					int foundIndex = it - commands.begin();
					switch (foundIndex)
					{
					case 0:
						filename = keys.second;
						break;
					case 1:
						sampleRate = std::stof(keys.second);
						break;
					case 2:
						frequency = std::stof(keys.second);
						break;
					case 3:
						duration = std::stof(keys.second);
						break;
					case 4:
						volume = std::stof(keys.second);
						break;
					}
				}
			}

		}
	}


	cout << "File name: " << filename << endl
		<< "Sample rate: " << sampleRate << endl
		<< "Frequency: " << frequency << endl
		<< "Duration: " << duration << endl
		<< "Volume: " << volume << endl;

	SinusWave::generateSin(filename, sampleRate, frequency, duration, volume);

	system("pause");
	return 0;
}
