//---------------------------------------------------------------------------
// BaseApplication.h
//---------------------------------------------------------------------------

/**
 * @file BaseApplication.h
 * 
 * Contains the class declaration for Apps Class. Manage the execution of all 
 * game.
 * 
 * @see Application::CBaseApplication
 * @see Application::CApplicationState
 * 
 * @author Pedro Pereira
 * @date July, 2016
 */

#ifndef __Application_BaseApplication_H
#define __Application_BaseApplication_H

//#include "GUI/InputManager.h"

#include <map>
#include <string>
#include <cassert>

//Class's Predeclaration to save compilation time.
namespace Application {
	class CApplicationState;
	class IClock;
}


/**
 * Namespace with everything related to the app: abstract class, states, etc. It
 * is the game's hearth, responsible to initialize all the systems needed to
 * execute the game (see @ref applicationGroup to more information).
 * 
 * @author Pedro Pereira
 * @date July, 2016
*/
namespace Application {
	/**
	 * CBaseApplication Class contains the application game control, that
	 * implements an app state machine.
	 * 
	 * The classes that inheritance fromn this should initialize the subsystems
	 * needed to that concrete application (graphic subsystem, etc.). As well as
	 * the state's creation that make up the application.
	 * 
	 * @remarks The classes that implements this class <em>must</em> initialize
	 * the clock (_clock).
	 * 
	 * @ingroup applicationGroup
	 * 
	 * @author Pedro Pereira
	 * @date July, 2016
	 */
	//class CBaseApplication : public GUI::CKeyboardListener,
	//	public GUI::CMouseListener {
	class CBaseApplication {
	public:
		/**
		 * Class constructor.
		 */
		CBaseApplication();

		/**
		 * Class destructor.
		 */
		virtual ~CBaseApplication();

		/**
		 * Return the application instance. Implements the singleton pattern,
		 * but through the constructor, must do a explicit <code>new</code> (or
		 * declare a globalor or local variable; without doubt to call the
		 * constructor of the class). That created object will be returned
		 * by this method.
		 * 
		 * @return The instance application pointer.
		 */
		static CBaseApplication *getSingletonPtr() {
			return _instance;
		}

		/**
		 * Initialize the application. At debug time, the appplication should be 
		 * initialized only one.
		 * 
		 * @return false if the initialization has failed.
		*/
		virtual bool init();

		/**
		 * Finalize the application, free up all resources. At debug time, the
		 * application should be initialized.
		 */
		virtual void release();

		/**
		 * Free up and remove all app states.
		 */
		virtual void releaseAllStates();

		/**
		 * Function to execute the application. The main loop is executed here,
		 * that it is repeated until someone request to end up. A transition 
		 * state is only checked in the loop, and if so the transition becomes
		 * effective. After that, tick() function is called to update de loop.
		 */
		virtual void run();

		/**
		 * This function is called when someone outside the application (usually
		 * a state) want to finalize the epplication. This function is conceived
		 * to be called while the run() method is in execution. At the end of
		 * the actual loop, the application will be terminated.
		 */
		void exitRequest() {
			_exit = true;
		}

		/**
		 * Function to look up if someone has requested to finalize the
		 * application.
		 * 
		 * @return true if the application should finalize at the end of the 
		 * actual loop.
		 */
		bool exitRequested() {
			return _exit;
		}

		// METHODS RELATED TO THE STATES
		//------------------------------

		/**
		 * Add an state to the application. The application accepts the
		 * responsibility to remove the state at the end of the application.
		 * 
		 * @param name State's name.
		 * @param newState State to add. The application will be responsible
		 * to remove at the end.
		 * @return true if everything is fine.
		*/
		bool addState(const std::string &name,
		              CApplicationState *newState);

		/**
		 * The function sets the state to the application, from its name. The
		 * action is <em>not</em> immediately, in the next main loop back of the
		 * application will be fulfilled.
		 * 
		 * @param name State's name.
		 * @return true if the state exist. If the state do not exist, do
		 * <em>not</em> have the state's change effectively.
		 */
		bool setState(const std::string &name);

		/**
		 * Return the application's actual state.
		 * 
		 * @return The application's actual state.
		 */
		CApplicationState *getState() {
			return _currentState;
		}
		
		//------------------------------

		/**
		 * Return the application's time.
		 * 
		 * @return The application's time takes active.
		 */
		unsigned int getAppTime();

