from BuildConfig import *

import platform

env = Environment(CC = compilerType)

Export("env")

if not isTestBuild():
    SConscript('SConscript')
else:
    SConscript(join(testDir, 'SConscript'))