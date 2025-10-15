set(ModuleName Detector)

set(ModuleRootPath ${c_RootSourceDirPath}/Plugin/${ModuleName})
set(ModuleSourcePath ${ModuleRootPath}/src)
set(ModuleIncludePath ${ModuleRootPath}/include)

set(IncludePathsPrivate "")
set(IncludePathsPublic "")
list(APPEND IncludePathsPrivate ${ModuleSourcePath})
list(APPEND IncludePathsPublic ${ModuleIncludePath})

file(GLOB_RECURSE ModuleSources ${ModuleSourcePath}/*.cpp ${ModuleSourcePath}/*.h)
create_source_group(${ModuleSourcePath} ${ModuleSources})
file(GLOB_RECURSE ModuleHeaders ${ModuleIncludePath}/*.h)
create_source_group(${ModuleIncludePath} ${ModuleHeaders})
set(SrcAll "")
list(APPEND SrcAll ${ModuleSources})
list(APPEND SrcAll ${ModuleHeaders})

add_library(${ModuleName} SHARED ${SrcAll})

# Required by libtensorflow_cc
set_target_properties(${ModuleName} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_precompile_headers(${ModuleName} PRIVATE ${ModuleSourcePath}/${ModuleName}Common.h)

target_include_directories(${ModuleName}
	PRIVATE ${IncludePathsPrivate}
	PUBLIC ${IncludePathsPublic}
)

target_compile_definitions(${ModuleName} PRIVATE -DDETECTOR_EXPORTS)

ngt_target_link_libraries(${ModuleName} PRIVATE Runtime)

include(${c_RootProjectDirPath}/Plugin/${ModuleName}/Licensed_TensorFlow.cmake)

list(APPEND v_ListModuleHeaderFilePath ${ModuleHeaders})
set(v_EnabledLoadTimeModuleRegistrar TRUE)
include(${c_RootProjectDirPath}/Niflect/Default.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${ModuleName})
else()
endif()