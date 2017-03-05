#include <node.h>
#include <random>
#include <iostream>
#include <chrono>
#include <sstream>
#include <cmath>
#include <array>
#include <typeinfo>
#include <deque>


namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Context;
using v8::Local;
using v8::Object;
using v8::Array;
using v8::String;
using v8::Value;
using v8::Boolean;
using v8::Exception;
using v8::Number;
using v8::Handle;
using std::cout;
using std::cin;
using std::endl;
using std::chrono::high_resolution_clock;
using std::stringstream;

void ThrowException(Isolate* isolate, const char * exception) {
    isolate -> ThrowException(Exception::Error(String::NewFromUtf8(isolate, exception)));
}

void CurrentTime(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    args.GetReturnValue().Set(Number::New(isolate, high_resolution_clock::now().time_since_epoch().count()));
}

void Bernoulli(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    int argLength = args.Length();
    double seed;
    int seqLength;
    int needLength = 1;
    int optionalLength = 0;
    if (argLength < needLength) {
            ThrowException(isolate, "Too few arguments");
            return;
    } else if (argLength > needLength + optionalLength + 2) {
        ThrowException(isolate, "Too many arguments");
        return;
    } else if (argLength == needLength + optionalLength + 1) {
        if (! args[needLength + optionalLength] -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        } else {
            seed = args[needLength + optionalLength] -> NumberValue();
            if (seed == 0) {
                seed = high_resolution_clock::now().time_since_epoch().count();
            }
        }
    } else if (argLength == needLength + optionalLength + 2) {
        if (! ( args[needLength + optionalLength] -> IsNumber() || args[needLength + optionalLength + 1] -> IsNumber())) {
            ThrowException(isolate, "Incorrect typing");
            return;
        } else {
            seed = args[needLength + optionalLength] -> NumberValue();
            if (seed == 0) {
                seed = high_resolution_clock::now().time_since_epoch().count();
            }
            seqLength = args[needLength + optionalLength + 1] -> NumberValue();
        }
    } else {
        seed = high_resolution_clock::now().time_since_epoch().count();
        seqLength = 0;
    }
    std::minstd_rand0 generator;
    for (int i = 0; i < needLength + optionalLength; i ++) {
        if (! args[i] -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        }
    }
    double doub1 = args[0] -> NumberValue();
    generator.seed(seed);
    std::bernoulli_distribution dist(doub1);
    if (seqLength > 0) {
        Local <Context> current = isolate -> GetCurrentContext();
        Local <Array> ret = Array::New(isolate, seqLength);
        for (int i = 0; i < seqLength; i ++) {
            ret -> Set(current, i, Number::New(isolate, dist(generator)));
        }
        args.GetReturnValue().Set(ret);
    } else {
        Local <Number> ret = Number::New(isolate, dist(generator));
        args.GetReturnValue().Set(ret);
    }
}

void Binomial(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    int argLength = args.Length();
    double seed = high_resolution_clock::now().time_since_epoch().count();
    int seqLength = 0;
    int needLength = 2;
    int optionalLength = 0;
    if (argLength < needLength) {
            ThrowException(isolate, "Too few arguments");
            return;
    } else if (argLength > needLength + optionalLength + 2) {
        ThrowException(isolate, "Too many arguments");
        return;
    } else if (argLength == needLength + optionalLength + 1) {
        if (! args[needLength + optionalLength] -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        } else {
            seed = args[needLength + optionalLength] -> NumberValue();
            if (seed == 0) {
                seed = high_resolution_clock::now().time_since_epoch().count();
            }
        }
    } else if (argLength == needLength + optionalLength + 2) {
        if (! ( args[needLength + optionalLength] -> IsNumber() || args[needLength + optionalLength + 1] -> IsNumber())) {
            ThrowException(isolate, "Incorrect typing");
            return;
        } else {
            seed = args[needLength + optionalLength] -> NumberValue();
            if (seed == 0) {
                seed = high_resolution_clock::now().time_since_epoch().count();
            }
            seqLength = args[needLength + optionalLength + 1] -> NumberValue();
        }
    }
    std::minstd_rand0 generator;
    for (int i = 0; i < needLength + optionalLength; i ++) {
        if (! args[i] -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        }
    }
    double doub1 = args[0] -> NumberValue();
    double doub2 = args[1] -> NumberValue();
    generator.seed(seed);
    std::binomial_distribution <int> dist(doub1, doub2);
    if (seqLength > 0) {
        Local <Context> current = isolate -> GetCurrentContext();
        Local <Array> ret = Array::New(isolate, seqLength);
        for (int i = 0; i < seqLength; i ++) {
            ret -> Set(current, i, Number::New(isolate, dist(generator)));
        }
        args.GetReturnValue().Set(ret);
    } else {
        Local <Number> ret = Number::New(isolate, dist(generator));
        args.GetReturnValue().Set(ret);
    }
}

