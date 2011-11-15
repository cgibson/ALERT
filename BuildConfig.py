import os
import sys

from SCons.Script import *
from os.path import join
from os import path

from LibConfig import *

#------------------------------------------------------------------------------#

programName = 'AleRT'

programPath = '.'

compilerType = 'g++'

buildPath = "build"

buildLibPath = buildPath + "/lib"

# No source besides include files and test files should exist outside of here
srcDir = "src"

# Test directory
testDir = "test"

externPath = "extern"

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

testModules = [
               'glm',
               'luabind',
               'texture'
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
           'boost_thread-mt',
           'luajit',
           #'lua',
           'luabindd',
           'IlmImf',
           'Half',
           'dl'
          ]
          
testLibs = [
            'boost_unit_test_framework'
           ]


#------------------------------------------------------------------------------#
def isDebugBuild():
    return ARGUMENTS.get('debug', 0)

def isTestBuild():
    return ARGUMENTS.get('test', 0)

def isLibRebuild():
    return ARGUMENTS.get('rebuild-libs', 0)
    
    
def getBuildPath(pathToRoot = "."):
    return join(pathToRoot, buildPath)
    
def buildPaths(paths, pathToRoot):
    mapPath = lambda x:  x if path.isabs(x) else join(pathToRoot, x); 
    return map(mapPath, paths)
    
def getSource(module, pathToRoot = "."):
    #print join(pathToRoot, buildPath, module, "*.cpp")
    return Glob(join(pathToRoot, srcDir, module, "*.cpp"))


#------------------------------------------------------------------------------#
def setupEnv(env, pathToRoot = "."):
    
    applyDir = lambda x, y: "%s/%s" % (x, y);
    
    # Include paths
    env.Replace(CPPPATH = buildPaths(sysIncludePaths, pathToRoot))
    
    # Library paths
    env.Replace(LIBPATH = buildPaths(sysLibPaths, pathToRoot))
    
    # Libraries
    env.Replace(LIBS = sysLibs)
    
    # Test libraries
    if(isTestBuild()):
        env.Append(LIBS = testLibs)
    
    if isDebugBuild():
        env.Append(CCFLAGS = ["-g"])
        
        
#------------------------------------------------------------------------------#
def initialize(pathToRoot = "."):
    
    env = Environment(CC = 'g++')
    
    setupEnv(env, pathToRoot)
    
    conf = Configure(env)
    
    return env, conf


def rebuildLibs():
    buildAllLibs()
    
def moveLibs():
    moveAllLibs(buildLibPath)
