if(BUILD_TEST)
  add_executable(AyonLoggerGtestMain GTestMain.cpp) 

  target_link_libraries(AyonLoggerGtestMain PRIVATE AyonCppLogger)
  target_link_libraries(AyonLoggerGtestMain PRIVATE GTest::gtest_main)


    install (
      TARGETS AyonLoggerGtestMain
      DESTINATION ${CMAKE_INSTALL_PREFIX}
    )


  add_executable(AyonLoggerGBenchMain GBenchMain.cpp) 

    target_link_libraries(AyonLoggerGBenchMain PRIVATE AyonCppLogger)
    target_link_libraries(AyonLoggerGBenchMain PRIVATE benchmark::benchmark)


    install (
      TARGETS AyonLoggerGBenchMain
      DESTINATION ${CMAKE_INSTALL_PREFIX}
    )


endif()
