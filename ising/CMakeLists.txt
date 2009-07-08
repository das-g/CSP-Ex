# Add executable called "ising" that is built from the source files
# "ising.cpp" and "IsingLattice.cpp". The extensions are automatically found.
add_executable (single_flip single_flip IsingSimulation  IsingLattice)
add_executable (wolff wolff IsingSimulation WolffIsingSimulation IsingLattice)
add_executable (binning_analysis binning_analysis IsingSimulation WolffIsingSimulation IsingLattice)

link_directories(${CSP_EXERCISES_BINARY_DIR}/binning)
target_link_libraries(single_flip CStat)
target_link_libraries(wolff CStat)
target_link_libraries(binning_analysis CStat)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT_single_flip.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size_single_flip.dat
	COMMAND single_flip
	DEPENDS single_flip
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT_wolff.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size_wolff.dat
	COMMAND wolff
	DEPENDS wolff
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/binning_single_flip.dat ${CMAKE_CURRENT_BINARY_DIR}/binning_wolff.dat
	COMMAND binning_analysis
	DEPENDS binning_analysis
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.png ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size.png
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/plots.py
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/plots.py ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT_single_flip.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size_single_flip.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT_wolff.dat ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size_wolff.dat
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/binning_analysis.png
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/binning_plots.py
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/binning_plots.py ${CMAKE_CURRENT_BINARY_DIR}/binning_single_flip.dat ${CMAKE_CURRENT_BINARY_DIR}/binning_wolff.dat
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(plots ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_kT.png ${CMAKE_CURRENT_BINARY_DIR}/everything_vs_system_size.png ${CMAKE_CURRENT_BINARY_DIR}/binning_analysis.png)
# the ALL option causes this target to be built when "make" is run from the toplevel