void Cauchy(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    int argLength = args.Length();
    double seed = high_resolution_clock::now().time_since_epoch().count();
    int seqLength = 0;
    int needLength = 2;
    int optionalLength = 0;
    if (argLength < needLength) {
            ThrowException(isolate, "Too few arguments");
            return;
    } else if (argLength > needLength + optionalLength + 2) {
        ThrowException(isolate, "Too many arguments");
        return;
    } else if (argLength == needLength + optionalLength + 1) {
        if (! args[needLength + optionalLength] -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        } else {
            seed = args[needLength + optionalLength] -> NumberValue();
            if (seed == 0) {
                seed = high_resolution_clock::now().time_since_epoch().count();
            }
        }
    } else if (argLength == needLength + optionalLength + 2) {
        if (! ( args[needLength + optionalLength] -> IsNumber() || args[needLength + optionalLength + 1] -> IsNumber())) {
            ThrowException(isolate, "Incorrect typing");
            return;
        } else {
            seed = args[needLength + optionalLength] -> NumberValue();
            if (seed == 0) {
                seed = high_resolution_clock::now().time_since_epoch().count();
            }
            seqLength = args[needLength + optionalLength + 1] -> NumberValue();
        }
    }
    std::minstd_rand0 generator;
    for (int i = 0; i < needLength + optionalLength; i ++) {
        if (! args[i] -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        }
    }
    double doub1 = args[0] -> NumberValue();
    double doub2 = args[1] -> NumberValue();
    generator.seed(seed);
    std::cauchy_distribution <double> dist(doub1, doub2);
    if (seqLength > 0) {
        Local <Context> current = isolate -> GetCurrentContext();
        Local <Array> ret = Array::New(isolate, seqLength);
        for (int i = 0; i < seqLength; i ++) {
            ret -> Set(current, i, Number::New(isolate, dist(generator)));
        }
        args.GetReturnValue().Set(ret);
    } else {
        Local <Number> ret = Number::New(isolate, dist(generator));
        args.GetReturnValue().Set(ret);
    }
}

void ChiSquared(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    int argLength = args.Length();
    double seed = high_resolution_clock::now().time_since_epoch().count();
    int seqLength = 0;
    int needLength = 1;
    int optionalLength = 0;
    if (argLength < needLength) {
            ThrowException(isolate, "Too few arguments");
            return;
    } else if (argLength > needLength + optionalLength + 2) {
        ThrowException(isolate, "Too many arguments");
        return;
    } else if (argLength == needLength + optionalLength + 1) {
        if (! args[needLength + optionalLength] -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        } else {
            seed = args[needLength + optionalLength] -> NumberValue();
            if (seed == 0) {
                seed = high_resolution_clock::now().time_since_epoch().count();
            }
        }
    } else if (argLength == needLength + optionalLength + 2) {
        if (! ( args[needLength + optionalLength] -> IsNumber() || args[needLength + optionalLength + 1] -> IsNumber())) {
            ThrowException(isolate, "Incorrect typing");
            return;
        } else {
            seed = args[needLength + optionalLength] -> NumberValue();
            if (seed == 0) {
                seed = high_resolution_clock::now().time_since_epoch().count();
            }
            seqLength = args[needLength + optionalLength + 1] -> NumberValue();
        }
    }
    std::minstd_rand0 generator;
    for (int i = 0; i < needLength + optionalLength; i ++) {
        if (! args[i] -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        }
    }
    double doub1 = args[0] -> NumberValue();
    generator.seed(seed);
    std::chi_squared_distribution <double> dist(doub1);
    if (seqLength > 0) {
        Local <Context> current = isolate -> GetCurrentContext();
        Local <Array> ret = Array::New(isolate, seqLength);
        for (int i = 0; i < seqLength; i ++) {
            ret -> Set(current, i, Number::New(isolate, dist(generator)));
        }
        args.GetReturnValue().Set(ret);
    } else {
        Local <Number> ret = Number::New(isolate, dist(generator));
        args.GetReturnValue().Set(ret);
    }
}

