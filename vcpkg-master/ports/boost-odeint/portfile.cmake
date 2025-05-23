# Automatically generated by scripts/boost/generate-ports.ps1

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO boostorg/odeint
    REF boost-${VERSION}
    SHA512 c7c3ddb96944efbd59db751c6ad2f49dba809cb5aa8730c68816c7119cdbcb57d49e733340958d7b516dc193b4c54a56e04ee81e788575b398a2d96ab9f2fb5d
    HEAD_REF master
    PATCHES
        opt-mpi.diff
)

set(FEATURE_OPTIONS "")
include("${CMAKE_CURRENT_LIST_DIR}/features.cmake")
boost_configure_and_install(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS ${FEATURE_OPTIONS}
)
