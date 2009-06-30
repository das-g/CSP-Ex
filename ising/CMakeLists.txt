# Add executable called "ising" that is built from the source files
# "ising.cpp" and "IsingLattice.cpp". The extensions are automatically found.
add_executable (ising ising IsingSimulation IsingLattice)

link_directories(${CSP_EXERCISES_BINARY_DIR}/binning)
target_link_libraries(ising CStat)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_max_deamon_energy.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_energy.dat # + hist_*.dat
	COMMAND ising
	DEPENDS ising
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.png ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT_2.png # + hist_*.dat.png
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/plots.py
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/plots.py ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_max_deamon_energy.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_energy.dat
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(plots ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.png ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT_2.png)  # + hist_*.dat.png
# the ALL option causes this target to be built when "make" is run from the toplevel
