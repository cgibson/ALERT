from SCons.Script import *

from SCons.Script import *
from os.path import join
from os import path
import os
import tarfile
import shutil
import distutils.dir_util


## UnzipLib will take the given library and pull it from its tar file,
#  placing it within the given folder
#  @param inputFile: The tar file to unzip
#  @param outPath: Where to output the tar
#  @param member: Whether or not to extract certain members
def unzipLib(inputFile, outPath, members=None):
    print "UNZIPPING [%s] --> [%s]" % (inputFile, outPath)
    tar = tarfile.open(inputFile, "r:gz")
        
    tar.extractall(path=outPath,members=members)


## DirContextManager is a context manager which will enter a certain
#  directory, leaving it and returning to the old cwd once finished
class DirContextManager(object):
    
    def __init__(self, dir):
        self.oldDir = os.getcwd()
        self.newDir = dir

    def __enter__(self):
        os.chdir(self.newDir)
        
    def __exit__(self, type, value, traceback):
        os.chdir(self.oldDir)


## TarContextManager is a special context manager that opens a tar file, 
#  extracts it in a given temporary directory, and enters a given folder
#  within that extracted tar, returning (and cleaning the folder) when done
class TarContextManager(DirContextManager):
    
    ## Initialization of the tar context manager
    #  @param file: The tar file to extract
    #  @param tmpDir: Temporary directory to extract in
    #  @param folder: Folder to cd into within the tar file
    #  @param doRemoval: Remove the directory after use (defaults to false)
    def __init__(self, file, tmpDir, folder, doRemoval=False):
        self.doRemoval = doRemoval
        self.file = file
        self.tmpDir = tmpDir
        self.unzippedDir = join(tmpDir, folder)
        super(self.__class__,self).__init__(self.unzippedDir)
        
    def __enter__(self):
        unzipLib(self.file, self.tmpDir)
        super(self.__class__,self).__enter__()
        
    def __exit__(self, type, value, traceback):
        super(self.__class__,self).__exit__(type,value,traceback)
        
        # If removal is requested, take out the entire tree that we created
        if self.doRemoval:
            shutil.rmtree(self.unzippedDir)
        
        
## EnvirContextManager is a special context manager that overwrites a given 
#  environment variable while it is active, reverting the variable to its
#  original state upon exit
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
            
            
## replaceInFile runs a sed command on the file, allowing us to search and
#  replace certain patterns within a file
#  @param file: File to run the sed command on
#  @param pattern: String pattern to replace
#  @param replace: Replacement string
def replaceInFile(file, pattern, replace):
        pattern = pattern.replace("/", "\/")
        replace = replace.replace("/", "\/")
        pattern = pattern.replace("[", "\[")
        replace = replace.replace("[", "\[")
        print "sed -i 's/%s/%s/g' %s" % (pattern, replace, file)
        return os.system("sed -i 's/%s/%s/g' %s" % (pattern, replace, file))


## copyHeaders recursively visits a folder structure, copying all headers it 
#  finds into a equivalent folder structure, leaving everything else out
#  @param inPath: The directory to recurse into searching for headers
#  @param outPath: The output where the resulting folder structure of headers 
#                  is to be placed
def copyHeaders(inPath, outPath):
    
    # We want to make sure that the output path and its ancestor directories
    # exist before we begin
    if not path.exists(outPath):
        os.makedirs(outPath)
        
    # Copy all headers into an include file
    # TODO:  listDir probably has a recursive flag that can save us a lot of
    #        trouble
    files = os.listdir(inPath)
    
    # Loop through every file that we find
    for file in files:
        inFile = join(inPath, file)
        outFile = join(outPath, file)
        if path.isdir(inFile):
            copyHeaders(inFile, outFile)
        else:
            if (file[-2:] == ".h") or (file[-4:] == ".hpp"):
                shutil.copy(inFile, outFile)


## buildLuaBind runs the necessary commands to construct the LuaBind library 
#  @param externPath: The location to uncompress the tar    
#  @param libPath: Where to place the lib once we are done      
def buildLuaBind(externPath, libPath):
    libName = "LuaBind"             # Library name is used in error messages
    libNameLong = "luabind-0.9.1"   # Long library name is used as the tar name
    libFile = "libluabindd.a"
    
    if path.exists(join(libPath, libFile)):
        print "Skipping %s -- Already Built" % libName
        return
    
    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):
        
        # Protect the LUA_PATH environment path
        with EnvirContextManager({"LUA_PATH":externPath}):
            
            #os.system("echo $LUA_PATH")
            os.system("bjam link=static --prefix=%s install" % externPath)
                