        // METHODS RELATED TO CKeyboardListener
        //-------------------------------------

		/**
		 * Function to be invoked allways a key is pushed. The application
		 * notifies this event to the current state.
		 * 
		 * @param key Pushed key's code.
		 * @return true if the event has been processed. In this case the 
		 * manager does not call to other listeners.
		 */
		virtual bool keyPressed(GUI::TKey key);

		/**
		 * Function to be invoked allways after a key pushed is finished. The
		 * application notifies this event to the current state.
		 * 
		 * @param key Pushed key's code.
		 * @return true if the event has been processed. In this case the 
		 * manager does not call to other listeners.
		 */
		virtual bool keyReleased(GUI::TKey key);

        //-------------------------------------
        
        //METHODS RELATED TO CMouseListener
        //-------------------------------------

		/**
		 * Function to be invoked allways after a mouse movement. The
		 * application notifies this event to the current state.
		 * 
		 * @param mouseState The mouse state when the event is launched.
		 * @return true if the event has been processed. In this case the 
		 * manager does not call to other listeners.
		 */
		virtual bool mouseMoved(const GUI::CMouseState &mouseState);

		/**
		 * Function to be invoked allways a buttons is pushed. The application
		 * notifies this event to the current state.
		 * 
		 * @param mouseState The mouse state when the event is launched.
		 * @return true if the event has been processed. In this case the
		 * manager does not call to other listeners.
		 */
		virtual bool mousePressed(const GUI::CMouseState &mouseState);

		/**
		 * Function to be invoked allways after a button pushed is finished. The
		 * application notifies this event to the current state.
		 * 
		 * @param mouseState The mouse state when the event is launched.
		 * @return true if the event has been processed. In this case the
		 * manager does not call to other listeners.
		 */
		virtual bool mouseReleased(const GUI::CMouseState &mouseState);
		
		//-------------------------------------
		
		/**
		 * Sometimes, like when playing a cutscene, we will need to lock every
		 * input the game may receive from the user so no interaction can be
		 * performed.
		 * With this method, we have to make sure nothing gets input and call
		 * the necessary methods to deselect everything which was selected,
		 * storing them somewhere for further restoring.
		 * We can also use this method to unlock input, enabling back every
		 * input and restoring anything important we stored during locking.
		 */
		virtual void lockInput(bool lock = true);

		/**
		 * Load a new level from somewhere in the level.
		 * 
		 * @param levelName The descriptive level name to load.
		 */
		virtual void loadNewLevel(const std::string &levelName);

		/**
		 * Return the minimum tick duration is allowed
		 */
		unsigned int getMinimumTick() {
			return _minimumTick;
		}

		/**
		 * Set the minimum tick duration is allowed
		 */
		void setMinimuyTick(unsigned int minimumTick) {
			_minimumTick = minimumTick;
		}
	
	protected:

		/**
		 * Make a state change, notifies to the outgoing state and incoming
		 * state of this change.
		 */
		void changeState();

		/**
		 * Function to execute an application's main loop.
		 * 
		 * @param msecs Number of milliseconds elapsed from the last call (or 
		 * from the activation of the application, incase of the first time...).
		 */
		virtual void tick(unsigned int msecs);

		/**
		 * Unique instance of the application.
		 */
		static CBaseApplication *_instance;

		/**
		 * Suggest if the application has been initialized.
		 */
		bool _initialized;

		/**
		 * Data type: States table. It is a STL's hash table.
		 */
		typedef std::map<std::string, CApplicationState *> TStateTable;

		/**
		 * Hash table with all application's states.
		 */
		TStateTable _states;

		/**
		 * Actual state pointer.
		 */
		CApplicationState *_currentState;

		/**
		 * Objective state pointer. Someone, outside of the application, has
		 * requested a state change that still it has not been effective.
		 */
		CApplicationState *_nextState;

		/**
		 * Suggest if the application will end at the finish of the actual loop.
		 */
		bool _exit;

		/**
		 * Timer that keeps the time from the application's started.
		 */
		IClock *_clock;

		/**
		 * Whether or not the input is currently locked.
		 */
		bool _inputLocked;

		/**
		 * Minimum value of time between ticks.
		 */
		unsigned int _minimumTick;
	}; // class BaseApplication

} // namespace Application

#endif // __Application_BaseApplication_H
