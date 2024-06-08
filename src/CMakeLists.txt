cmake_minimum_required( VERSION 3.10 )
project( homework4 VERSION 0.1.1 )
add_executable( print_ip ip_printer.cpp )
add_executable( test_print_ip test_print_ip.cpp )

# package part which enales
# run: cmake --build . --target package
install(TARGETS print_ip RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
set(CPACK_PACKAGE_CONTACT berrendej@gmail.com)
include(CPack)

#testing part which enables
# cmake --build . --target test
enable_testing()
add_test(tst_print_ip  test_print_ip) 