## buildLuaJIT unpacks the luaJIT tar files, but also has to prepare the source
#  code before use.  Unfortunately, in order for luaJIT and LuaBind to work well
#  together, a few changes (namely adding the -fPIC flag) must be made.  Also,
#  a symlink is made so that LuaBind thinks that luaJIT is really Lua...
#  @param externPath: The location to uncompress the tar
#  @param libPath: Where to place the lib once we are done
def buildLuaJIT(externPath, libPath):
    libName = "LuaJIT"                  # Library name is used in error messages
    libNameLong = "LuaJIT-2.0.0-beta8"  # Long library name is used as the tar name
    libFile = "libluajit.a"
    
    if path.exists(join(libPath, libFile)):
        print "Skipping %s -- Already Built" % libName
        return
    
    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):
        
        print "currently in %s" % os.getcwd()
        # First, find and replace the line in the Makefile that includes the CFLAGS.  We want
        # to add -fPIC near the end
        replaceInFile("src/Makefile", 
                      "CCWARN= -Wall", 
                      "CCWARN= -Wall -fPIC")
        
        os.system("make")
        
        # Copy lib
        shutil.copy(join("src", libFile), libPath)
        
        incPath = join(externPath, "include")
        
        # Copy Include
        copyHeaders("src", join(incPath, "luajit"))
        
        # Create lua sym link to includes (ONLY if we didn't make lua already)
        print "LINKING [%s] --> [%s]" % (join(incPath, "luajit"), join(incPath, "lua51"))

        if not path.exists(join(incPath, "lua51")):
            os.symlink(join(incPath, "luajit"), join(incPath, "lua51"))
        
        # Create lua lib link to luajit (if we didn't make lua)
        if not path.exists(join(libPath, "liblua.a")):
            os.symlink(join(libPath, "libluajit.a"), join(libPath, "liblua.a"))
                  

## buildIlmBase takes the Ilm libraries necessary for Open EXR  and compiles 
#  them.  Because newer versions of GCC choke on this library, a few additional
#  includes are added to a select few source files automatically
#  @param externPath: The location to uncompress the tar
#  @param libPath: Where to place the lib once we are done              
def buildIlmBase(externPath, libPath, confOpts=[]):
    libName = "IlmBase"             # Library name is used in error messages
    libNameLong = "ilmbase-1.0.2"   # Long library name is used as the tar name
    libFile = "libImath.so"
    
    if path.exists(join(libPath, libFile)):
        print "Skipping %s -- Already Built" % libName
        return
    
    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):
        
        # PATCH to fix gcc 4.3.2 compatability issus
        replaceInFile(" Imath/ImathMatrix.h", 
                      "#include <iostream>", 
                      "#include <iostream>\\n#include <cstring>")
        
        os.system("./configure %s" % " ".join(confOpts))
        os.system("make")
        os.system("make install")
        
        incPath = join(externPath, "include")
        copyHeaders("Imath", join(incPath, "Imath"))


## buildOpenExr also makes modifications to a few of its files in order to fix a
#  gcc 4.3.2 compatibility issue before compiling.  This library enables us to
#  load and save EXR images (for high dynamic range beyond the typical 32-bit 
#  color range
#  @param externPath: The location to uncompress the tar
#  @param libPath: Where to place the lib once we are done     
def buildOpenEXR(externPath, libPath, confOpts=[]):
    libName = "OpenEXR"             # Library name is used in error messages
    libNameLong = "openexr-1.7.0"   # Long library name is used as the tar name
    libFile = "libIlmImf.so"
    
    if path.exists(join(libPath, libFile)):
        print "Skipping %s -- Already Built" % libName
        return

    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):

        # PATCH to fix gcc 4.3.2 compatibility issus   
        replaceInFile("exrenvmap/blurImage.cpp", 
                      "#include <iostream>", 
                      "#include <iostream>\\n#include <cstring>")
        
        # Compile
        os.system("./configure %s" % " ".join(confOpts))
        os.system("make")
        os.system("make install")


## buildLua is mostly a legacy function used when we can't get LuaJIT to work.
#  Notice that a specific flag is inserted into the makefile... -fPIC is 
#  necessary for some of our work
#  @param externPath: The location to uncompress the tar
#  @param libPath: Where to place the lib once we are done
def buildLua(externPath, libPath):
    libName = "Lua"             # Library name is used in error messages
    libNameLong = "lua-5.1.4"   # Long library name is used as the tar name
    libFile = "liblua.a"
    
    if path.exists(join(libPath, libFile)):
        print "Skipping %s -- Already Built" % libName
        return
    
    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):
        
        # First, find and replace the line in the Makefile that includes the CFLAGS.  We want
        # to add -fPIC near the end
        replaceInFile("src/Makefile", 
                      "CFLAGS= -O2 -Wall", 
                      "CFLAGS= -O2 -Wall -fPIC")
        
        os.system("make posix")
        
        # Copy lib
        shutil.copy("src/liblua.a", libPath)
        
        # Copy Include
        incPath = join(externPath, "include")
        copyHeaders("src", join(incPath, "lua"))


