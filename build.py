#!/usr/bin/env python

# /*
# (c) 2014 +++ Filip Stoklas, aka FipS, http://www.4FipS.com +++
# THIS CODE IS FREE - LICENSED UNDER THE MIT LICENSE
# ARTICLE URL: http://forums.4fips.com/viewtopic.php?f=3&t=1201
# */

import os
import stat
import fnmatch
import SimpleHTTPServer
import SocketServer
from shutil import rmtree, copy2
from subprocess import check_call

def resolve_path(rel_path):
    return os.path.abspath(os.path.join(os.path.dirname(__file__), rel_path)) 

def rmtree_silent(root):
    def remove_readonly_handler(fn, root, excinfo):
        if fn is os.rmdir:
            if os.path.isdir(root): # if exists
                os.chmod(root, stat.S_IWRITE) # make writable
                os.rmdir(root)
        elif fn is os.remove:
            if os.path.isfile(root): # if exists
                os.chmod(root, stat.S_IWRITE) # make writable
                os.remove(root)
    rmtree(root, onerror=remove_readonly_handler)

def makedirs_silent(root):
    try:
        os.makedirs(root)
    except OSError: # mute if exists
        pass

def copyfiles(srcdir, dstdir, filepattern):
    def failed(exc):
        raise exc

    for dirpath, dirs, files in os.walk(srcdir, topdown=True, onerror=failed):
        for file in fnmatch.filter(files, filepattern):
            copy2(os.path.join(dirpath, file), dstdir)
        break # no recursion

if __name__ == "__main__":

    build_dir = resolve_path("./Build")
    rmtree_silent(build_dir)
    makedirs_silent(build_dir)
    os.chdir(build_dir)

    check_call([
     "cmake",
     #os.path.expandvars("-DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Platform/Emscripten.cmake"),
     os.path.expandvars("-DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake"),
     #"-DCMAKE_BUILD_TYPE=Release",
     "-DCMAKE_BUILD_TYPE=RelWithDebInfo",
     "-DCYC_EMSCRIPTEN=1",
     "-DCMAKE_MAKE_PROGRAM=make",
     "-G", "Unix Makefiles",
     ".."
    ])

    #check_call(["mingw32-make"])
    check_call(["make"])
    
    # we are in Build directory
    #dest_dir = resolve_path("../../../tklweb-cp/public/kull-ems")
    dest_dir = resolve_path("../Public")
    rmtree_silent(dest_dir)
    makedirs_silent(dest_dir)
    
    # we are in Build directory
    copyfiles(resolve_path("./Applications/Main"), resolve_path("../Public"), "Main*")

    # run http server in current dir

    port = 8000

    os.chdir(dest_dir)
    Handler = SimpleHTTPServer.SimpleHTTPRequestHandler
    httpd = SocketServer.TCPServer(("", port), Handler)

    print "serving at port", port
    httpd.serve_forever()

    #open browser
