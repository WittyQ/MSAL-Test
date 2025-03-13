#pragma once
#include <iostream>
#include <string>
#include <codecvt>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <wincrypt.h>
#include "../lib/subprojects/pymsalruntime-0.18.0/build_resources/MSALRuntime.h"

// 定义函数指针类型
typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_Startup_Ptr)();
typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_AcquireTokenSilentlyAsync_Ptr)(MSALRUNTIME_AUTH_PARAMETERS_HANDLE authParameters, const os_char* correlationId, MSALRUNTIME_ACCOUNT_HANDLE account, MSALRUNTIME_COMPLETION_ROUTINE callback, void* callbackData, MSALRUNTIME_ASYNC_HANDLE* asyncHandle);
typedef void (MSALRUNTIME_API* MSALRUNTIME_SetIsPiiEnabled_Ptr)(int32_t enabled);
typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_CreateAuthParameters_Ptr)(const os_char* clientId, const os_char* authority, MSALRUNTIME_AUTH_PARAMETERS_HANDLE* authParameters);
typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_SetRequestedScopes_Ptr)(MSALRUNTIME_AUTH_PARAMETERS_HANDLE authParameters, const os_char* scopes);
typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_SetRedirectUri_Ptr)(MSALRUNTIME_AUTH_PARAMETERS_HANDLE authParameters, const os_char* redirectUri);
typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_SetAdditionalParameter_Ptr)(MSALRUNTIME_AUTH_PARAMETERS_HANDLE authParameters, const os_char* key, const os_char* value);
typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_ReleaseAsyncHandle_Ptr)(MSALRUNTIME_ASYNC_HANDLE asyncHandle);
typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_ReleaseAuthParameters_Ptr)(MSALRUNTIME_AUTH_PARAMETERS_HANDLE authParameters);
typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_ReleaseAsyncHandle_Ptr)(MSALRUNTIME_ASYNC_HANDLE asyncHandle);
typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_GetDiscoverAccountsAt_Ptr)(
	MSALRUNTIME_DISCOVER_ACCOUNTS_RESULT_HANDLE discoverAccountsResult,
	int32_t index,
	MSALRUNTIME_ACCOUNT_HANDLE* account);

typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_ReleaseDiscoverAccountsResult_Ptr)(MSALRUNTIME_DISCOVER_ACCOUNTS_RESULT_HANDLE discoverAccountsResult);

typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_GetAccount_Ptr)(MSALRUNTIME_AUTH_RESULT_HANDLE authResult, MSALRUNTIME_ACCOUNT_HANDLE* account);

typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_DiscoverAccountsAsync_Ptr)(
	const os_char* clientId,
	const os_char* correlationId,
	MSALRUNTIME_DISCOVER_ACCOUNTS_COMPLETION_ROUTINE callback,
	void* callbackData,
	MSALRUNTIME_ASYNC_HANDLE* asyncHandle);

typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_ReleaseAccount_Ptr)(MSALRUNTIME_ACCOUNT_HANDLE account);

typedef MSALRUNTIME_ERROR_HANDLE(MSALRUNTIME_API* MSALRUNTIME_ReleaseAuthResult_Ptr)(MSALRUNTIME_AUTH_RESULT_HANDLE authResult);

typedef void (*MSALRUNTIME_Shutdown_Ptr)();

// 声明函数指针变量
extern MSALRUNTIME_Startup_Ptr fn_MSALRUNTIME_Startup;
extern MSALRUNTIME_AcquireTokenSilentlyAsync_Ptr fn_MSALRUNTIME_AcquireTokenSilentlyAsync;
extern MSALRUNTIME_SetIsPiiEnabled_Ptr fn_MSALRUNTIME_SetIsPiiEnabled;
extern MSALRUNTIME_CreateAuthParameters_Ptr fn_MSALRUNTIME_CreateAuthParameters;
extern MSALRUNTIME_SetRequestedScopes_Ptr fn_MSALRUNTIME_SetRequestedScopes;
extern MSALRUNTIME_SetRedirectUri_Ptr fn_MSALRUNTIME_SetRedirectUri;
extern MSALRUNTIME_SetAdditionalParameter_Ptr fn_MSALRUNTIME_SetAdditionalParameter;
extern MSALRUNTIME_ReleaseAsyncHandle_Ptr fn_MSALRUNTIME_ReleaseAsyncHandle;
extern MSALRUNTIME_ReleaseAuthParameters_Ptr fn_MSALRUNTIME_ReleaseAuthParameters;
extern MSALRUNTIME_DiscoverAccountsAsync_Ptr fn_MSALRUNTIME_DiscoverAccountsAsync;
extern MSALRUNTIME_GetDiscoverAccountsAt_Ptr fn_MSALRUNTIME_GetDiscoverAccountsAt;
extern MSALRUNTIME_ReleaseDiscoverAccountsResult_Ptr fn_MSALRUNTIME_ReleaseDiscoverAccountsResult;
extern MSALRUNTIME_Shutdown_Ptr fn_MSALRUNTIME_Shutdown;
extern MSALRUNTIME_GetAccount_Ptr fn_MSALRUNTIME_GetAccount;
extern MSALRUNTIME_ReleaseAccount_Ptr fn_MSALRUNTIME_ReleaseAccount;
extern MSALRUNTIME_ReleaseAuthResult_Ptr fn_MSALRUNTIME_ReleaseAuthResult;
bool initDll();

//#define MACRO_STR(s) #s
//#define MSAL_GET_STRING(handle, func, value) \
//	do { \
//		int32_t _length = 0; \
//		func(handle, nullptr, &_length); \
//		if (_length > 0) { \
//			os_char *_w_value = new os_char[_length]; \
//			if (func(handle, _w_value, &_length) == MSALRUNTIME_SUCCEED) { \
//				value = toUtf8(_w_value); \
//			} \
//			delete[] _w_value; \
//		} \
//	} while (0)
//
//
//#define PRINT_FIELD(handle, func) \
//	do { \
//		std::string out; \
//		MSAL_GET_STRING(handle, func, out); \
//		std::cout << MACRO_STR(func) " \"" << out << "\"" << std::endl; \
//	} while (0)
//
//inline void printAccount(MSALRUNTIME_ACCOUNT_HANDLE handle) {
//	PRINT_FIELD(handle, MSALRUNTIME_GetAccountId);
//	PRINT_FIELD(handle, MSALRUNTIME_GetHomeAccountId);
//	PRINT_FIELD(handle, MSALRUNTIME_GetEnvironment);
//	PRINT_FIELD(handle, MSALRUNTIME_GetRealm);
//	PRINT_FIELD(handle, MSALRUNTIME_GetLocalAccountId);
//	PRINT_FIELD(handle, MSALRUNTIME_GetUserName);
//	PRINT_FIELD(handle, MSALRUNTIME_GetGivenName);
//	PRINT_FIELD(handle, MSALRUNTIME_GetFamilyName);
//	PRINT_FIELD(handle, MSALRUNTIME_GetMiddleName);
//	PRINT_FIELD(handle, MSALRUNTIME_GetDisplayName);
//	PRINT_FIELD(handle, MSALRUNTIME_GetClientInfo);
//	PRINT_FIELD(handle, MSALRUNTIME_GetAdditionalFieldsJson);
//	PRINT_FIELD(handle, MSALRUNTIME_GetHomeEnvironment);
//}