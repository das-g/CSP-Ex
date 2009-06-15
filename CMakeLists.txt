# The name of our project is "CSP_EXERCISES". CMakeLists files in this project can
# refer to the root source directory of the project as ${CSP_EXERCISES_SOURCE_DIR} and
# to the root binary directory of the project as ${CSP_EXERCISES_BINARY_DIR}.
cmake_minimum_required (VERSION 2.6)
project (CSP_EXERCISES)

# Recurse into the "ising"subdirectory. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (ising)
add_subdirectory (binning)
