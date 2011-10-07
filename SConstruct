from BuildConfig import *

import platform

env = Environment(CC = compilerType)

Export("env")

SConscript(join(testDir, 'SConscript'))

if not isTestBuild():
    SConscript('SConscript')