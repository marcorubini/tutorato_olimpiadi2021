cmake_minimum_required(VERSION 3.16)
project(tutorato_olimpiadi2021)

function(add_exercise name)
  add_executable(${name} ${CMAKE_CURRENT_LIST_DIR}/${name}.cpp)
  target_compile_features(${name} PRIVATE cxx_std_11)
endfunction()

add_subdirectory(programmazione_dinamica)
add_subdirectory(grafi)
add_subdirectory(terry2018)
add_subdirectory(terry2019)
add_subdirectory(terry2020)
add_subdirectory(vari)
