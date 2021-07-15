/*
	ArtyK's Console (Game) Engine. Console engine for apps and games
	Copyright (C) 2021  Artemii Kozhemiak

	https://github.com/SuperArtyK/artyks-engine

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License 3.0 as published
	by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License 3.0 for more details.

	You should have received a copy of the GNU General Public License 3.0
	along with this program.  If not, see <https://www.gnu.org/licenses/gpl-3.0.txt>.
*/

/** @file main.cpp
 *  This file is the main file of the engine, has main().  
 *  Should not cause everything to break.  
 */

#pragma comment(lib, "winmm.lib")

#if __cplusplus == 199711L
#pragma message("It looks like you didn't set the /Zc:__cplusplus switch, so your __cplusplus will always be \'199711L\' no matter what standard you use\nit's advisable you set it")
#else
#if __cplusplus <= 201702L
#error "C++ is not of standard of 2017 or higher! Set the standard to it!" 
#else
#pragma message("Your c++ standard is c++17 or higher, that's a good sign!")
#endif // __cplusplus <= 201702L
#endif // __cplusplus == 199711L

#ifndef UNICODE
#error It looks like you are not using unicode in your project/solution, please fix that
#endif // !#define UNICODE


#include "include_engine.hpp"
#include "AEGraphic.hpp"
using namespace std;


void benchmark();

int main()
{
	artyk::init_main(false, false, false);

	//USE_FAST_PIPE_IF_AVAILABLE();
//your code goes below...
	int i = 0;
	int previ = 0;
	auto timestart = std::chrono::system_clock::now();
	auto timeend = std::chrono::system_clock::now();
	float fElapsedTime;
	int fps = 0, maxfps = fps, minfps = INT_MAX;
	AEBeep mybp;
	AEScreen myscr;
	AEKeyboard mykb;
	myscr.setcolor_con(artyk::color::DEF_BGR, artyk::color::DEF_FGR);
	short screenx = 320, screeny = 240;
	AEFrame myfr;
	AEGraphic mygx(screenx, screeny,1,1);
	int posx = 0,posy = 0;
	using artyk::utils::rand;
	for (;;) {
		i++;
		mygx.fill(rand() % screenx, rand() % screeny, rand()% screenx, rand()%screeny, '#',rand());
		
		//mygx.drawscreen();
		timeend = std::chrono::system_clock::now();
		fElapsedTime = std::chrono::duration<float>(timeend - timestart).count();
			
		if (fElapsedTime > 1.0f) {
			fps = i - previ;
			if (fps > maxfps) maxfps = fps;
			if (fps < minfps) minfps = fps;
			previ = i;
			timestart = timeend;
			//mybp.makesound_async(660, 200);
			myscr.settitle("GFX FPS: "+ to_string(AEGraphic::getfps())+"|GAME FPS: "+to_string(fps)+"|Time Since start : " + to_string(global_timer.getworldtime()) + " "+to_string(posx) + " "+to_string(posy));
			
		}
		//_getch();
		
		
	
	}

	



	artyk::closing_app = 1;

	if (artyk::closing_app) {
		AELog mylog;
		mylog.writetolog("Closed the \"" + artyk::app_name + "\". Version: " + artyk::app_version + " Build: " + to_string(artyk::app_build), LOG_INFO);
	}
	//cout << "\nPress enter to continue . . .\n";
	std::cin.get();
	//cout << "Exiting. . .\n";
	return 0;
}




#ifdef AE_EXPERIMENTAL
void benchmark() {

	__AEBaseClass mybc("BaseClass", 1);
	mybc.benchmark();

	AEBeep mybp(true, false);
	mybp.benchmark();
	//
	AEKeyboard mykb(true, false);
	mykb.benchmark();
	//
	AELog mylog;
	mylog.benchmark();
	//
	AEScreen myscr(true, false);
	myscr.benchmark();
	//
	AETimer mytime(-1);
	mytime.benchmark();
	//
	global_timer.benchmark();


}
#endif // AE_EXPERIMENTAL