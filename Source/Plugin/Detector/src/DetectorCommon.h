#pragma once

#ifdef WIN32
	#ifdef DETECTOR_EXPORTS
		#define DETECTOR_API __declspec(dllexport)
	#else
		#define DETECTOR_API __declspec(dllimport)
	#endif
#else
	#ifdef DETECTOR_EXPORTS
		#define DETECTOR_API __attribute__((visibility("default")))
	#else
		#define DETECTOR_API 
	#endif
#endif