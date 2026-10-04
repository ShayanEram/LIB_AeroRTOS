cmake_minimum_required(VERSION 3.10)
project(AeroRTOS VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# 1. Run Python Config Generator
# -----------------------------
execute_process(
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/config.py
            ${CMAKE_CURRENT_SOURCE_DIR}/config.yaml
            ${CMAKE_CURRENT_SOURCE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# -----------------------------
# 2. Build Unified RTOS Shared Library
# -----------------------------
add_library(rtos SHARED
    # Core ARINC 653
    RTOS/ARINC653/Src/error.c
    RTOS/ARINC653/Src/ipc_queueing.c
    RTOS/ARINC653/Src/ipc_sampling.c
    RTOS/ARINC653/Src/partition.c
    RTOS/ARINC653/Src/process.c
    RTOS/ARINC653/Src/scheduler.c

    # Generated RTOS Startup Logic (contains start_rtos())
    Runner/start_rtos.c
)

# -----------------------------
# 3. Export Header Directories
# -----------------------------
target_include_directories(rtos PUBLIC
    RTOS/ARINC653/Inc
    Runner
)

# -----------------------------
# 4. System Libraries
# -----------------------------
target_link_libraries(rtos PRIVATE pthread rt)