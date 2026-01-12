#include "pch.h"

#include "ReactPackageProvider.h"
#if __has_include("ReactPackageProvider.g.cpp")
#include "ReactPackageProvider.g.cpp"
#endif

#include "ReactNativeWebview.h"

#ifdef RNW_NEW_ARCH
#include "RCTWebView2ComponentView.h"
#endif

using namespace winrt::Microsoft::ReactNative;

namespace winrt::ReactNativeWebView::implementation
{

void ReactPackageProvider::CreatePackage(IReactPackageBuilder const &packageBuilder) noexcept
{
  // --- Diagnostic logging for Issue #16 ---
  OutputDebugStringW(L"[RNW-WebView] CreatePackage called\n");

  // Log which module this code is running from (detect wrong-DLL scenarios)
  {
    wchar_t modulePath[MAX_PATH] = {};
    HMODULE hModule = nullptr;
    if (GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           reinterpret_cast<LPCWSTR>(&ReactPackageProvider::CreatePackage), &hModule)) {
      GetModuleFileNameW(hModule, modulePath, MAX_PATH);
    }
    wchar_t msg[512];
    swprintf_s(msg, L"[RNW-WebView] Module path: %s\n", modulePath[0] ? modulePath : L"<unknown>");
    OutputDebugStringW(msg);
  }

  // Log compile-time macros
#ifdef RNW_NEW_ARCH
  OutputDebugStringW(L"[RNW-WebView] RNW_NEW_ARCH = DEFINED\n");
#else
  OutputDebugStringW(L"[RNW-WebView] RNW_NEW_ARCH = NOT DEFINED (Fabric path SKIPPED!)\n");
#endif

#ifdef USE_WINUI3
  OutputDebugStringW(L"[RNW-WebView] USE_WINUI3 = DEFINED\n");
#else
  OutputDebugStringW(L"[RNW-WebView] USE_WINUI3 = NOT DEFINED\n");
#endif
  // --- End diagnostic logging ---

  AddAttributedModules(packageBuilder, true);

#ifdef RNW_NEW_ARCH
  OutputDebugStringW(L"[RNW-WebView] Calling RegisterRCTWebView2ComponentView...\n");
  RegisterRCTWebView2ComponentView(packageBuilder);
  OutputDebugStringW(L"[RNW-WebView] RegisterRCTWebView2ComponentView returned\n");
#endif
}

} // namespace winrt::ReactNativeWebView::implementation
