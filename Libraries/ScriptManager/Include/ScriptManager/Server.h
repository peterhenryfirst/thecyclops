//---------------------------------------------------------------------------
// Server.h
//---------------------------------------------------------------------------

/**
* @file Server.h
* 
* TODO: comments
* 
* 
* @author Pedro Pereira
* @date September, 2017
*/

#ifndef __ScriptManager_Server_H
#define __ScriptManager_Server_H

#include "duktape.h"

namespace ScriptManager {
    class CServer;
}  

namespace ScriptManager {
    class CServer {
    public:

        /**
		Devuelve la única instancia de la clase CServer.

		@return Única instancia de la clase CServer.
		*/
		static CServer *getSingletonPtr();
        
         /**
		Inicializa la instancia

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool init();
        
        /**
         * Finalize the application, free up the used resources and destroy the
         * states created.
         */
        static void release();

        /**
         * Execute basic duktape test
         */
        void test();

    protected:
        /**
        * Class constructor.
        */
        CServer();

        /**
        * Class destructor.
        */
        ~CServer();

        duk_context *_ctx;

    private:

        /**
		 * Unique instance of the application.
		 */
		static CServer *_instance;

    }; // class CServer

} // namespace ScriptManager

#endif // __ScriptManager_Server_H
