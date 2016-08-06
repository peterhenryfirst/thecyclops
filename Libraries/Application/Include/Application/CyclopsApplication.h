//---------------------------------------------------------------------------
// CyclopsApplication.h
//---------------------------------------------------------------------------

/**
 * @file CyclopsApplication.h
 * 
 * Contains the class application declaration.
 * This class manage the execution of all the game.
 * 
 * @see Application::CCyclopsApplication
 * @see Application::CSDLApplication
 * 
 * @author Pedro Pereira
 * @date June, 2016
 */

#ifndef __Application_CyclopsApplication_H
#define __Application_CyclopsApplication_H

#include "SDLApplication.h"
//#include "GUI/InputManager.h"
#include <string>

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
	 * CCyclopsApplication class, extends from CSDLApplication to add the
	 * concrete states that needed to create the gameplay.
	 * 
	 * @ingroup applicationGroup
	 * 
	 * @author Pedro Pereira
	 * @date June, 2016
	 */
	class CCyclopsApplication : public CSDLApplication {
	public:
		/**
		 * Class constructor.
		 */
		CCyclopsApplication();

		/**
		 * Class destructor.
		 */
		virtual ~CCyclopsApplication();

		/**
		 * Initialize the application where we add the concrete states.
		 * 
		 * @return false if the initilization failed.
		 */
		virtual bool init(const std::string levelToLoad);

		/**
		 * Finalize the application, free up the used resources and destroy the
		 * states created.
		 */
		virtual void release();

	}; // class CCyclopsApplication

} // namespace Application

#endif // __Application_CyclopsApplication_H
