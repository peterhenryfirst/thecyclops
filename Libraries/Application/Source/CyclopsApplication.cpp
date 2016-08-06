//---------------------------------------------------------------------------
// CyclopsApplication.cpp
//---------------------------------------------------------------------------

/**
 * @file CyclopsApplication.cpp
 * 
 * Contains the implementation of the class application.
 * This class manage the execution of all the game.
 * 
 * @see Application::CCyclopsApplication
 * @see Application::CSDLApplication
 * 
 * @author Pedro Pereira
 * @date June, 2016
*/
#include "Application/CyclopsApplication.h"

/*
#include "ExitState.h"
#include "MenuState.h"
#include "GameState.h"
#include "LoadingState.h"
*/

namespace Application {

	//CGaleonApplication::CGaleonApplication() : C3DApplication() {
	CCyclopsApplication::CCyclopsApplication() : CSDLApplication() {

	} // CCyclopsApplication

	//--------------------------------------------------------

	CCyclopsApplication::~CCyclopsApplication() {

	} // ~CCyclopsApplication

	//--------------------------------------------------------

	bool CCyclopsApplication::init(const std::string levelToLoad) {
	    
		//receive the level to load and only charge a unique game state, that it
		//will change with new levels.
		//it is possible to load the exitstate too, because we need to exit the
		//application correctly.
		
		//if we receive a level from param, send that string to the add state to
		//load.

		//In the future we use this functionality to load the initial menu level
		//and later we need to charge other levels from the game play (lua or a 
		//component).

		//if we do not receive the level to load, we need to look up for the
		//initial level to load in the lua configuration.
		
		printf("Try to initilize SDL Application");
		
		// Init the base class.
		if(!CSDLApplication::init()) {
			return false;
		}

        //We create the states. The app is responsible to delete that states.
        /*
		if(!addState("menu", new CMenuState(this))) {
			return false;
		}

		if(!addState("loading", new CLoadingState(this))) {
			return false;
		}

		if(!addState("game", new CGameState(this, levelToLoad))) {
			return false;
		}

		if(!addState("exit", new CExitState(this))) {
			return false;
		}

		if(!setState("game")) {
			return false;
		}
		*/

		return true;

	} // init

	//--------------------------------------------------------

	void CCyclopsApplication::release() {
	    //Disable and delete all states.
	    
		//releaseAllStates();
		
		CSDLApplication::release();

	} // release

} // namespace Application
