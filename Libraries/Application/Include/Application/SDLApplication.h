//---------------------------------------------------------------------------
// SDLApplication.h
//---------------------------------------------------------------------------

/**
 * @file SDLApplication.h
 * 
 * Contains the class declaration for SDL apps. Manage the execution of all 
 * game.
 * 
 * @see Application::CSDLApplication
 * @see Application::CBaseApplication
 * 
 * @author Pedro Pereira
 * @date July, 2016
 */

#ifndef __Application_SDLApplication_H
#define __Application_SDLApplication_H

//#include "BaseApplication.h"

// Predeclaración de clases para ahorrar tiempo de compilación
/*
namespace Application {
	class CApplicationState;
}
namespace Graphics {
	class CServer;
}
namespace Ogre {
	class Timer;
}
*/

namespace Application {
	/**
	 * CSDLApplication class, contains the management of the entire aplication
	 * game. Extends from CBaseApplication and its state machine to manage the
	 * tasks to draw the scene with SDL library.
	 * 
	 * @ingroup applicationGroup
	 * 
	 * @author Pedro Pereira
	 * @date July, 2016
	 */
	//class CSDLApplication : public CBaseApplication {
	class CSDLApplication {
	public:
		/**
		 * Class constructor.
		 */
		CSDLApplication();

		/**
		 * Class destructor.
		 */
		virtual ~CSDLApplication();

		/**
		 * Initialize the application.
		 * 
		 * @return false if the initilization failed.
		 */
		virtual bool init();

        /**
		 * Finalize the application, free up the used resources.
		 */
		virtual void release();

		/**
		 * @see BaseApplication's lockInput(bool)
		 */
		//virtual void lockInput(bool lock = true);

	protected:

		/**
		 * Function to execute the application main loop.
		 * 
		 * @param msecs Num of miliseconds elapsed from the last call (or from 
		 * the activation of the application).
		 */
		//virtual void tick(unsigned int msecs);

	}; // class CSDLApplication

} // namespace Application

#endif // __Application_SDLApplication_H