## buildHdf5 builds the extensible file format library used primarily for our
#  volume code.
#  @param externPath: The location to uncompress the tar
#  @param libPath: Where to place the lib once we are done
def buildHdf5(externPath, libPath, confOpts=[]):
    libName = "Hdf5"             # Library name is used in error messages
    libNameLong = "hdf5-1.8.8"   # Long library name is used as the tar name
    libFile = "libhdf5.so"
    
    if path.exists(join(libPath, libFile)):
        print "Skipping %s -- Already Built" % libName
        return
    
    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):
        
        # Compile
        os.system("./configure %s" % " ".join(confOpts))
        os.system("make")
        os.system("make install")
        
        # Copy Include
        incPath = join(externPath, "include")
        copyHeaders("src", join(incPath, "hdf5"))


## buildField3D builds Sony ImageWorks' open source volume library
#  @param externPath: The location to uncompress the tar
#  @param libPath: Where to place the lib once we are done
def buildField3D(externPath, libPath, archNum="32"):
    libName = "Field3D"             # Library name is used in error messages
    libNameLong = "Field3D"   # Long library name is used as the tar name
    libFile = "libField3D.so"
    
    incPath = join(externPath, "include")
    
    if path.exists(join(libPath, libFile)):
        print "Skipping %s -- Already Built" % libName
        return
    
    with TarContextManager(join(externPath, libNameLong + ".tar.gz"), externPath, libNameLong):
        
        # Copy "Site.py" build configuration
        shutil.copy("ExampleSite.py", "Site.py")
        
        # Replace/add include and library folders:
        replaceInFile("Site.py", "mathIncPaths = [", "mathIncPaths = [\"%s\",\"%s\"," %
                      (join(incPath, "Imath"), incPath))
        
        replaceInFile("Site.py", "mathLibPaths = [", "mathLibPaths = [\"%s\"," %
                      libPath)
        
        replaceInFile("Site.py", "incPaths = [", "incPaths = [\"%s\"," % incPath)
        
        replaceInFile("Site.py", "libPaths = [", "libPaths = [\"%s\"," % libPath)
        
        # Remove TERRIBLE additional namespace that caused SO MUCH GRIEF
        replaceInFile("Site.py", "extraNamespace = \"SPI\"", "")
        
        # Add -fPIC... cuz i said so.
        replaceInFile("BuildSupport.py", "env.Append(CCFLAGS = [\"-Wall\"])", "env.Append(CCFLAGS = [\"-Wall\", \"-fPIC\"])")
        
        # Include correct boost thread library
        replaceInFile("Site.py", "boost_thread-gcc34-mt", "boost_thread-mt")
        
        # Compile
        os.system("scons do64=1")
        
        # Copy lib
        shutil.copy("install/linux2/m%s/release/lib/libField3D.so" % archNum, libPath)
        
        # Copy Include
        copyHeaders("install/linux2/m%s/release/include/Field3D" % archNum, join(incPath, "Field3D"))
          
          
## buildAllLibs will go through and build each required lib one at a time.
#  After all of the build* methods have been run, the extern/lib folder
#  should be filled with ready-to-use static libraries.      
def buildAllLibs(archNum, buildLibPath=join("build","lib")):
        
    # Necessary paths
    externPath = path.abspath("extern")
    libPath = path.abspath("extern/lib")
    
    # Sanity checks
    if not path.exists(externPath):
        raise ValueError("No extern path [%s]" % externPath)
    if not path.exists(libPath):
        os.makedirs(libPath)
        
    # Ensure that the libraries running ./configure will build ONLY as static
    # libraries.  This is very important, as shared libraries just lead to
    # complications and hearache.
    #
    configureOpts = ["--prefix=%s" % externPath,
                     #"--enable-shared=yes",
                     #"--enable-static=no",
                     "CPPFLAGS=\"-fPIC\""
                     ]
    
    # We skip over Lua because we have LuaJIT working!
    #buildLua(externPath, libPath)
    buildLuaJIT(externPath, libPath)
    buildLuaBind(externPath, libPath)
    buildIlmBase(externPath, libPath, 
                 confOpts=configureOpts + ["--enable-shared=no",
                                           "--enable-static=yes"])
    buildOpenEXR(externPath, libPath, 
                 confOpts=configureOpts + ["--enable-shared=yes",
                                           "--enable-static=yes"])
    buildHdf5(externPath, libPath, 
                 confOpts=configureOpts + ["--enable-shared=yes",
                                           "--enable-static=yes"])
    buildField3D(externPath, libPath, archNum=archNum)
    
    # Copy libs out of extern
    if not path.exists(buildLibPath):
        os.symlink(libPath, buildLibPath)
        
    #shutil.copytree(libPath, buildLibPath)
