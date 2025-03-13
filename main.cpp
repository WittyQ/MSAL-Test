#include <iostream>
#include <windows.h>
#include "MSALWrapper.h"
#include "..\lib\sources\utils.hpp"

// Your Microsoft Azure AD/Entra ID "Application (client) ID"
#define APP_CLIENT_ID L"2e8f5536-0310-4abf-acb3-90cb18a1959a"

// Your Microsoft Azure AD/Entra ID "Directory (tenant) ID"
#define APP_AUTHORITY L"https://login.microsoftonline.com/82fa1a12-0ec4-4393-a078-28136ca3f6df"

typedef struct discover_s {
	bool called;
	MSALRUNTIME_ACCOUNT_HANDLE account;
} discover_t;

static void auth_callback(
	MSALRUNTIME_AUTH_RESULT_HANDLE authResult, void* callbackData) {
	bool* shouldWait = (bool*)callbackData;
	MSALRUNTIME_ACCOUNT_HANDLE account = 0;

	// print account info
	fn_MSALRUNTIME_GetAccount(authResult, &account);
	//printAccount(account);

	// print auth result
	//printAuthResult(authResult);

	// free memory
	fn_MSALRUNTIME_ReleaseAccount(account);
	fn_MSALRUNTIME_ReleaseAuthResult(authResult);

	// let's stop waiting for this async callback
	*shouldWait = false;
}

static void discover_callback(
	MSALRUNTIME_DISCOVER_ACCOUNTS_RESULT_HANDLE discoverAccountsResult,
	void* callbackData) {
	discover_t* ctx = (discover_t*)callbackData;

	// fetch the first account available
	fn_MSALRUNTIME_GetDiscoverAccountsAt(discoverAccountsResult, 0, &ctx->account);

	// free up memory
	fn_MSALRUNTIME_ReleaseDiscoverAccountsResult(discoverAccountsResult);

	// stop waiting for this async call
	ctx->called = true;
}

static MSALRUNTIME_ACCOUNT_HANDLE discoverFirstAccount(
	std::wstring& correlationId) {
	discover_t ctx = { 0 };
	MSALRUNTIME_ASYNC_HANDLE asyncHandle = 0;

	fn_MSALRUNTIME_DiscoverAccountsAsync(APP_CLIENT_ID, correlationId.c_str(),
		discover_callback, &ctx, &asyncHandle);

	// this is a terrible way to wait for async, but this is
	// an example, so please use locks & signals.
	while (!ctx.called) {
		Sleep(300);
	}

	// free the async handle
	fn_MSALRUNTIME_ReleaseAsyncHandle(asyncHandle);

	// return the first account.
	return ctx.account;
}

int main(int argc, char const* argv[]) {
	if (!initDll()) {
		std::cout << "init msalruntime_x86.dll and get function point failed" << std::endl;
		return 1;
	}

	// Some vars to wait for reply
	bool shouldWait = true;
	// MSAL required variables
	//MSALRUNTIME_LOG_CALLBACK_HANDLE logHandle = 0;
	MSALRUNTIME_AUTH_PARAMETERS_HANDLE authParameters = 0;
	MSALRUNTIME_ASYNC_HANDLE asyncHandle = 0;
	MSALRUNTIME_ACCOUNT_HANDLE account = 0;

	// create a random correlation uuid (can be empty)
	auto correlationId = uuidGen();

	// Initialize MSALRuntime library
	fn_MSALRUNTIME_Startup();

	// set pii
	fn_MSALRUNTIME_SetIsPiiEnabled(0);

	// create auth parameters and configure the app.
	fn_MSALRUNTIME_CreateAuthParameters(
		APP_CLIENT_ID, APP_AUTHORITY, &authParameters);

	// sets the requested scopes (mandatory and cannot be an empty string).
	fn_MSALRUNTIME_SetRequestedScopes(
		authParameters, L"https://graph.microsoft.com/.default");

	// configure the redirect uri to use the secure broker popup
	// msal for python sets this as 'placeholder'.
	fn_MSALRUNTIME_SetRedirectUri(authParameters, L"placeholder");

	// set the secure broker popup to not block this thread.
	fn_MSALRUNTIME_SetAdditionalParameter(
		authParameters, L"msal_gui_thread", L"true");
	
	// get first account available
	account = discoverFirstAccount(correlationId);
	//printAccount(account);

	// finally try to acquire the token.
	fn_MSALRUNTIME_AcquireTokenSilentlyAsync(authParameters, correlationId.c_str(),
		account, auth_callback, &shouldWait, &asyncHandle);
	
	while (shouldWait) {
		Sleep(300);
	}

	// free the async handle
	fn_MSALRUNTIME_ReleaseAsyncHandle(asyncHandle);

	// free auth parameters
	fn_MSALRUNTIME_ReleaseAuthParameters(authParameters);
	
	// free logger handle
	//MSALRUNTIME_ReleaseLogCallbackHandle(logHandle);

	// deinitialize msalruntime
	fn_MSALRUNTIME_Shutdown();
	return 0;
}