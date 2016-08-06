//---------------------------------------------------------------------------
// BaseApplication.cpp
//---------------------------------------------------------------------------

/**
 * @file BaseApplication.cpp
 * 
 * Contains the implementation of the class application, that manage the 
 * execution of the game.
 * 
 * @see Application::CBaseApplication
 * @see Application::CApplicationState
 * 
 * @author Pedro Pereira
 * @date July, 2016
*/

#include "BaseApplication.h"
#include "ApplicationState.h"
#include "Clock.h"

//#include "ScriptManager/ScriptManager.h"
//#include "Application/ScriptDataPublisher/Publisher.h"

#include <assert.h>

namespace Application {

	CBaseApplication *CBaseApplication::_instance = 0;

	CBaseApplication::CBaseApplication() :
		_initialized(false),
		_currentState(0),
		_nextState(0),
		_exit(false),
		_clock(0),
		_minimumTick(13),
		_inputLocked(false) {
		assert(!_instance && "It can not create more than one application");

		_instance = this;
	} // CBaseApplication

	//--------------------------------------------------------

	CBaseApplication::~CBaseApplication() {
		_instance = 0;
	} // ~CBaseApplication

	//--------------------------------------------------------

	bool CBaseApplication::init() {
		assert(!_initialized && "The application is already initialized");
		_initialized = true;
		/*
		// export this project's necessary data to Lua
		ScriptDataPublisher::CPublisher::registerData(
		    ScriptManager::CScriptManager::getSingletonPtr()->getCurrentLuaState());
	   */

		return true;
	} // init

	//--------------------------------------------------------

	void CBaseApplication::release() {
		assert(_initialized && "The application is not initialized");
		//Disable and remove all states.
		releaseAllStates();
		_initialized = false;
	} // release

	//--------------------------------------------------------

	void CBaseApplication::releaseAllStates() {
	    //Disable the current state
		if(_currentState) {
			_currentState->deactivate();
			_currentState = 0;
		}

        //Remove the states
		TStateTable::const_iterator it, end;

		for(it = _states.begin(), end = _states.end();
		    it != end; ++it) {
			it->second->release();
			delete it->second;
		}

		_states.clear();
	} // releaseAllStates

	//--------------------------------------------------------

	bool CBaseApplication::addState(const std::string &name,
	                                CApplicationState *newState) {
		TStateTable::const_iterator it;
#ifdef _DEBUG
        /*
         * Check if the state do not exist with this name.
         * 
         * Another possibility is not do in Debug, but allways, and in case if
         * exist, remove it (because the application accepts the charge to 
         * remove the states that it contains).
         * 
         * However, in that case would be check that it is not the current
         * state, nor the next state that it is expeted to go...
         * 
         */
		it = _states.find(name);
		assert(it == _states.end());
#endif
		_states[name] = newState;
		return newState->init();
	} // addState

	//--------------------------------------------------------

	bool CBaseApplication::setState(const std::string &name) {
	    //Look up the state
		TStateTable::const_iterator it;
		it = _states.find(name);

		//If not exist an state with that name, nothing to do.
		if(it == _states.end()) {
			return false;
		}

		_nextState = it->second;
		return true;
	} // setState

	//--------------------------------------------------------

	void CBaseApplication::run() {
		assert(_clock && "You are sure have created a clock in the class init of your application!");
		//Update the time, the first time, before starting, to the first 
		//frame have a reasonable frame time.
		_clock->updateTime();
		unsigned int timer = 0;

        //Execution the main loop. Only look if it is needed to make a state's
        //transition, and if not needed, execute the loop.
		while(!exitRequested()) {
			if(!_currentState ||
			   (_nextState && (_currentState != _nextState))) {
				changeState();
			}

			_clock->updateTime();
			timer += _clock->getLastFrameDuration();

			if(timer >= _minimumTick) {
				/*if(_clock->getLastFrameDuration() < _minimumTick) {
					tick(_minimumTick);
				} else {
			tick(_clock->getLastFrameDuration());
				}*/
				tick(timer);
				timer = 0;
		}
		}
	} // run

	//--------------------------------------------------------

	unsigned int CBaseApplication::getAppTime() {
		return _clock->getTime();
	} // getAppTime

	//--------------------------------------------------------

	void CBaseApplication::changeState() {
	    //Notify to the current state that it will go to remove.
		if(_currentState) {
			_currentState->deactivate();
		}

		assert(_nextState);
		_nextState->activate();
		_currentState = _nextState;
	} // changeState

	//--------------------------------------------------------

	void CBaseApplication::tick(unsigned int msecs) {
	    /**
	     * Apparently this function is simple. Here, it can add another common
	     * calls to all application's states.
	     * 
	     * This method is virtual, if a concrete application identify a common
	     * things to all the states, it can add in the implementation of that
	     * method.
	     */
		if (_currentState){
			_currentState->tick(msecs);
		}
	} // tick

	//--------------------------------------------------------

	bool CBaseApplication::keyPressed(GUI::TKey key) {
		// Avisamos al estado actual de la pulsación.
		if(_currentState) {
			return _currentState->keyPressed(key);
		}

		return false;
	} // keyPressed

	//--------------------------------------------------------

	bool CBaseApplication::keyReleased(GUI::TKey key) {
		// Avisamos al estado actual del fin de la pulsación.
		if(_currentState) {
			return _currentState->keyReleased(key);
		}

		return false;
	} // keyReleased

	//--------------------------------------------------------

	bool CBaseApplication::mouseMoved(const GUI::CMouseState &mouseState) {
		// Avisamos al estado actual del movimiento.
		if(_currentState) {
			return _currentState->mouseMoved(mouseState);
		}

		return false;
	} // mouseMoved

	//--------------------------------------------------------

	bool CBaseApplication::mousePressed(const GUI::CMouseState &mouseState) {
		// Avisamos al estado actual de la pulsación.
		if(_currentState) {
			return _currentState->mousePressed(mouseState);
		}

		return false;
	} // mousePressed

	//--------------------------------------------------------


	bool CBaseApplication::mouseReleased(const GUI::CMouseState &mouseState) {
		// Avisamos al estado actual del fin de la pulsación.
		if(_currentState) {
			return _currentState->mouseReleased(mouseState);
		}

		return false;
	} // mouseReleased

	void CBaseApplication::lockInput(bool lock) {
		// child classes will use this flag
		_inputLocked = lock;

		// tell current state to lock/unlock
		if(_currentState) {
			_currentState->lockInput(lock);
		}
	}

	void CBaseApplication::loadNewLevel(const std::string &levelName) {
		//change to a new level to load with the loading state

		TStateTable::const_iterator it;
		it = _states.find("loading");

		if(it != _states.end()) {

			it->second->loadNewLevel(levelName);

			if(!setState("loading")) {
			}
		}


		/*
		if(_currentState) {
			_currentState->loadNewLevel(levelName);
		}
		/**/
	}

} // namespace Application
