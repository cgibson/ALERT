import os
import sys

from SCons.Script import *
from os.path import join
from os import path

#------------------------------------------------------------------------------#

programName = 'AleRT'

programPath = '.'

compilerType = 'g++'

buildPath = "build"

# No source besides include files and test files should exist outside of here
srcDir = "src"

# Test directory
testDir = "test"

# These lie under the source directory
srcModules = [
              "geom",
              "util"
             ]

testModules = [
               "glm"
              ]

# Paths to include from
sysIncludePaths = [
                   'include',
                   'glm'
                  ]

# Paths containing libraries
sysLibPaths = [
               'lib'
              ]

# Libraries to reference
sysLibs = [
           'boost_thread-mt'
          ]

#------------------------------------------------------------------------------#
def isDebugBuild():
    return ARGUMENTS.get('debug', 0)


#------------------------------------------------------------------------------#
def setupEnv(env, pathToRoot = "."):
    
    applyDir = lambda x, y: "%s/%s" % (x, y);
    
    # Include paths
    env.Append(CPPPATH = sysIncludePaths)
    
    # Library paths
    env.Append(LIBPATH = sysLibPaths)
    
    # Libraries
    env.Append(LIBS = sysLibs)
    
    if isDebugBuild():
        env.Append(CCFLAGS = ["-g"])
        
        
#------------------------------------------------------------------------------#
def initialize(pathToRoot = "."):
    
    env = Environment(CC = 'g++')
    
    setupEnv(env, pathToRoot)
    
    conf = Configure(env)
    
    return env, conf
    