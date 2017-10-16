//---------------------------------------------------------------------------
// Server.cpp
//---------------------------------------------------------------------------

/**
 * @file Server.cpp
 * 
 * TODO: comments
 * 
 * @author Pedro Pereira
 * @date September, 2017
*/

#include "ScriptManager/Server.h"

#include <stdio.h>
#include <assert.h>

#include "duktape.h"

namespace ScriptManager {

	CServer *CServer::_instance = 0;

	CServer *CServer::getSingletonPtr() {
		assert(_instance && "Can't get ScriptManager's instance. It's not initialized.");
		return _instance;
	}

	CServer::CServer() : _ctx(0) {
		_instance = this;
	} // CServer

	//--------------------------------------------------------

	CServer::~CServer() {
		delete _instance;
		_instance = NULL;
	} // ~CServer

	//--------------------------------------------------------

	bool CServer::init() {
		assert(!_instance && "Segunda inicialización de ScriptManager::CServer no permitida!");

		new CServer();

		return true;

	} // init

	void CServer::release() {

	} // release

	void CServer::test() {
		printf("Try to run basic duktape test\n");
		
		_instance->_ctx = duk_create_heap_default();
    	duk_eval_string(_instance->_ctx, "1+2");
    	printf("1+2=%d\n", (int) duk_get_int(_instance->_ctx, -1));
    	duk_destroy_heap(_instance->_ctx);
	} 

} // namespace ScriptManager
