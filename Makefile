all:
	scons -j 5 .

tests:
	scons -j 5 test=1

clean:
	scons -c .
	rm -r docs
	rm -r build

doc:
	doxygen doxygen.conf

test-lua:
	./build/test/luabind/suites
