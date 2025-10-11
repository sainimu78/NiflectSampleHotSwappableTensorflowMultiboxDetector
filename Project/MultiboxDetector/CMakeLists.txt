cmake_minimum_required(VERSION 3.10.0)

include(../InitRootPath.cmake)

set(c_ProjectName MultiboxDetector)

include(${c_RootCMakeProjectFrameworkDirPath}/ProjectBegin.cmake)
set(CMAKE_CXX_STANDARD 17)
project(${c_ProjectName})
include(${c_RootCMakeProjectFrameworkDirPath}/ProjectEnd.cmake)

include(${c_RootCMakeProjectFrameworkDirPath}/InitCMakeTargetOutputDirPaths.cmake)

set(ModuleName ${c_ProjectName})

set(ModuleRootPath ${c_RootSourceDirPath}/${ModuleName})
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

add_executable(${ModuleName} ${SrcAll})

target_include_directories(${ModuleName}
	PRIVATE ${IncludePathsPrivate}
	PUBLIC ${IncludePathsPublic}
)

#get_filename_component(TensorFlowRootDirPath "${c_RootDirPath}/../../out" ABSOLUTE)
#target_include_directories(${ModuleName} PRIVATE 
#    ${TensorFlowRootDirPath}/include
#    ${TensorFlowRootDirPath}/include/third_party/xla
#    ${TensorFlowRootDirPath}/include/third_party/xla/third_party/tsl
#    ${TensorFlowRootDirPath}/include/bazel-tensorflow/external/ml_dtypes_py
#    ${TensorFlowRootDirPath}/include/external/local_xla
#)
#target_link_libraries(${ModuleName} PRIVATE
#    ${TensorFlowRootDirPath}/lib/libtensorflow_cc.so
#	${TensorFlowRootDirPath}/lib/libtensorflow_framework.so
#)
	
list(APPEND v_ListModuleHeaderFilePath ${ModuleHeaders})
list(APPEND v_ListAccessorSettingHeaderFilePath ${ModuleSourcePath}/AccessorSetting.h)
set(v_EnabledLoadTimeModuleRegistrar TRUE)
include(${c_RootThirdPartyDirPath}/Niflect/Shared.cmake)
include(${c_RootThirdPartyDirPath}/NiflectGenTool/Exe.cmake)
include(Licensed_TensorFlow.cmake)

include(${c_ProjectDirPath}/Install.cmake)

if(MSVC)
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${ModuleName})
endif()

if(MSVC)
	set_target_properties(${ModuleName} PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "$<IF:$<CONFIG:Debug>,${c_ProjectBinDirPathDebug},${c_ProjectBinDirPathRelease}>"
	)
endif()

include(${c_RootCMakeProjectFrameworkDirPath}/Release.cmake)
include(${c_RootCMakeProjectFrameworkDirPath}/Cleanup.cmake)