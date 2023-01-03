#file(GLOB_RECURSE my_c_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")

file(GLOB my_cpp_list
     "*.cpp"
)

foreach(file_path ${my_cpp_list})
  string( REPLACE ".cpp" "" new_name ${file_path} )
  get_filename_component(executable_name ${new_name} NAME)
  #add_executable( ${executable_name} ${file_path} )

  set(executable_name "${executable_name}Test")

  add_unit_test(NAME ${executable_name}
      SOURCES ${file_path}
          LIBS Catch2::Catch2WithMain)

  include(Catch)
  catch_discover_tests(${executable_name})
endforeach()
