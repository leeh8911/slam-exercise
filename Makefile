PROJECT_NAME = $(notdir $(CURDIR))
release = release
debug = "debug"

ifeq ($(config), release) 
	config = Release
else
	config = Debug
endif

.PHONY: conan_install
conan_install:
	mkdir build || \
	cd build && \
	conan install .. -s build_type=Release --build=missing && \
	conan install .. -s build_type=Debug --build=missing

.PHONY: format
format:
	clang-format src/**/*.cpp src/**/*.h test/**/*.cpp -i

.PHONY: build-test
build-test: conan_install
	mkdir build || \
	cd build && \
	cmake .. -DCMAKE_CONFIGURATION_TYPES=Debug;Release -DBUILD_EXAPLE=OFF -DBUILD_TEST=ON -DBUILD_DOC=OFF && \
	cmake --build .

.PHONY: build-example
build-example: conan_install
	mkdir build || \
	cd build && \
	cmake .. -DCMAKE_CONFIGURATION_TYPES=Debug;Release -DBUILD_EXAPLE=ON -DBUILD_TEST=OFF -DBUILD_DOC=OFF && \
	cmake --build .

.PHONY: run-test
run-test:
	cd build && \
	bin\$(PROJECT_NAME)_test.exe

.PHONY: test
test: build-test run-test

.PHONY: run-example
run-example:
	cd build && \
	bin\ad_framework_example1.exe
	
.PHONY: example
example: build-example run-example

.PHONY: build-doc
build-doc: conan_install
	mkdir build || \
	cd build && \
	cmake .. -DCMAKE_CONFIGURATION_TYPES=Debug;Release -DBUILD_EXAPLE=OFF -DBUILD_TEST=OFF -DBUILD_DOC=ON && \
	cmake --build .

.PHONY: doc
doc: build-doc
