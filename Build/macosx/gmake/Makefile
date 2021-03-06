# GNU Make workspace makefile autogenerated by Premake

.NOTPARALLEL:

ifndef config
  config=debug_x32
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug_x32)
  bundle_config = debug_x32
  yaml_cpp_config = debug_x32
  ris_test_config = debug_x32
  ris_config = debug_x32
  ris_acceptance_test_config = debug_x32
endif
ifeq ($(config),debug_x64)
  bundle_config = debug_x64
  yaml_cpp_config = debug_x64
  ris_test_config = debug_x64
  ris_config = debug_x64
  ris_acceptance_test_config = debug_x64
endif
ifeq ($(config),debug_native)
  bundle_config = debug_native
  yaml_cpp_config = debug_native
  ris_test_config = debug_native
  ris_config = debug_native
  ris_acceptance_test_config = debug_native
endif
ifeq ($(config),release_x32)
  bundle_config = release_x32
  yaml_cpp_config = release_x32
  ris_test_config = release_x32
  ris_config = release_x32
  ris_acceptance_test_config = release_x32
endif
ifeq ($(config),release_x64)
  bundle_config = release_x64
  yaml_cpp_config = release_x64
  ris_test_config = release_x64
  ris_config = release_x64
  ris_acceptance_test_config = release_x64
endif
ifeq ($(config),release_native)
  bundle_config = release_native
  yaml_cpp_config = release_native
  ris_test_config = release_native
  ris_config = release_native
  ris_acceptance_test_config = release_native
endif

PROJECTS := bundle yaml-cpp ris-test ris ris-acceptance-test

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

bundle:
ifneq (,$(bundle_config))
	@echo "==== Building bundle ($(bundle_config)) ===="
	@${MAKE} --no-print-directory -C . -f bundle.make config=$(bundle_config)
endif

yaml-cpp:
ifneq (,$(yaml_cpp_config))
	@echo "==== Building yaml-cpp ($(yaml_cpp_config)) ===="
	@${MAKE} --no-print-directory -C . -f yaml-cpp.make config=$(yaml_cpp_config)
endif

ris-test: bundle yaml-cpp
ifneq (,$(ris_test_config))
	@echo "==== Building ris-test ($(ris_test_config)) ===="
	@${MAKE} --no-print-directory -C . -f ris-test.make config=$(ris_test_config)
endif

ris: bundle yaml-cpp
ifneq (,$(ris_config))
	@echo "==== Building ris ($(ris_config)) ===="
	@${MAKE} --no-print-directory -C . -f ris.make config=$(ris_config)
endif

ris-acceptance-test: bundle yaml-cpp
ifneq (,$(ris_acceptance_test_config))
	@echo "==== Building ris-acceptance-test ($(ris_acceptance_test_config)) ===="
	@${MAKE} --no-print-directory -C . -f ris-acceptance-test.make config=$(ris_acceptance_test_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f bundle.make clean
	@${MAKE} --no-print-directory -C . -f yaml-cpp.make clean
	@${MAKE} --no-print-directory -C . -f ris-test.make clean
	@${MAKE} --no-print-directory -C . -f ris.make clean
	@${MAKE} --no-print-directory -C . -f ris-acceptance-test.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug_x32"
	@echo "  debug_x64"
	@echo "  debug_native"
	@echo "  release_x32"
	@echo "  release_x64"
	@echo "  release_native"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   bundle"
	@echo "   yaml-cpp"
	@echo "   ris-test"
	@echo "   ris"
	@echo "   ris-acceptance-test"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
