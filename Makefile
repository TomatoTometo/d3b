SRC_DIR=$(CURDIR)/src
BUILD_DIR=$(CURDIR)/build

######################################################################
.PHONY: setup-relwithdebinfo
setup-relwithdebinfo:
		mkdir -p $(BUILD_DIR)/relwithdebinfo && \
		cmake -B $(BUILD_DIR)/relwithdebinfo \
		-DCMAKE_BUILD_TYPE=RelWithDebInfo && \
		cmake --install $(BUILD_DIR)/relwithdebinfo

.PHONY: setup-debug
setup-debug:
		mkdir -p $(BUILD_DIR)/debug && \
		cmake -B $(BUILD_DIR)/debug \
		-DCMAKE_BUILD_TYPE=Debug && \
		cmake --install $(BUILD_DIR)/debug

.PHONY: setup-release
setup-release:
		mkdir -p $(BUILD_DIR)/release && \
		cmake -B $(BUILD_DIR)/release \
		-DCMAKE_BUILD_TYPE=Release && \
		cmake --install $(BUILD_DIR)/release

.PHONY: setup
setup: setup-relwithdebinfo setup-debug setup-release

######################################################################
.PHONY: relwithdebinfo
relwithdebinfo:
		cmake --build $(BUILD_DIR)/relwithdebinfo

.PHONY: debug
debug:
		cmake --build $(BUILD_DIR)/debug --config debug

.PHONY: release
release:
		cmake --build $(BUILD_DIR)/release --config release

.PHONY: all
all: relwithdebinfo debug delease

.PHONY: clean
clean:
		rm -rf build
