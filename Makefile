.PHONY: all
all: clean configure build

.PHONY: build
build:
	cmake --build build

.PHONY: clean
clean:
	rm -rf build dist

.PHONY: configure
configure:
	cmake --preset=static -DCMAKE_BUILD_TYPE=Debug -DVCPKG_MANIFEST_FEATURES=${VCPKG_MANIFEST_FEATURES}

.PHONY: install
install:
	cmake --install build