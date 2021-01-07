#include "sweph.h"

Napi::Value sweph_cotrans(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	if(info.Length() < 2) {
		Napi::TypeError::New(env, "Expecting 3 arguments").ThrowAsJavaScriptException();
		return env.Null();
	}
	if(!info[0].IsArray()) {
		Napi::TypeError::New(env, "Argument 1 should be an array of 3 numbers").ThrowAsJavaScriptException();
		return env.Null();
	}
	if(!info[1].IsNumber()) {
		Napi::TypeError::New(env, "Argument 2 should be a number").ThrowAsJavaScriptException();
		return env.Null();
	}
	Napi::Array coords = info[0].As<Napi::Array>();
	double in [3];
	for(int i = 0; i < 3; i++) {
		if(!((Napi::Value)coords[i]).IsNumber()) {
			Napi::TypeError::New(env, "Argument 1 should be an array of 3 numbers").ThrowAsJavaScriptException();
			return env.Null();
		}
		in[i] = ((Napi::Value)coords[i]).As<Napi::Number>().DoubleValue();
	}
	double out [3];
	swe_cotrans(
		in,
		out,
		info[1].As<Napi::Number>().DoubleValue()
	);
	Napi::Array array = Napi::Array::New(env);
	for(int i = 1; i < 3; i++) {
		array[i] = Napi::Number::New(env, out[i]);
	}
	return array;
}
