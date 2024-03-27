(use-modules (guix packages)
	     (gnu packages llvm))
(specifications->manifest
 (list
  "coreutils"
  "libgccjit"
  "make"
  "bison"
  "clang-toolchain"
  "valgrind"))
