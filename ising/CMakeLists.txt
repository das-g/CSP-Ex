# Add executable called "ising" that is built from the source files
# "ising.cpp" and "IsingLattice.cpp". The extensions are automatically found.
add_executable (ising ising IsingLattice)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ising_result.dat
	COMMAND ising > ${CMAKE_CURRENT_BINARY_DIR}/ising_result.dat
	DEPENDS ising
)

add_custom_target(driver ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/ising_result.dat)
