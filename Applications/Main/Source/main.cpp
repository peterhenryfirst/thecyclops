/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL OpenGL, standard IO, and, strings
#include <SDL.h>
#include <SDL_opengl.h>
//#include <GL\GLU.h>
#include <GL\GLU.h>
#include <stdio.h>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matrices and clear color
bool initGL();

//Input handler
void handleKeys( unsigned char key, int x, int y );

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

void loop ();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Use OpenGL 2.1
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create context
			gContext = SDL_GL_CreateContext( gWindow );
			if( gContext == NULL )
			{
				printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Use Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 )
				{
					printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
				}

				//Initialize OpenGL
				if( !initGL() )
				{
					printf( "Unable to initialize OpenGL!\n" );
					success = false;
				}
			}
		}
	}

	return success;
}

bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	//Initialize Projection Matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	
	//Check for error
	error = glGetError();
	if( error != GL_NO_ERROR )
	{
		printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		success = false;
	}

	//Initialize Modelview Matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	//Check for error
	error = glGetError();
	if( error != GL_NO_ERROR )
	{
		printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		success = false;
	}
	
	//Initialize clear color
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	
	//Check for error
	error = glGetError();
	if( error != GL_NO_ERROR )
	{
		printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		success = false;
	}
	
	return success;
}

void handleKeys( unsigned char key, int x, int y )
{
	//Toggle quad
	if( key == 'q' )
	{
		gRenderQuad = !gRenderQuad;
	}
}

void update()
{
	//No per frame update needed
}

void render()
{
	//Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT );
	
	//Render quad
	if( gRenderQuad )
	{
		glBegin( GL_QUADS );
			glVertex2f( -0.5f, -0.5f );
			glVertex2f( 0.5f, -0.5f );
			glVertex2f( 0.5f, 0.5f );
			glVertex2f( -0.5f, 0.5f );
		glEnd();
	}
}

void close()
{
	//Destroy window	
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;
		
		//Enable text input
		SDL_StartTextInput();

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				//Handle keypress with current mouse position
				else if( e.type == SDL_TEXTINPUT )
				{
					int x = 0, y = 0;
					SDL_GetMouseState( &x, &y );
					handleKeys( e.text.text[ 0 ], x, y );
				}
			}

			//Render quad
			render();
			
			//Update screen
			SDL_GL_SwapWindow( gWindow );
		}
		
		//Disable text input
		SDL_StopTextInput();
	}

	//Free resources and close SDL
	close();

	return 0;
}

/*
#include "Math/vector3.hpp"
#include <stdio.h>

int main(int argc, char *argv[])
{
    float x;
    Math::Vector3f {x, 11, 13.1};
    
    printf( "Hello World" );

    return 0;
}
*/

/*
#include <iostream>
#include <SDL.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#elif __EMSCRIPTEN__
#include <GLES2/gl2.h>
#include "emscripten.h"
#elif WIN32
#include <GL/glew.h>
// WTF
#ifdef main
#undef main
#endif
#endif


GLuint load_shader (GLenum type, const char* shader_src) {
    auto shader = glCreateShader(type);
    GLint compiled;
    
    if (shader == 0) {
        return 0;
    }
    
    glShaderSource(shader, 1, &shader_src, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    
    if (!compiled) {
        GLint info_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);
        if (info_length > 1) {
            auto info_log = static_cast<char*>(malloc(sizeof(char) * info_length));
            glGetShaderInfoLog(shader, info_length, nullptr, info_log);
            std::cerr << "Error compiling shader:\n" << shader_src << "\n" <<
            info_log << std::endl;
            free(info_log);
        }
    }
    
    return shader;
}

GLuint load_program () {
    const char* vShaderStr =
        "attribute vec4 aPosition;\n"
        "void main () {\n"
        "  gl_Position = aPosition;\n"
        "}";
    const char* fShaderStr =
#ifdef __EMSCRIPTEN__
        "precision mediump float;\n"
#endif
        "void main () {\n"
        "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}";
    // TODO: error handling
    GLuint vertexShader = load_shader(GL_VERTEX_SHADER, vShaderStr);
    GLuint fragmentShader = load_shader(GL_FRAGMENT_SHADER, fShaderStr);
    GLuint program = glCreateProgram();
    if (program == 0) {
        return 0;
    }
    
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    
    glBindAttribLocation(program, 0, "aPosition");
    glLinkProgram(program);
    
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked) {
        GLint info_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length);
        if (info_length > 1) {
            auto info_log = static_cast<char*>(malloc(sizeof(char*) * info_length));
            glGetProgramInfoLog(program, info_length, nullptr, info_log);
            std::cerr << "Error linking program: " << info_log << std::endl;
            free(info_log);
        }
        glDeleteProgram(program);
        return GL_FALSE;
    }
    glUseProgram(program);
    glViewport(0, 0, 640, 480);
    
    return GL_TRUE;
}

void load_buffers () {
    GLfloat vertices [] = {
        0.0f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    
    GLuint vertexPosObj;
    glGenBuffers(1, &vertexPosObj);
    glBindBuffer(GL_ARRAY_BUFFER, vertexPosObj);
    glBufferData(GL_ARRAY_BUFFER, 9 * 4, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

void draw () {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void loop () {
    draw();
}

struct SDL {
    SDL () {
        if ((SDL_Init(SDL_INIT_VIDEO)) != 0) {
            throw std::string("Unable to initialize SDL: ") + std::string(SDL_GetError());
        }
    }
    ~SDL () {
        SDL_Quit();
    }
};

struct Win {
    SDL_Window* const mWin;
    Win (): mWin(SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)) {
        if (mWin == nullptr) {
            throw std::string("Unable to create a window: " + std::string(SDL_GetError()));
        }
    }
    ~Win () {
        if (mWin) SDL_DestroyWindow(mWin);
    }
    void swapBuffers () {
        SDL_GL_SwapWindow(mWin);
    }
};

struct GL {
    SDL_GLContext mgl;
    GL (const Win& win) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetSwapInterval(1);
        mgl = SDL_GL_CreateContext(win.mWin);
        if (mgl == nullptr) {
            throw std::string("Unable to create GL Context: ") + std::string(SDL_GetError());
        }
    }
    ~GL () {
        if (mgl) SDL_GL_DeleteContext(mgl);
    }
};

int main () {
    SDL sdl;
    Win win;
    GL gl(win);
    
    // TODO: Error handling
    load_program();
    load_buffers();
    
    glClearColor (0.0, 1.0, 0.0, 1.0);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 0);
#else
    bool run = true;
    SDL_Event e;
    while (run) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                run = false;
            }
        }
        loop();
        win.swapBuffers();
    }
#endif
    return 0;
}

*/

/*
#include <stdio.h>
//#include <SDL2/SDL.h>
#include <SDL.h>
#include <assert.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window * window;
SDL_Renderer * renderer;

void render_func(void) {
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, 0, 0, 640, 320);
    SDL_RenderPresent(renderer);

#ifdef EMSCRIPTEN
    emscripten_cancel_main_loop();
#endif
}

int main(int argc, char* argv[])
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);
    SDL_CreateWindowAndRenderer(640, 320, 0, &window, &renderer);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(render_func, 60, 1);
#else
    render_func();
#endif

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
*/