void Discrete (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    int argLength = args.Length();
    double seed = high_resolution_clock::now().time_since_epoch().count();
    int seqLength = 0;
    int needLength = 1;
    int optionalLength = 0;
    Local <Context> current = isolate -> GetCurrentContext();
    if (argLength < needLength) {
            ThrowException(isolate, "Too few arguments");
            return;
    } else if (argLength > needLength + optionalLength + 2) {
        ThrowException(isolate, "Too many arguments");
        return;
    } else if (argLength == needLength + optionalLength + 1) {
        if (! args[needLength + optionalLength] -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        } else {
            seed = args[needLength + optionalLength] -> NumberValue();
            if (seed == 0) {
                seed = high_resolution_clock::now().time_since_epoch().count();
            }
        }
    } else if (argLength == needLength + optionalLength + 2) {
        if (! ( args[needLength + optionalLength] -> IsNumber() || args[needLength + optionalLength + 1] -> IsNumber())) {
            ThrowException(isolate, "Incorrect typing");
            return;
        } else {
            seed = args[needLength + optionalLength] -> NumberValue();
            if (seed == 0) {
                seed = high_resolution_clock::now().time_since_epoch().count();
            }
            seqLength = args[needLength + optionalLength + 1] -> NumberValue();
        }
    }
    std::minstd_rand0 generator;
    if (! args[0] -> IsArray()) {
        ThrowException(isolate, "Incorrect typing");
        return;
    }
    Local <Array> arr = Local <Array>::Cast(args[0]);
    std::deque <double> weights;
    if (arr -> Length() > weights.max_size()) {
        ThrowException(isolate, "Array too long");
        return;
    }
    for (unsigned int i = 0; i < arr -> Length(); i ++) {
        Local <Value> element;
        if (arr -> Get(current, i).IsEmpty()) {
            ThrowException(isolate, "Cannot convert to local");
            return;
        }
        element = arr -> Get(current, i).ToLocalChecked();
        if (! element -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        }
        weights.push_back(element -> NumberValue());
    }
    generator.seed(seed);
    std::discrete_distribution <int> dist (weights.begin(), weights.end());
    if (seqLength > 0) {
        Local <Context> current = isolate -> GetCurrentContext();
        Local <Array> ret = Array::New(isolate, seqLength);
        for (int i = 0; i < seqLength; i ++) {
            ret -> Set(current, i, Number::New(isolate, dist(generator)));
        }
        args.GetReturnValue().Set(ret);
    } else {
        Local <Number> ret = Number::New(isolate, dist(generator));
        args.GetReturnValue().Set(ret);
    }
}

void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "time", CurrentTime);
    NODE_SET_METHOD(exports, "bernoulli_distribution", Bernoulli);
    NODE_SET_METHOD(exports, "binomial_distribution", Binomial);
    NODE_SET_METHOD(exports, "cauchy_distribution", Cauchy);
    NODE_SET_METHOD(exports, "chi_squared_distribution", ChiSquared);
    NODE_SET_METHOD(exports, "discrete_distribution", Discrete);
    /*NODE_SET_METHOD(exports, "exponential_distribution", Exponential);
    NODE_SET_METHOD(exports, "extreme_value_distribution", ExtremeValue);
    NODE_SET_METHOD(exports, "fisher_f_distribution", FisherF);
    NODE_SET_METHOD(exports, "gamma_distribution", Gamma);
    NODE_SET_METHOD(exports, "geometric_distribution", Geometric);
    NODE_SET_METHOD(exports, "lognormal_distribution", Lognormal);
    NODE_SET_METHOD(exports, "negative_binomial_distribution", NegativeBinomial);*/
}

NODE_MODULE(random, init)

}