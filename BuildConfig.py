import os
import sys

from SCons.Script import *
from os.path import join
from os import path
from LibConfig import *

#------------------------------------------------------------------------------#

archNum = "64"

# Program to output
programName = 'AleRT'

# The location to compile the program
programPath = '.'

# The compiler to use throughout the compilation process
compilerType = 'g++'

# Where to place all build-related objects and files
buildPath = "build"

# Where all libraries exist
buildLibPath = buildPath + "/lib"

# No source besides include files and test files should exist outside of here
srcDir = "src"

# Test directory
testDir = "test"

externPath = "extern"


sysDefines = {} #{"FIELD3D_EXTRA_NAMESPACE":"SPI"}
# These lie under the source directory
srcModules = [
              'geom',
              'util',
              'lua',
              'light',
              'core',
              'texture',
              'camera',
              'render',
              'scene'
             ]

# Modules referenced by the test source code
testModules = [
               'glm',
               'luabind',
               'texture',
               'Field3D'
              ]

# Paths to include from
sysIncludePaths = [
                   'include',
                   'glm',
                   'extern/include/',
                   'extern/include/luajit/',
                   'extern/include/luabind/',
                   'extern/include/lua',
                   'extern/include/OpenEXR'
                  ]

# Paths containing libraries
sysLibPaths = [
               'lib',
               'extern/lib'
              ]

# Libraries to reference
sysLibs = [
           'boost_thread-mt', # Because everything needs boost
           'Field3D',         # Pure volume-structure awesomeness
           'luajit',          # Super fast lua (supposedly)
           'Imath',           # Maths, let me tell you about them
           'hdf5',            # Some awesome extendable file format
           'Iex',             # Something something something Field3D
           'IlmThread',       # Throw more threads at it and it will go faster
           #'lua',            # We use luaJIT as a replacement for Lua51
           'luabindd',        # Bind our luas to our C++
           'IlmImf',          # Ilm makes a lot of cool stuff.
           'Half',            # Required for OpenEXR
           'dl',              # Required for god only knows why
           'z'                # Required for gzip performance on hdf5
          ]
          
testLibs = [
            'boost_unit_test_framework'
           ]


#------------------------------------------------------------------------------#

## isDebugBuild returns whether or not the "debug=1" flag was included while
#  running scons
def isDebugBuild():
    return ARGUMENTS.get('debug', 0)


## isDebugBuild returns whether or not the "test=1" flag was included while
#  running scons
def isTestBuild():
    return ARGUMENTS.get('test', 0)


## isDebugBuild returns whether or not the "rebuild-libs=1" flag was included 
#  while running scons
def isLibRebuild():
    return ARGUMENTS.get('rebuild-libs', 0)
    

## getBuildPath finds the path to the root directory and tacks on the build path
#  @param pathToRoot: Necessary to normalize the path to the root directory
def getBuildPath(pathToRoot = "."):
    return join(pathToRoot, buildPath)
    
    
## buildPaths takes the list of paths and sanitizes them for whatever folder we
#  are currently in (according to pathToRoot.)  This fixes any relative path
#  craziness
#  @param paths: List of paths to sanitize
#  @param pathToRoot: The path that gets us to the root directory
def buildPaths(paths, pathToRoot):
    mapPath = lambda x:  x if path.isabs(x) else join(pathToRoot, x); 
    return map(mapPath, paths)


## getSource will take the module requested and normalize it based on the 
#  pathToRoot variable, returning all source files within
#  @param module: The directory under the source dir to grab cpp files from
#  @param pathToRoot: Used to normalize the path to the source dir
def getSource(module, pathToRoot = "."):
    #print join(pathToRoot, buildPath, module, "*.cpp")
    return Glob(join(pathToRoot, srcDir, module, "*.cpp"))


#------------------------------------------------------------------------------#
## setupEnv will take the current environment and path to root directory and 
#  apply the correct paths and library locations to the environment
#  @param env: SCons environment
#  @param pathToRoot: Used to normalize us to the root directory
def setupEnv(env, pathToRoot = "."):
    
    applyDir = lambda x, y: "%s/%s" % (x, y);
    
    # Include paths
    env.Replace(CPPPATH = buildPaths(sysIncludePaths, pathToRoot))
    
    # Library paths
    env.Replace(LIBPATH = buildPaths(sysLibPaths, pathToRoot))
    
    # Libraries
    env.Replace(LIBS = sysLibs)
    
    # Defines
    env.AppendUnique(CPPDEFINES=sysDefines)
    
    # Test libraries
    if(isTestBuild()):
        env.Append(LIBS = testLibs)
    
    if isDebugBuild():
        env.Append(CCFLAGS = ["-g"])
        
        
#------------------------------------------------------------------------------#
## Hopefully unused
def initialize(pathToRoot = "."):
    
    env = Environment(CC = 'g++')
    
    setupEnv(env, pathToRoot)
    
    conf = Configure(env)
    
    return env, conf


## rebuildLibs runs the "buildAllLibs" method within the libConfig module
def rebuildLibs():
    buildAllLibs(archNum)
    
## moveLibs moves all libs to the build library path for use in the build
#  folder structure
def moveLibs():
    moveAllLibs(buildLibPath)
