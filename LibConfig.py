from SCons.Script import *

from SCons.Script import *
from os.path import join
from os import path
import os
import tarfile
import shutil



def unzipLib(inputFile, outPath, members=None):
    print "UNZIPPING [%s] --> [%s]" % (inputFile, outPath)
    tar = tarfile.open(inputFile, "r:gz")
        
    tar.extractall(path=outPath,members=members)


class DirContextManager(object):
    
    def __init__(self, dir):
        self.oldDir = os.getcwd()
        self.tmpDir = dir

    def __enter__(self):
        print "ENTERING [%s]" % self.tmpDir
        os.chdir(self.tmpDir)
        
    def __exit__(self, type, value, traceback):
        os.chdir(self.oldDir)


class TarContextManager(DirContextManager):
    
    def __init__(self, file, tmpDir, folder):
        self.unzippedDir = join(tmpDir, folder)
        unzipLib(file, tmpDir)
        super(self.__class__,self).__init__(self.unzippedDir)
        
    def __exit__(self, type, value, traceback):
        super(self.__class__,self).__exit__(type,value,traceback)
        #shutil.rmtree(self.unzippedDir)
        
        
class EnvirContextManager(object):
    
    def __init__(self, dict):
        self.dict = dict
        self.oldDict = {}
        
    def __enter__(self):
        for key, value in self.dict.iteritems():
            if key in os.environ:
                self.oldDict[key] = os.environ[key]
            else:
                self.oldDict[key] = ""
            os.environ[key] = value
    
    def __exit__(self, type, value, traceback):
        for key, value in self.oldDict.iteritems():
            os.environ[key] = value
        


def makeLib(libInfo, tmpPath, outPath):
    # Path to the zip file
    libZipPath = join(externPath, libInfo["name"] + ".tar.gz")
    # Path to the unzipped lib directory
    libTmpPath = join(tmpPath, libInfo["name"])
    # Path to the generated library file
    tmpLibObjPath = join(libTmpPath, libInfo["outLib"], libInfo["libFile"])
    if path.exists(tmpLibObjPath):
        return tmpLibObjPath
    
    # Copy the contents of the tar.gz file into the temp dir
    unzipLib(libZipPath, tmpPath)
        
    # Compile the library
    print "COMPILING [%s]" % libInfo["name"]
    oldPath = os.getcwd()
    os.chdir(libTmpPath)
    os.system(libInfo["buildCmd"])
    os.chdir(oldPath)
    
    return tmpLibObjPath

def copyHeaders(inPath, outPath):
    if not path.exists(outPath):
        os.makedirs(outPath)
    # Copy all headers into an include file
    files = os.listdir(inPath)
    
    for file in files:
        inFile = join(inPath, file)
        outFile = join(outPath, file)
        if path.isdir(inFile):
            copyHeaders(inFile, outFile)
        else:
            if (file[-2:] == ".h") or (file[-4:] == ".hpp"):
                shutil.copy(inFile, outFile)
                
def buildLuaBind(externPath, libPath):
    libName = "LuaBind"
    libNameLong = "luabind-0.9.1"
    
    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):
        
        # Protect the LUA_PATH environment path
        with EnvirContextManager({"LUA_PATH":externPath}):
            
            #os.system("echo $LUA_PATH")
            os.system("bjam link=static --prefix=%s install" % externPath)
                
def buildLuaJIT(externPath, libPath):
    libName = "LuaJIT"
    libNameLong = "LuaJIT-2.0.0-beta8"

    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):
        
        # First, find and replace the line in the Makefile that includes the CFLAGS.  We want
        # to add -fPIC near the end
        os.system("sed -i 's/CCWARN= -Wall/CCWARN= -Wall -fPIC/g' %s" % "src/Makefile")
        
        os.system("make")
        
        # Copy lib
        shutil.copy("src/libluajit.a", libPath)
        
        incPath = join(externPath, "include")
        
        # Copy Include
        copyHeaders("src", join(incPath, "luajit"))
        
        # Create lua sym link to includes (ONLY if we didn't make lua already)
        print "LINKING [%s] --> [%s]" % (join(incPath, "luajit"), join(incPath, "lua51"))

        if not path.exists(join(incPath, "lua")):
            os.symlink(join(incPath, "luajit"), join(incPath, "lua51"))
        
        # Create lua lib link to luajit (if we didn't make lua)
        if not path.exists(join(libPath, "liblua.a")):
            os.symlink(join(libPath, "libluajit.a"), join(libPath, "liblua.a"))
                
def buildIlmBase(externPath, libPath):
    libName = "IlmBase"
    libNameLong = "ilmbase-1.0.2"

    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):
        
        # PATCH to fix gcc 4.3.2 compatability issus
        os.system("sed -i 's/#include <iostream>/#include <iostream>\\n#include <cstring>/g' Imath/ImathMatrix.h")
        
        os.system("./configure --prefix=%s" % externPath)
        os.system("make")
        os.system("make install")
        
        incPath = join(externPath, "include")
                
def buildOpenEXR(externPath, libPath):
    libName = "OpenEXR"
    libNameLong = "openexr-1.7.0"

    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):

        # PATCH to fix gcc 4.3.2 compatability issus          
        os.system("sed -i 's/#include <iostream>/#include <iostream>\\n#include <cstring>/g' exrenvmap/blurImage.cpp")
        
        # Compile
        os.system("./configure --prefix=%s" % externPath)
        os.system("make")
        os.system("make install")


def buildLua(externPath, libPath):
    libName = "Lua"
    libNameLong = "lua-5.1.4"

    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):
        
        # First, find and replace the line in the Makefile that includes the CFLAGS.  We want
        # to add -fPIC near the end
        os.system("sed -i 's/CFLAGS= -O2 -Wall/CFLAGS= -O2 -Wall -fPIC/g' %s" % "src/Makefile")
        
        os.system("make posix")
        
        # Copy lib
        shutil.copy("src/liblua.a", libPath)
        
        # Copy Include
        incPath = join(externPath, "include")
        copyHeaders("src", join(incPath, "lua"))
                
def buildAllLibs():
        
    # Necessary paths
    externPath = path.abspath("extern")
    libPath = path.abspath("extern/lib")
    
    
    # Sanity checks
    if not path.exists(externPath):
        raise ValueError("No extern path [%s]" % externPath)
    if not path.exists(libPath):
        os.makedirs(libPath)
    
    #buildLua(externPath, libPath)
    buildLuaJIT(externPath, libPath)
    buildLuaBind(externPath, libPath)
    buildIlmBase(externPath, libPath)
    buildOpenEXR(externPath, libPath)