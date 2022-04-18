**Early stage work in progress**

## Introduction

Alternatives:

### Bootstrap project

[`cmake-init`](https://github.com/friendlyanon/cmake-init)


### Build systems

[B2](https://www.bfgroup.xyz/b2/)

### Package managers

[vcpkg](https://github.com/microsoft/vcpkg)

[CMake `FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html)

## Questions to be answered for any component

Components: accelerator, static checker, runtime sanitizer, test
framework, individual tests, ...

For each component, need to test / verify:

1. What is a case that forces it to trigger?  When there are several
   related tools, is there a case that triggers exactly this one?
2. How do you turn it off completely?
2A. How do you turn it off for specific checks, lines of code, or
   files (as relevant)?
3. Where will its messages go? At what stage of the build?
4. What are its (command-line) options or (function) parameters?
5. How do you find the options or parameters specified for a given
   run?
6. How do you specify the options or parameters in the high level configuration?

## Tools references

### Runtime sanitizers

Address sanitizer and leak sanitizer

[UBSan behaviors](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html#ubsan-checks)

### Testers

Catch2 (Package)

[LibFuzzer home](https://llvm.org/docs/LibFuzzer.html)

[An introduction to LibFuzzer](https://www.moritz.systems/blog/an-introduction-to-llvm-libfuzzer/)

### Code coverage

`gcov`

`gcovr`

`codecov.io`

`cdash`

`OpenCppCoverage.exe`

### Code quality

LGTM / Semmle / GitHub

### Security

GitHub CodeQL

> By default, only alerts with the severity level of Error or security
> severity level of Critical or High will cause a pull request check
> failure, and a check will still succeed with alerts of lower
> severities.
> ---[Defining the severities causing pull request check failure](https://docs.github.com/en/code-security/code-scanning/automatically-scanning-your-code-for-vulnerabilities-and-errors/configuring-code-scanning#defining-the-severities-causing-pull-request-check-failure)

[Severity levels for CodeQL security alerts](https://github.blog/changelog/2021-07-19-codeql-code-scanning-new-severity-levels-for-security-alerts/)

GitHub Dependabot

### Packages

spdlog

doctopt

### Build accelerator

[ccache](https://ccache.dev/)

`ccache -s` to get ccache stats

`ccache -C` to clear entire cache

### GitHub tools

[Cache accross GitHub CI runs](https://docs.github.com/en/actions/using-workflows/caching-dependencies-to-speed-up-workflows)

### CMake components

[`cmake`](https://cmake.org/cmake/help/latest/manual/cmake.1.html)

[Static checks with CMake/CDash (iwyu, clang-tidy, lwyu, cpplint and cppcheck)](https://www.kitware.com/static-checks-with-cmake-cdash-iwyu-clang-tidy-lwyu-cpplint-and-cppcheck/)

[`__run_co_compile` argument processing source code](https://github.com/Kitware/CMake/blob/master/Source/cmcmd.cxx)

[`ctest`](https://cmake.org/cmake/help/latest/manual/ctest.1.html)

[`cpack`](https://cmake.org/cmake/help/latest/manual/cpack.1.html)

[CPack TBZ2 generator](https://cmake.org/cmake/help/latest/cpack_gen/archive.html)

#### CMake Modules

[`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html)s

[`CPack`](https://cmake.org/cmake/help/latest/module/CPack.html)

### Formatting

`clang-format`

## The static checks (in order)

Every compilation:

1. clang-tidy
2. cppcheck
3. Compiler

Upon push to GitHub:

4. CodeQL security scan (BADGE, alert)
5. LGTM code complexity (BADGE)

Occasionally, in background:

6. Dependabot (Alert)
7. CodeQL security scan (Alert)

Plus: code coverage by [Codecov](https://codecov.io) (BADGE)

## The build accelerators

ccache

precompiled headers / modules

conan / vcpkg

make / ninja / ... (Only recompiling when out of date)

GitHub cache

## The tests

### Upon push to GitHub:

Unit tests

Unit tests of command line

### Ongoing, in background:

Fuzz tests

## Questions to ask

### Static checkers

1. How are the options passed to the compiler (such as include file
   directories or warnings-as-errors) passed to the checker?

### Build tool

Accelerators?

How do you specify the following compiler options:

1. Optimization level
2. Warnings
3. Warnings as errors
4. Sanitizers
5. Debugging information

Can you group related option sets (for example, debugging information
with low optimizations for a "debug" configuration)?

Specify build directories

### Package tool

1. What package format(s) do you want?

### CI Tool
