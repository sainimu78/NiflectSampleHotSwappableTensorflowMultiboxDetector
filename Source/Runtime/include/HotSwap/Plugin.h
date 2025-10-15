#pragma once
#include "Niflect/NiflectLoadTimeModuleRegistry.h"

#ifdef WIN32
#define CPF_PLATFORM_OS_NAME "Windows"
#define CPF_FINAL_OUTPUT_DIR_NAME "bin"
#else
#define CPF_PLATFORM_OS_NAME "Linux"
#define CPF_FINAL_OUTPUT_DIR_NAME "lib"
#endif
#ifdef NDEBUG
#define CPF_CONFIG_NAME "Release"
#else
#define CPF_CONFIG_NAME "Debug"
#endif

#define DEFAULT_PLUGIN_DIR_PATH "../../Plugin/" CPF_PLATFORM_OS_NAME "/DefaultBuild/" CPF_CONFIG_NAME "/" CPF_FINAL_OUTPUT_DIR_NAME