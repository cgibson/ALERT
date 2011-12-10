from BuildConfig import *

import platform

env = Environment(CC = compilerType)
    
# Set up environment to be receptive to shared objects in the ../lib directory
env.Append( LINKFLAGS = Split('-z origin') )
env.Append( RPATH = env.Literal(os.path.join('\\$$ORIGIN', os.pardir, 'lib')))

# Do everything else
Export("env")

if isLibRebuild():
    print "Rebuilding Libs"
    rebuildLibs()
else:
    
    if not isTestBuild():
        SConscript('SConscript')
    else:
        SConscript(join(testPath, 'SConscript'))
