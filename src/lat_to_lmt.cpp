#include "sweph.h"

Napi::Value sweph_lat_to_lmt(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	if(info.Length() < 2) {
		Napi::TypeError::New(env, "Expecting 2 arguments").ThrowAsJavaScriptException();
		return env.Null();
	}
	if(!info[0].IsNumber()) {
		Napi::TypeError::New(env, "Argument 1 should be a number").ThrowAsJavaScriptException();
		return env.Null();
	}
	if(!info[1].IsNumber()) {
		Napi::TypeError::New(env, "Argument 2 should be a number").ThrowAsJavaScriptException();
		return env.Null();
	}
	double conv;
	char serr [SE_MAX_STNAME];
	int flag = swe_lat_to_lmt(
		info[0].As<Napi::Number>().DoubleValue(),
		info[1].As<Napi::Number>().DoubleValue(),
		&conv,
		serr
	);
	Napi::Object obj = Napi::Object::New(env);
	obj.Set(Napi::String::New(env, "flag"), Napi::Number::New(env, flag));
	obj.Set(Napi::String::New(env, "serr"), Napi::String::New(env, serr));
	obj.Set(Napi::String::New(env, "lmt"), Napi::Number::New(env, conv));
	return obj;
}
