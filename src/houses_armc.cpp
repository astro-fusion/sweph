#include "sweph.h"

Napi::Value sweph_houses_armc(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	if(info.Length() < 4) {
		Napi::TypeError::New(env, "Expecting 4 arguments").ThrowAsJavaScriptException();
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
	if(!info[2].IsNumber()) {
		Napi::TypeError::New(env, "Argument 3 should be a number").ThrowAsJavaScriptException();
		return env.Null();
	}
	if(!info[3].IsString()) {
		Napi::TypeError::New(env, "Argument 4 should be a string").ThrowAsJavaScriptException();
		return env.Null();
	}
	double cusps [37];
	double points [10];
	char sys = info[3].As<Napi::String>().Utf8Value()[0];
	int flag = swe_houses_armc(
		info[0].As<Napi::Number>().DoubleValue(),
		info[1].As<Napi::Number>().DoubleValue(),
		info[2].As<Napi::Number>().DoubleValue(),
		int(sys),
		cusps,
		points
	);
	Napi::Object obj = Napi::Object::New(env);
	Napi::Array c1 = Napi::Array::New(env);
	Napi::Array p1 = Napi::Array::New(env);
	for(int i = 1; i < (sys == 'G' ? 37 : 13); i++) {
		c1[i] = Napi::Number::New(env, cusps[i]);
	}
	for(int i = 0; i < 8; i++) {
		p1[i] = Napi::Number::New(env, points[i]);
	}
	obj.Set(Napi::String::New(env, "houses"), c1);
	obj.Set(Napi::String::New(env, "points"), p1);
	obj.Set(Napi::String::New(env, "flag"), Napi::Number::New(env, flag));
	return obj;
}
