set(SOURCES
    main.cpp
    Coin.cpp
    Coin.h
    CoinStore.cpp
    CoinStore.h
    VendingMachine.cpp
    VendingMachine.h
    )

target_sources(${PROJECT} PUBLIC ${SOURCES})
add_library(${PROJECT_LIB} STATIC ${SOURCES})
