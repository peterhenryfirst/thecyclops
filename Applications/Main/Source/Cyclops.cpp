//---------------------------------------------------------------------------
// Cyclops.cpp
//---------------------------------------------------------------------------

/**
 * @file Cyclops.cpp
 * 
 * Contains the start point of the Cyclops program.
 * TODO: We need to use a memory leak detector.
 * 
 * For a specific configuration and platform, we use different main.
 * 
 * @author Pedro Pereira
 * @date June, 2016
*/

#ifdef _DEBUG
//VLD is an example of memory leak detector. We need something similar.
#define _VISUALLEAKDETECTOR

#ifdef _VISUALLEAKDETECTOR
#include <vld.h>
#endif _VISUALLEAKDETECTOR

//Code to check on Windows if exists memory leaks.
//Comment it to disable
//#define _LEAKDETECTOR

#if (!defined _VISUALLEAKDETECTOR) && (defined _LEAKDETECTOR) && (defined _WIN32)
#include <crtdbg.h>
#include <assert.h>
#endif // _LEAKDETECTOR && _WIN32

#endif // _DEBUG


#include "Application/CyclopsApplication.h"

#if (defined _DEBUG) || !(defined _WIN32)
int main(int __argc, char **__argv) {

	int paramsCount = 0;
	paramsCount = __argc;

	std::string levelToLoad;

	if(__argc == 2) {
		levelToLoad = __argv[1];
	}

#if (!defined _VISUALLEAKDETECTOR) && (defined _LEAKDETECTOR)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetBreakAlloc(-1);
#endif
#else
// Windows
// ...
#endif // (defined _DEBUG) || !(defined _WIN32)

	//Here we launch the application
	{
		//*
		Application::CCyclopsApplication miApp;

		//send to init function a param with the level to load.

		if(miApp.init(levelToLoad)) {
			printf( "Run!\n" );
			//miApp.run();
		}

		miApp.release();
		/**/
	}

	return 0;

} // main
