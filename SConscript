from BuildConfig import *


Import('env')

srcEnv = env.Clone()

setupEnv(srcEnv)

builtLibs = []

# Build all modules within the source directory
for dir in srcModules:
	sources = Glob(join(srcDir, dir, '*.cpp'))
	objects = []

	libPath = join(buildPath, dir)

	lib = srcEnv.SharedLibrary(libPath, sources)
	
	builtLibs.append(lib)
	
# Compile the remaining source files and create a program using the above libs
sources = Glob(join(srcDir, '*.cpp'))

srcEnv.Program(join(buildPath, programName), sources, LIBS=builtLibs)