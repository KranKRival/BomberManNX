#ifndef INCLUDES_H_INCLUDED
#define INCLUDES_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#endif // INCLUDES_H_INCLUDED

/** \mainpage Introduction
 *
 * \section intro_sec Introduction
 *
 * Project name: Bomberman
 *
 * Authors: \n
 *  - Aleksandar Miletic
 *  - Mirko Brkusanin
 *
 * Description: Clone of Bomberman game in C++ using SDL2
 *
 * Source code:
 *  - <a href="https://github.com/MATF-RS16/rs16-14">Download from GitHub</a>
 * .
 * Documentation: \n
 *  - html version: <a href="http://alas.matf.bg.ac.rs/~mi13211/bomberman/">alas.matf.bg.ac.rs/~mi13211/bomberman/</a>  \n
 *  - pdf version : <a href="http://alas.matf.bg.ac.rs/~mi13211/Bomberman.pdf">alas.matf.bg.ac.rs/~mi13211/Bomberman.pdf</a> \n
 * .
 * Executables for Microsoft Windows OS:
 *  - <a href="http://alas.matf.bg.ac.rs/~mi13211/Bomberman.rar">Download link</a>
 * .
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Setting up SDL2
 *
 * For compiling this code you will need the following libraries: \n
 * Note: make sure you get 'Development Libraries' not 'Runtime Binaries' \n
 *  - SDL2        : <a href="https://www.libsdl.org/download-2.0.php">page with download links</a>  \n
 *  - SDL2 image  : <a href="https://www.libsdl.org/projects/SDL_image/">page with download links</a> \n
 *  - SDL2 mixer  : <a href="https://www.libsdl.org/projects/SDL_mixer/">page with download links</a> \n
 *  - SDL2 ttf    : <a href="https://www.libsdl.org/projects/SDL_ttf/">page with download links</a> \n
 *      - FreeType2.6 : <a href="http://download.savannah.gnu.org/releases/freetype/">page with download links</a> \n
 * .
 * \subsubsection step1-1 Setting up on Microsoft Windows OS:
 * On Windows you can use this specific packages (or use links above to find
 * more recent version): \n
 *  - SDL2        : <a href="https://www.libsdl.org/release/SDL2-devel-2.0.4-mingw.tar.gz">
 * download link for version 2.0.4-mingw</a> \n
 *  - SDL2 image  : <a href="https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.1-win32-x86.zip">
 * download link for version 2.0.1-win32-x86</a> \n
 *  - SDL2 mixer  : <a href="https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.1-win32-x86.zip">
 * download link for version 2.0.1-win32-x86</a> \n
 *  - SDL2 ttf    : <a href="https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14-win32-x86.zip">
 * download link for version 2.0.14-win32-x86</a> \n
 *      -  FreeType2.6 : included in SDL2 ttf
 * .
 * Installing the libraries: \n
 * Extract the archives anywhere you want but remember the path to these files \n
 * For example you can extract them to C:\\SDL\\ \n
 *
 * \subsubsection step1-2 Setting up on Unix:
 *
 * Compiling from source. You can use this specific packages (or use links above
 * to find more recent version): \n
 *  - SDL2        : <a href="https://www.libsdl.org/release/SDL2-2.0.4.tar.gz">
 * download link for version 2.0.4</a> \n
 *  - SDL2 image  : <a href="https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.1.tar.gz">
 * download link for version 2.0.4</a> \n
 *  - SDL2 mixer  : <a href="https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.1.tar.gz">
 * download link for version 2.0.4</a> \n
 *  - SDL2 ttf    : <a href="https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz">
 * download link for version 2.0.4</a> \n
 *      - FreeType2.6 : <a href="http://download.savannah.gnu.org/releases/freetype/freetype-2.6.3.tar.gz">
 * download link for version 2.6.3</a> \n
 *
 * .
 * For each of the above mention archives do the following: \n
 *  -# <b>extract the archive</b>
 *  -# <b>execute the following commands:</b>
 *      -# <b>$ ./configure</b>
 *      -# <b>$ make</b>
 *      -# <b>$ make install</b>
 * .
 * note: command 'make install' needs to be done as root. \n
 * note2: FreeType2.6 (libfreetype6) needs to be installed before SDL2 ttf. You
 * might already have it. \n
 * Or use different instruction for installing given in the packages. \n
 * After installing above libraries you should run \n
 *  - <b>$ ldconfig </b>(as root).
 * .
 *
 * On Ubuntu systems you can use this specific packages instead: \n
 * Note: doing it this way will require you to change paths to include and lib
 * files in Makefile \n
 *  - SDL2        : <b>$ sudo apt-get install libsdl2-dev</b> \n
 *  - SDL2 image  : <b>$ sudo apt-get install libsdl2-image-dev</b> \n
 *  - SDL2 mixer  : <b>$ sudo apt-get install libsdl2-mixer-dev</b> \n
 *  - SDL2 ttf    : <b>$ sudo apt-get install libsdl2-ttf-dev</b> \n
 *  - FreeType2.6 : <b>$ sudo apt-get install libfreetype6-dev</b> \n
 * .
 * \subsection step2 Step 2: Compile using g++
 *
 * \subsubsection step2-1 Compiling on Microsoft Windows OS:
 *
 * The project was written using <a href="http://www.codeblocks.org/">
 * Code::Block IDE</a> on Windows which you can
 * <a href="http://www.codeblocks.org/downloads">download here</a>. It is
 * recommended to compile it on Windows this way since there is already a .cbp
 * file (code blocks project file) included with the source code. \n
 * Only change you will possibly need to make before compiling is to configure
 * the path to SDL libraries. If you extracted all the packages into C:\\SDL\\
 * you are already set to go. \n
 * If not the you need to will need to configure custom variable under
 * <b>Project-> Build Options...-> Custom variables</b>. Change
 * <b>the SDL_install_dir</b> variable to reflect the correct path of your
 * location of SDL libraries. If you don't have all libraries under the same
 * path then you need to reconfigure path for each of them individually under
 * <b>Project-> Build Options...-> Search Directories</b> for both compiler and
 * linker. Keep in mind that you need to reconfigure this settings for each of
 * the build setups. \n
 * In the given .cbp file there are two setups: Debug and Release. \n
 * After compilation Code::Blocks puts the executables under the
 * ./bin/{Build_name}/ and object files under ./obj/{Build_name}/ where
 * {Build_name} is the name of build setup.
 *
 * \subsubsection step2-2 Compiling on Unix:
 *
 * There is a Makefile provided with the source code that you can use to compile
 * the project. If you installed your libraries from source the default way then
 * additional configuration are not necessary. If you installed them in a
 * different way you need to change variables <b>SDL_INCLUDE</b> and
 * <b>SDL_LIB</b> in Makefile. <b>SDL_INCLUDE</b> is the path to include or
 * header files of SDL2 while <b>SDL_LIB</b> is path to lib or .so files of SDL2
 * \n
 * You can use one of the following commands to compile the source code:
 *  - <b>$ make</b> (default way)
 *  - <b>$ make debug</b> (compiles with -g flag for debugging)
 *  - <b>$ make release</b> (compiles with -O2 flag for additional optimizations)
 *
 * \subsection step3 Step 3: Running the game
 *
 * \subsubsection step3-1 Running the game on Microsoft Windows OS:
 *
 * Simple way: Download, extract and run precompiled binaries for Windows from this
 * <a href="http://alas.matf.bg.ac.rs/~mi13211/Bomberman.rar">link</a>. \n
 *
 * Or if you have compiled the code on your own take the following steps: \n
 * In order to run the executable you need following .dll files:
 *  - libfreetype-6.dll
 *  - SDL2.dll
 *  - SDL2_image.dll
 *  - SDL2_mixer.dll
 *  - SDL2_ttf.dll
 *  - smpeg2.dll
 *  - zlib1.dll
 * .
 * all of which can be found in both 'Development Libraries' and 'Runtime
 * Binaries' archives from above links to SLD2 or alternatively you can download
 * them from this
 * <a href="http://alas.matf.bg.ac.rs/~mi13211/Bomberman%20DLL%20files.rar">
 * link</a> \n
 * If you are running the game from inside Code::Block IDE the you need to copy
 * the file into project root directory. \n
 * If you want to run executable directly the you need to place the .dll files
 * in the directory from which you are running the .exe file (that will most
 * likely be the same directory as the one with .exe).
 * The last thing you need is to have a copy of 'resources' directory in the
 * same directory from which you are running the .exe, same as with .dll files.
 *
 * \subsubsection step3-2 Running the game on Unix:
 *
 * After you have compiled the source code you can run the game from the root
 * directory of the project by using command \n
 * <b>$ ./bin/Bomberman.exe</b> \n
 * If you want to move the compiled files to a different directory you also need
 * to copy directory 'resources' with it. All you need is to have
 * 'Bomberman.exe' and 'resources' directory in the same directory in order to
 * run the game.
 */


/*
Please not that if you use a later version of SDL you will need to update the linker directories and compiler directories under
Settings>Compiler>Search directories>Linker and Settings>Compiler>Search directories>compiler

The directories below are the ones that will need to be changed if you use a different version.

Under: settings>Search directories>Compiler
C:\SDL\SDL2-2.0.2\i686-w64-mingw32\include\SDL2
C:\SDL\SDL2_image-2.0.0\i686-w64-mingw32\include\SDL2

Under: settings>Search directories>Linker
C:\SDL\SDL2-2.0.2\i686-w64-mingw32\lib
C:\SDL\SDL2_image-2.0.0\i686-w64-mingw32\lib

My includes are
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

if you change
C:\SDL\SDL2-2.0.2\i686-w64-mingw32\include\SDL2
C:\SDL\SDL2_image-2.0.0\i686-w64-mingw32\include\SDL2
to
C:\SDL\SDL2-2.0.2\i686-w64-mingw32\include
C:\SDL\SDL2_image-2.0.0\i686-w64-mingw32\include
the include would need to be changed to
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
*/
