#include "MSALWrapper.h"

// 定义函数指针变量
MSALRUNTIME_Startup_Ptr fn_MSALRUNTIME_Startup = NULL;
MSALRUNTIME_AcquireTokenSilentlyAsync_Ptr fn_MSALRUNTIME_AcquireTokenSilentlyAsync = NULL;
MSALRUNTIME_SetIsPiiEnabled_Ptr fn_MSALRUNTIME_SetIsPiiEnabled = NULL;
MSALRUNTIME_CreateAuthParameters_Ptr fn_MSALRUNTIME_CreateAuthParameters = NULL;
MSALRUNTIME_SetRequestedScopes_Ptr fn_MSALRUNTIME_SetRequestedScopes = NULL;
MSALRUNTIME_SetRedirectUri_Ptr fn_MSALRUNTIME_SetRedirectUri = NULL;
MSALRUNTIME_SetAdditionalParameter_Ptr fn_MSALRUNTIME_SetAdditionalParameter = NULL;
MSALRUNTIME_ReleaseAsyncHandle_Ptr fn_MSALRUNTIME_ReleaseAsyncHandle = NULL;
MSALRUNTIME_ReleaseAuthParameters_Ptr fn_MSALRUNTIME_ReleaseAuthParameters = NULL;
MSALRUNTIME_DiscoverAccountsAsync_Ptr fn_MSALRUNTIME_DiscoverAccountsAsync = NULL;
MSALRUNTIME_GetDiscoverAccountsAt_Ptr fn_MSALRUNTIME_GetDiscoverAccountsAt = NULL;
MSALRUNTIME_ReleaseDiscoverAccountsResult_Ptr fn_MSALRUNTIME_ReleaseDiscoverAccountsResult = NULL;
MSALRUNTIME_GetAccount_Ptr fn_MSALRUNTIME_GetAccount = NULL;
MSALRUNTIME_ReleaseAccount_Ptr fn_MSALRUNTIME_ReleaseAccount = NULL;
MSALRUNTIME_ReleaseAuthResult_Ptr fn_MSALRUNTIME_ReleaseAuthResult = NULL;
MSALRUNTIME_Shutdown_Ptr fn_MSALRUNTIME_Shutdown = NULL;

bool initDll() {
	// Load DLL
	HMODULE hDll = LoadLibrary(L"msalruntime_x86.dll");
	if (hDll == NULL) {
		std::cout << "Failed to load msalruntime_x86.dll" << std::endl;
		return false;
	}

	// Get function pointers
	fn_MSALRUNTIME_Startup = (MSALRUNTIME_Startup_Ptr)GetProcAddress(hDll, "MSALRUNTIME_Startup");
	fn_MSALRUNTIME_AcquireTokenSilentlyAsync = (MSALRUNTIME_AcquireTokenSilentlyAsync_Ptr)GetProcAddress(hDll, "MSALRUNTIME_AcquireTokenSilentlyAsync");
	fn_MSALRUNTIME_SetIsPiiEnabled = (MSALRUNTIME_SetIsPiiEnabled_Ptr)GetProcAddress(hDll, "MSALRUNTIME_SetIsPiiEnabled");
	fn_MSALRUNTIME_CreateAuthParameters = (MSALRUNTIME_CreateAuthParameters_Ptr)GetProcAddress(hDll, "MSALRUNTIME_CreateAuthParameters");
	fn_MSALRUNTIME_SetRequestedScopes = (MSALRUNTIME_SetRequestedScopes_Ptr)GetProcAddress(hDll, "MSALRUNTIME_SetRequestedScopes");
	fn_MSALRUNTIME_SetRedirectUri = (MSALRUNTIME_SetRedirectUri_Ptr)GetProcAddress(hDll, "MSALRUNTIME_SetRedirectUri");
	fn_MSALRUNTIME_SetAdditionalParameter = (MSALRUNTIME_SetAdditionalParameter_Ptr)GetProcAddress(hDll, "MSALRUNTIME_SetAdditionalParameter");
	fn_MSALRUNTIME_ReleaseAsyncHandle = (MSALRUNTIME_ReleaseAsyncHandle_Ptr)GetProcAddress(hDll, "MSALRUNTIME_ReleaseAsyncHandle");
	fn_MSALRUNTIME_ReleaseAuthParameters = (MSALRUNTIME_ReleaseAuthParameters_Ptr)GetProcAddress(hDll, "MSALRUNTIME_ReleaseAuthParameters");
	fn_MSALRUNTIME_DiscoverAccountsAsync = (MSALRUNTIME_DiscoverAccountsAsync_Ptr)GetProcAddress(hDll, "MSALRUNTIME_DiscoverAccountsAsync");
	fn_MSALRUNTIME_GetDiscoverAccountsAt = (MSALRUNTIME_GetDiscoverAccountsAt_Ptr)GetProcAddress(hDll, "MSALRUNTIME_GetDiscoverAccountsAt");
	fn_MSALRUNTIME_ReleaseDiscoverAccountsResult = (MSALRUNTIME_ReleaseDiscoverAccountsResult_Ptr)GetProcAddress(hDll, "MSALRUNTIME_ReleaseDiscoverAccountsResult");
	fn_MSALRUNTIME_GetAccount = (MSALRUNTIME_GetAccount_Ptr)GetProcAddress(hDll, "MSALRUNTIME_GetAccount");
	fn_MSALRUNTIME_ReleaseAccount = (MSALRUNTIME_ReleaseAccount_Ptr)GetProcAddress(hDll, "MSALRUNTIME_ReleaseAccount");
	fn_MSALRUNTIME_ReleaseAuthResult = (MSALRUNTIME_ReleaseAuthResult_Ptr)GetProcAddress(hDll, "MSALRUNTIME_ReleaseAuthResult");
	fn_MSALRUNTIME_Shutdown = (MSALRUNTIME_Shutdown_Ptr)GetProcAddress(hDll, "MSALRUNTIME_Shutdown");

	if (fn_MSALRUNTIME_Startup == NULL || fn_MSALRUNTIME_AcquireTokenSilentlyAsync == NULL || fn_MSALRUNTIME_SetIsPiiEnabled == NULL || fn_MSALRUNTIME_CreateAuthParameters == NULL ||
		fn_MSALRUNTIME_SetRequestedScopes == NULL || fn_MSALRUNTIME_SetRedirectUri == NULL || fn_MSALRUNTIME_SetAdditionalParameter == NULL ||
		fn_MSALRUNTIME_ReleaseAsyncHandle == NULL || fn_MSALRUNTIME_ReleaseAuthParameters == NULL || fn_MSALRUNTIME_Shutdown == NULL || fn_MSALRUNTIME_DiscoverAccountsAsync == NULL ||
		0) {
		std::cout << "Failed to get function pointers" << std::endl;
		FreeLibrary(hDll);
		return false;
	}
	return true;
}