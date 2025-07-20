set(SOURCES
    main.cpp
    VendingMachine.cpp
    VendingMachine.h
    )

target_sources(${PROJECT} PUBLIC ${SOURCES})
add_library(${PROJECT_LIB} STATIC ${SOURCES})
