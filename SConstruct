from BuildConfig import *

import platform

env = Environment(CC = compilerType)

Export("env")

if isTestBuild():
    SConscript('SConscript')
else:
    SConscript(join(testDir, 'SConscript'))