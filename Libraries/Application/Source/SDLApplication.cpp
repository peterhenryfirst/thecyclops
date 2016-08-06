//---------------------------------------------------------------------------
// SDLApplication.cpp
//---------------------------------------------------------------------------

/**
 * @file SDLApplication.cpp
 * 
 * Contains the implementation of the class application to SDL apps. This class
 * manage the execution of all game.
 * 
 * @see Application::CSDLApplication
 * @see Application::CBaseApplication
 * @author Pedro Pereira
 * @date July, 2016
 */


//#include "OgreClock.h"
#include "Application/SDLApplication.h"
/*
#include "Graphics/Server.h"
#include "BaseSubsystems/Server.h"
#include "GUI/InputManager.h"
#include "GUI/Server.h"
#include "Logic/Server.h"
#include "Logic/Maps/ComponentFactory.h"
#include "Physics/Server.h"
#include "AI/Server.h"
#include "ScriptManager/ScriptManager.h"
#include "Configuration/Server.h"
#include "Audio/Server.h"
*/

#include <cassert>

#include <iostream>

namespace Application {

	//CSDLApplication::CSDLApplication() : CBaseApplication() {
	CSDLApplication::CSDLApplication() {

	} // CSDLApplication

	//--------------------------------------------------------

	CSDLApplication::~CSDLApplication() {

	} // ~CSDLApplication

	//--------------------------------------------------------

	bool CSDLApplication::init() {
	    /*
		if(!ScriptManager::CScriptManager::Init()) {
			return false;
		}

		// Inicializamos la clase base.
		if(!CBaseApplication::init()) {
			return false;
		}

		// Inicializamos los diferentes subsistemas, los de
		// Ogre entre ellos.
		if(!BaseSubsystems::CServer::Init()) {
			return false;
		}

		if(!Configuration::CServer::Init()) {
			return false;
		}

		// Inicializamos el servidor gráfico.
		if(!Graphics::CServer::Init()) {
			return false;
		}

		// Inicializamos el gestor de entrada de periféricos.
		if(!GUI::CInputManager::Init()) {
			return false;
		}

		// Nos registramos como oyentes de los eventos del teclado.
		GUI::CInputManager::getSingletonPtr()->addKeyListener(this);
		// Y como oyentes de los eventos del ratón.
		GUI::CInputManager::getSingletonPtr()->addMouseListener(this);

		// Inicializamos el servidor de interfaz con el usuario.
		if(!GUI::CServer::Init()) {
			return false;
		}

		// Inicialización del servidor de física.
		if(!Physics::CServer::Init()) {
			return false;
		}

		// Inicializamos el servidor de la lógica.
		if(!Logic::CServer::Init()) {
			return false;
		}

		// Init the AI server
		if(!AI::CServer::Init()) {
			return false;
		}

		// Init the Audio server
		if(!Audio::CServer::Init()) {
			return false;
		}

		// now that everything has been initialized, classes have been exported to Lua
		// and so on, we can finally execute base Lua script
		ScriptManager::CScriptManager::getSingletonPtr()->loadScripts();

		// Creamos el reloj basado en Ogre.
		_clock = new COgreClock();
        
        */
        
        printf("Initilize SDL Application!!");
        
		return true;

	} // init

	//--------------------------------------------------------

	void CSDLApplication::release() {
	    /*
		// Eliminamos el reloj de la aplicación.
		delete _clock;

		// Destruimos la factoría de componentes. La factoría
		// de componentes no es de construcción y destrucción explícita
		// debido a como se registran los componentes. Por ello Init y
		// Release no son simétricos.
		if(Logic::CComponentFactory::getSingletonPtr()) {
			delete Logic::CComponentFactory::getSingletonPtr();
		}

		if(Audio::CServer::getSingletonPtr()) {
			Audio::CServer::Release();
		}

		if(AI::CServer::getSingletonPtr()) {
			AI::CServer::Release();
		}

		if(Logic::CServer::getSingletonPtr()) {
			Logic::CServer::Release();
		}

		// Liberar los recursos del servidor de física
		if(Physics::CServer::getSingletonPtr()) {
			Physics::CServer::Release();
		}

		if(GUI::CServer::getSingletonPtr()) {
			GUI::CServer::Release();
		}

		if(GUI::CInputManager::getSingletonPtr()) {
			// Dejamos de ser oyentes de los eventos del teclado.
			GUI::CInputManager::getSingletonPtr()->removeKeyListener(this);
			// Y de los eventos del ratón
			GUI::CInputManager::getSingletonPtr()->removeMouseListener(this);
			GUI::CInputManager::Release();
		}

		if(Graphics::CServer::getSingletonPtr()) {
			Graphics::CServer::Release();
		}

		if(Configuration::CServer::getSingletonPtr()) {
			Configuration::CServer::Release();
		}

		if(BaseSubsystems::CServer::getSingletonPtr()) {
			BaseSubsystems::CServer::Release();
		}

		CBaseApplication::release();

		if(ScriptManager::CScriptManager::getSingletonPtr()) {
			ScriptManager::CScriptManager::Release();
		}
		*/

	} // release

	//--------------------------------------------------------

    /*
	void CSDLApplication::tick(unsigned int msecs) {
		float secs = msecs / 1000.0f;

		CBaseApplication::tick(msecs);
		GUI::CInputManager::getSingletonPtr()->tick();
		Graphics::CServer::getSingletonPtr()->tick(secs);
		AI::CServer::getSingletonPtr()->tick(secs);
		Audio::CServer::getSingletonPtr()->tick(secs);
	} // tick

	void CSDLApplication::lockInput(bool lock) {
		CBaseApplication::lockInput(lock);

		// lock/unlock GUI server
		GUI::CServer::getSingletonPtr()->lockInput(lock);

		if(lock) {
			// stop listening for events
			GUI::CInputManager::getSingletonPtr()->removeMouseListener(this);
			GUI::CInputManager::getSingletonPtr()->removeKeyListener(this);
		} else {
			// start listening for events
			GUI::CInputManager::getSingletonPtr()->addMouseListener(this);
			GUI::CInputManager::getSingletonPtr()->addKeyListener(this);
		}
	}
	*/

} // namespace Application
