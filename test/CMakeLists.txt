enable_testing()

add_executable(TestVecteursEtAutres
    testVecteur.cxx
    testCellule.cxx
    testParticule.cxx
)

add_executable(testConditionsLimites
    testConditionsLimites.cxx
)

target_link_libraries(TestVecteursEtAutres
    gtest_main
    simulation
)

target_link_libraries(testConditionsLimites
    gtest_main
    simulation
)

include(GoogleTest)
gtest_discover_tests(TestVecteursEtAutres)
gtest_discover_tests(testConditionsLimites)
