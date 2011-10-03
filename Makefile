all:
	scons -j 5 .

clean:
	scons -c .
	rm -r docs

doc:
	doxygen doxygen.conf