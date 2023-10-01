cmake_minimum_required(VERSION 3.20.0)

project(tunnelos LANGUAGES C)

enable_language(ASM)

set(CMAKE_C_FLAGS "-ffreestanding -O0 -g -Wall -Wextra -no-pie -fno-pic -m32 -nostdlib -Wunused-parameter")
set(CMAKE_CXX_FLAGS "-ffreestanding -O0 -g -Wall -Wextra -no-pie -fno-pic -m32 -nostdlib")
set(CMAKE_EXE_LINKER_FLAGS "-m32 -T${CMAKE_CURRENT_LIST_DIR}/src/link.ld -nostdlib")
set(CMAKE_ASM_FLAGS "-m32 -T${CMAKE_CURRENT_LIST_DIR}/src/link.ld")

set(BUILD_SHARED_AND_STATIC_LIBS ON)
# set(CJSON_LIBRARY_TYPE STATIC)
SET(ENABLE_CJSON_TEST OFF)
add_subdirectory(src/external/cJSON)

# file(GLOB_RECURSE application_bootscreen CONFIGURE_DEPENDS "src/application_bootscreen/*.c")
# file(GLOB_RECURSE application_help CONFIGURE_DEPENDS "src/application_help/*.c")
# file(GLOB_RECURSE application_terminal CONFIGURE_DEPENDS "src/application_terminal/*.c")
# file(GLOB_RECURSE application_enableints CONFIGURE_DEPENDS "src/applications_enableints/*.c")
# file(GLOB_RECURSE application_lsblk CONFIGURE_DEPENDS "src/application_lsblk/*.c")
# file(GLOB_RECURSE application_clear CONFIGURE_DEPENDS "src/application_clear/*.c")
# file(GLOB_RECURSE application_memusage CONFIGURE_DEPENDS "src/application_memusage/*.c")
file(GLOB_RECURSE kernel_vectors CONFIGURE_DEPENDS "src/vector_*/*.c")

# add_library(libapplication_bootscreen STATIC ${application_bootscreen})
# add_library(libapplication_help STATIC ${application_help})
# add_library(libapplication_terminal STATIC ${application_terminal})
# add_library(libapplication_enableints STATIC ${application_enableints})
# add_library(libapplication_lsblk STATIC ${application_lsblk})
# add_library(libapplication_clear STATIC ${application_clear})
# add_library(libapplication_memusage STATIC ${application_clear})

file(GLOB_RECURSE applications CONFIGURE_DEPENDS "src/application_*/*.c")
add_library(libapplications STATIC ${applications})

add_library(libkernel_vectors STATIC ${kernel_vectors})

file(GLOB_RECURSE kernel_base CONFIGURE_DEPENDS "src/base/*.c")
file(GLOB_RECURSE kernel_boot CONFIGURE_DEPENDS "src/boot/*.s")
file(GLOB_RECURSE kernel_cpu CONFIGURE_DEPENDS "src/cpu/*.s" "src/cpu/*.c")

file(GLOB_RECURSE kernel_drivers_base CONFIGURE_DEPENDS "src/drivers/*/*.c")

file(GLOB_RECURSE kernel_etc CONFIGURE_DEPENDS "src/etc/*.c" "src/etc/embeddable/*/*.c")

file(GLOB_RECURSE kernel_std CONFIGURE_DEPENDS "src/std/*.c")

add_library(libkernel_std STATIC ${kernel_std})

target_link_libraries(libkernel_vectors libkernel_std)

add_library(libkernel_drivers_base STATIC ${kernel_drivers_base})

include_directories(src/include src/external/cJSON)

add_executable(kernel.elf
    ${kernel_boot} ${kernel_base} ${kernel_cpu} ${kernel_etc}
)

set (CJSON_LIBRARY_PATH ${CMAKE_BINARY_DIR}/src/external/cJSON/libcjson.a)

message(NOTICE ${CJSON_LIBRARY_PATH})

target_link_libraries(libapplications libkernel_std libkernel_drivers_base libkernel_vectors)

# target_link_libraries(libapplication_help ${CJSON_LIBRARY_PATH})

# target_link_libraries(libkernel_drivers_base libkernel_std)

# target_link_libraries(libapplication_clear libkernel_drivers_base)

# target_link_libraries(libapplication_terminal libapplication_bootscreen libapplication_help libapplication_enableints libapplication_lsblk libapplication_clear libkernel_vectors)

target_link_libraries(kernel.elf libapplications)

# ADD_CUSTOM_COMMAND (TARGET kernel.img
# 	POST_BUILD
# 	COMMAND "ld -m elf_i386 -T${CMAKE_CURRENT_LIST_DIR}/src/link.ld -o ${CMAKE_BINARY_DIR}/phOS.img ${CMAKE_BINARY_DIR}/kernel.elf"
# )
