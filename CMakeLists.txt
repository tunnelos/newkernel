cmake_minimum_required(VERSION 3.20.0)

project(tunnelos LANGUAGES C)

enable_language(ASM)

set(CMAKE_C_FLAGS "-ffreestanding -O0 -g -Wall -Wextra -no-pie -fno-pic -m32 -nostdlib -Wunused-parameter")
set(CMAKE_CXX_FLAGS "-ffreestanding -O0 -g -Wall -Wextra -no-pie -fno-pic -m32 -nostdlib")
set(CMAKE_EXE_LINKER_FLAGS "-m32 -T${CMAKE_CURRENT_LIST_DIR}/src/link.ld -nostdlib")
set(CMAKE_ASM_FLAGS "-m32 -T${CMAKE_CURRENT_LIST_DIR}/src/link.ld")

file(GLOB_RECURSE application_bootscreen "src/application_bootscreen/*.c")
file(GLOB_RECURSE application_help "src/application_help/*.c")
file(GLOB_RECURSE application_terminal "src/application_terminal/*.c")
file(GLOB_RECURSE application_enableints "src/applications_enableints/*.c")
file(GLOB_RECURSE application_lsblk "src/application_lsblk/*.c")

add_library(libapplication_bootscreen STATIC ${application_bootscreen})
add_library(libapplication_help STATIC ${application_help})
add_library(libapplication_terminal STATIC ${application_terminal})
add_library(libapplication_enableints STATIC ${application_enableints})
add_library(libapplication_lsblk STATIC ${application_lsblk})

file(GLOB_RECURSE kernel_base "src/base/*.c")
file(GLOB_RECURSE kernel_boot "src/boot/*.s")
file(GLOB_RECURSE kernel_cpu "src/cpu/*.s" "src/cpu/*.c")

file(GLOB_RECURSE kernel_drivers_base "src/drivers/*/*.c")

file(GLOB_RECURSE kernel_etc "src/etc/*.c")

file(GLOB_RECURSE kernel_std "src/std/*.c")

add_library(libkernel_std STATIC ${kernel_std})

add_library(libkernel_drivers_base ${kernel_drivers_base})

include_directories(src/include)

add_executable(kernel.elf
    ${kernel_boot} ${kernel_base} ${kernel_cpu} ${kernel_etc}
)

target_link_libraries(libkernel_drivers_base libkernel_std)

target_link_libraries(libapplication_terminal libapplication_bootscreen libapplication_help libapplication_enableints libapplication_lsblk)

target_link_libraries(kernel.elf libapplication_terminal libkernel_std libkernel_drivers_base)

# ADD_CUSTOM_COMMAND (TARGET kernel.img
# 	POST_BUILD
# 	COMMAND "ld -m elf_i386 -T${CMAKE_CURRENT_LIST_DIR}/src/link.ld -o ${CMAKE_BINARY_DIR}/phOS.img ${CMAKE_BINARY_DIR}/kernel.elf"
# )
