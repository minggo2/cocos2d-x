//
//  ScriptingCore.h
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef cocos2dx_ScriptingCore_h
#define cocos2dx_ScriptingCore_h

#include "jsapi.h"

class ScriptingCore
{
	JSRuntime *rt;
	JSContext *cx;
	JSObject  *global;
public:
	ScriptingCore();
	~ScriptingCore();

	/**
	 * will eval the specified string
	 * @param string The string with the javascript code to be evaluated
	 */
	void evalString(const char *string);
	void runScript(const char *path);

	/**
	 * @param cx
	 * @param message
	 * @param report
	 */
	static void reportError(JSContext *cx, const char *message, JSErrorReport *report)
	{
		fprintf(stderr, "%s:%u:%s\n",  
				report->filename ? report->filename : "<no filename=\"filename\">",  
				(unsigned int) report->lineno,  
				message);
	};

	/**
	 * Log something using CCLog
	 * @param cx
	 * @param argc
	 * @param vp
	 */
	static JSBool log(JSContext *cx, uint32_t argc, jsval *vp)
	{
		if (argc > 0) {
			JSString *string = NULL;
			JS_ConvertArguments(cx, argc, JS_ARGV(cx, vp), "S", &string);
			if (string) {
				char *cstr = JS_EncodeString(cx, string);
				cocos2d::CCLog(cstr);
			}
		}
		return JS_TRUE;
	};
};

#endif