# Add executable called "ising" that is built from the source files
# "ising.cpp" and "IsingLattice.cpp". The extensions are automatically found.
add_executable (ising ising IsingSimulation IsingLattice)
add_executable (fss finite_size_scaling IsingSimulation IsingLattice)

link_directories(${CSP_EXERCISES_BINARY_DIR}/binning)
target_link_libraries(ising CStat)
target_link_libraries(fss CStat)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size.dat
	COMMAND ising
	DEPENDS ising
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/max_chi_vs_N.dat ${CMAKE_CURRENT_BINARY_DIR}/data_collapse.dat
	COMMAND fss
	DEPENDS fss
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.png ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size.png
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/ex01plots.py
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ex01plots.py ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size.dat
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/max_chi_vs_N.png ${CMAKE_CURRENT_BINARY_DIR}/data_collapse-0.595.png  ${CMAKE_CURRENT_BINARY_DIR}/data_collapse0.0.png  ${CMAKE_CURRENT_BINARY_DIR}/data_collapse0.75.png
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/ex03plots.py
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ex03plots.py ${CMAKE_CURRENT_BINARY_DIR}/max_chi_vs_N.dat ${CMAKE_CURRENT_BINARY_DIR}/data_collapse.dat
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(ex01 ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.png ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size.png)
add_custom_target(ex03 ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/max_chi_vs_N.png  ${CMAKE_CURRENT_BINARY_DIR}/data_collapse-0.595.png  ${CMAKE_CURRENT_BINARY_DIR}/data_collapse0.0.png  ${CMAKE_CURRENT_BINARY_DIR}/data_collapse0.75.png)
# the ALL option causes these targets to be built when "make" is run from the toplevel
