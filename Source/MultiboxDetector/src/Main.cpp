#include <iostream>
#include "Niflect/NiflectLoadTimeModuleRegistry.h"
#include "HotSwap/RuntimeMethodHash.h"
#include "HotSwap/Plugin.h"
#include "HotSwap/HotSwap.h"
#include "Detector.h"
#include "MultiboxDetector_private.h"

#define KEY_HOTSWAP 'h'
#define KEY_DETECT 'd'
#define KEY_REPORT 'r'
#define KEY_QUIT 'q'
#define KEY_CLEAR 'c'

template <typename TMethodAddr>
static Niflect::HashInt FindMethodSignatureHash(Niflect::CNiflectType* type, TMethodAddr&& methodAddr)
{
	CRuntimeMethodHash hashToFind(methodAddr);
	for (uint32 idx = 0; idx < type->m_vecMethodInfo.size(); ++idx)
	{
		auto& method = type->m_vecMethodInfo[idx];
		if (auto nata = Niflect::CastDerivedNata<CMethodNata>(method.m_nata.Get()))
		{
			if (nata->m_methodHash == hashToFind)
				return method.m_signatureHash;
		}
	}
	return INVALID_HASH;
}
static void PrintTips()
{
	printf("Tips:\n");
	uint32 tipsCount = 0;
#ifdef WIN32
	printf(
R"(%u. (For VS users) Must launch without debugger(Ctrl+F5) - Debug mode(F5) locks PDB files, preventing debug DLL rebuild.
%u. (For VS users) Use "Debug > Attach to Process" for debugging the plugin DLL.
)", tipsCount + 1, tipsCount + 2);
	tipsCount += 2;
#endif
	printf(
R"(%u. Press [%c] then [Enter] to hot-swap.
%u. Press [%c] then [Enter] to detect.
%u. Press [%c] then [Enter] to report.
%u. Press [%c] then [Enter] to quit.
%u. Press [%c] then [Enter] to clear screen.
)", 
		tipsCount + 1, KEY_HOTSWAP,
		tipsCount + 2, KEY_DETECT,
		tipsCount + 3, KEY_REPORT,
		tipsCount + 4, KEY_QUIT, 
		tipsCount + 5, KEY_CLEAR
	);
	printf("------------------------------------------\n");
}
static void ClearConsole()
{
#ifdef _WIN32
	system("cls");
#else
	auto _ret = system("clear"); (void)_ret;
#endif
}

void CDetector::Detect(CDetectingContext& ctx) {}
void CDetector::Report(CReportingContext& ctx) {}

int main()
{
	PrintTips();

	Niflect::CNiflectModuleRegistry reg;
	reg.InitLoadTimeModules();

	{
		const char* pszPluginName = "Detector";
		CHotSwap swapper;
		swapper.Init(DEFAULT_PLUGIN_DIR_PATH, pszPluginName, "Swappable");
		bool wasCleared = false;
		bool initialOrDefault = true;
		uint32 methodIdx_Report = INDEX_NONE;
		uint32 methodIdx_Detect = INDEX_NONE;
		while (true)
		{
			bool quit = false;
			int key = 0;
			if (!initialOrDefault)
				key = std::cin.get();
			bool hotSwapping = false;
			switch (key)
			{
			case KEY_HOTSWAP:
				printf("Hot-Swapping\n");
				hotSwapping = true;
				break;
			case KEY_DETECT:
			{
				CDetectingContext detectingCtx;
				if (methodIdx_Detect != INDEX_NONE)
					swapper.InvokeBestPractice(methodIdx_Detect, detectingCtx);
				else
					printf("Method Detect not found\n");
				break;
			}
			case KEY_REPORT:
			{
				CReportingContext reportingCtx;
				if (methodIdx_Report != INDEX_NONE)
					swapper.InvokeBestPractice(methodIdx_Report, reportingCtx);
				else
					printf("Method Report not found\n");
				break;
			}
			case KEY_QUIT:
				quit = true;
				break;
			case KEY_CLEAR:
				ClearConsole();
				wasCleared = true;
				break;
			default:
				break;
			}
			if (quit)
				break;
			if (initialOrDefault)
			{
				if (wasCleared)
					wasCleared = false;
			}
			if (initialOrDefault || hotSwapping)
			{
				if (swapper.Swap())
				{
					methodIdx_Detect = INDEX_NONE;
					methodIdx_Report = INDEX_NONE;
					Niflect::TArray<SMethodBinding> vecBinding;
					auto type = Niflect::StaticGetType<CDetector>();
					vecBinding.push_back({ FindMethodSignatureHash(type, &CDetector::Detect), &methodIdx_Detect });
					vecBinding.push_back({ FindMethodSignatureHash(type, &CDetector::Report), &methodIdx_Report });
					swapper.Bind(vecBinding);
				}
				else
				{
					printf("Fail to load the plugin, please build the %s project then try again\n", pszPluginName);
				}
			}
			initialOrDefault = false;
		}
	}

	return 0;
}