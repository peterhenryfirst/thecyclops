#!/usr/bin/env python

# /*
# (c) 2014 +++ Filip Stoklas, aka FipS, http://www.4FipS.com +++
# THIS CODE IS FREE - LICENSED UNDER THE MIT LICENSE
# ARTICLE URL: http://forums.4fips.com/viewtopic.php?f=3&t=1201
# */

import os
import stat
import fnmatch
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
    os.chdir(build_dir)

    #check_call(["mingw32-make"])
    check_call(["make"])
    
    # we are in Build directory
    dest_dir = resolve_path("../../../tklweb-cp/public/kull-ems")
    rmtree_silent(dest_dir)
    makedirs_silent(dest_dir)
    
    copyfiles(resolve_path("./Applications/Main"), resolve_path("../../../tklweb-cp/public/kull-ems"), "Main*")
