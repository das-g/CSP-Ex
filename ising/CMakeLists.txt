# Add executable called "ising" that is built from the source files
# "ising.cpp" and "IsingLattice.cpp". The extensions are automatically found.
add_executable (ising ising IsingLattice)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size.dat
	COMMAND ising
	DEPENDS ising
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.png ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size.png
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/plots.py
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/plots.py ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size.dat
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(plots ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.png)
# the ALL option causes this target to be built when "make" is run from the toplevel
