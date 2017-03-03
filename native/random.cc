#include <node.h>
#include <random>
#include <iostream>


namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Boolean;
using v8::Exception;
using std::cout;
using std::cin;
using std::endl;

void ThrowException(Isolate* isolate, const char * exception) {
    isolate->ThrowException(Exception::Error(String::NewFromUtf8(isolate, exception)));
}

void Bernoulli(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  int argLength = args.Length();
  if (argLength == 0) {
      ThrowException(isolate, "Too few arguments");
      return;
  }
  std::default_random_engine generator;
  if (! args[0] -> IsNumber()) {
      ThrowException(isolate, "Incorrect typing");
      return;
  }
  double doub = args[0] -> NumberValue();
  std::bernoulli_distribution dist(doub);
  cout << doub << "\n" << dist(generator) << "\n";
  Local <Boolean> ret = Boolean::New(isolate, dist(generator));
  args.GetReturnValue().Set(ret);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "bernoulli_distribution", Bernoulli);
}

NODE_MODULE(random, init)

}