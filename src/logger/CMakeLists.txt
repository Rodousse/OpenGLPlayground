set(LOGGER_SRC
    logger/Logger.cpp)

set(LOGGER_HEADERS
    logger/Logger.hpp)


add_library(logger ${LOGGER_SRC} ${LOGGER_HEADERS})

generate_export_header(logger
  EXPORT_MACRO_NAME LOGGER_API
  EXPORT_FILE_NAME ${GENERATED_DIR}/LoggerSymbols.h
)

set(LOGGER_STATIC_FLAG "")
if(BUILD_SHARED_LIBS)
    set(LOGGER_STATIC_FLAG "LOGGER_STATIC_DEFINE")
endif()
target_include_directories(logger
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${GENERATED_DIR}>)
target_link_libraries(logger PRIVATE spdlog::spdlog)
target_compile_definitions(logger PUBLIC ${LOGGER_STATIC_FLAG} _USE_MATH_DEFINES _ENABLE_EXTENDED_ALIGNED_STORAGE PRIVATE LOGGER_EXPORT)

