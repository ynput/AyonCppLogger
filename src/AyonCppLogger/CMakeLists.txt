add_library(AyonCppLogger ${AYONCPPLOGGERLIBTYPE} AyonLogger.cpp)

target_link_libraries(AyonCppLogger PUBLIC Backward::Interface)

target_include_directories(AyonCppLogger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/spdlog)

target_include_directories(AyonCppLogger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../ext/spdlog/include)

install (
  TARGETS AyonCppLogger
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)

install (
  FILES AyonLogger.h
  DESTINATION include
) 
