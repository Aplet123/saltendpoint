#include <node.h>
#include <random>
#include <iostream>
#include <chrono>
#include <sstream>
#include <cmath>
#include <array>
#include <typeinfo>
#include <deque>
#include <cstdlib>
#include <iterator>


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

template <class T>

class ArrayIterator : public std::iterator <std::input_iterator_tag, T> {
    T * p;
public:
    ArrayIterator(T* x) : p(x) {}
    ArrayIterator(const ArrayIterator& mit) : p(mit.p) {}
    ArrayIterator& operator++() { ++ p; return *this; }
    ArrayIterator operator++(int) { ArrayIterator tmp(*this); operator++(); return tmp; }
    bool operator==(const ArrayIterator& rhs) { return p == rhs.p; }
    bool operator!=(const ArrayIterator& rhs) { return p != rhs.p; }
    T& operator*() { return *p; }
};

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
    double * weights = ( double * ) malloc(arr -> Length() * sizeof(double));
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
        weights[i] = element -> NumberValue();
    }
    generator.seed(seed);
    ArrayIterator <double> begin = weights;
    ArrayIterator <double> end = weights + arr -> Length();
    std::discrete_distribution <int> dist (begin, end);
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
    free(weights);
}

void Exponential(const FunctionCallbackInfo<Value>& args) {
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
    std::exponential_distribution <double> dist(doub1);
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

void ExtremeValue(const FunctionCallbackInfo<Value>& args) {
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
    std::extreme_value_distribution <double> dist(doub1, doub2);
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

void FisherF(const FunctionCallbackInfo<Value>& args) {
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
    std::fisher_f_distribution <double> dist(doub1, doub2);
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

void Gamma(const FunctionCallbackInfo<Value>& args) {
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
    std::gamma_distribution <double> dist(doub1, doub2);
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

void Geometric(const FunctionCallbackInfo<Value>& args) {
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
    std::geometric_distribution <int> dist(doub1);
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

void Lognormal(const FunctionCallbackInfo<Value>& args) {
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
    std::lognormal_distribution <double> dist(doub1, doub2);
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

void NegativeBinomial(const FunctionCallbackInfo<Value>& args) {
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
    std::negative_binomial_distribution <int> dist(doub1, doub2);
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

void Normal(const FunctionCallbackInfo<Value>& args) {
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
    std::normal_distribution <double> dist(doub1, doub2);
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

void PiecewiseConstant (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    int argLength = args.Length();
    double seed = high_resolution_clock::now().time_since_epoch().count();
    int seqLength = 0;
    int needLength = 2;
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
    if (! ( args[0] -> IsArray() && args[1] -> IsArray())) {
        ThrowException(isolate, "Incorrect typing");
        return;
    }
    Local <Array> arr = Local <Array>::Cast(args[0]);
    Local <Array> arr0 = Local <Array>::Cast(args[1]);
    if (arr -> Length() - arr0 -> Length() != 1) {
        ThrowException(isolate, "Lengths are mismatched");
        return;
    }
    double * weights = ( double * ) malloc(arr -> Length() * sizeof(double));
    double * weights0 = ( double * ) malloc(arr0 -> Length() * sizeof(double));
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
        weights[i] = element -> NumberValue();
    }
    for (unsigned int i = 0; i < arr0 -> Length(); i ++) {
        Local <Value> element;
        if (arr0 -> Get(current, i).IsEmpty()) {
            ThrowException(isolate, "Cannot convert to local");
            return;
        }
        element = arr0 -> Get(current, i).ToLocalChecked();
        if (! element -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        }
        weights0[i] = element -> NumberValue();
    }
    generator.seed(seed);
    ArrayIterator <double> begin = weights;
    ArrayIterator <double> begin0 = weights0;
    ArrayIterator <double> end = weights + arr -> Length();
    std::piecewise_constant_distribution <double> dist (begin, end, begin0);
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

void PiecewiseLinear (const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    int argLength = args.Length();
    double seed = high_resolution_clock::now().time_since_epoch().count();
    int seqLength = 0;
    int needLength = 2;
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
    if (! ( args[0] -> IsArray() && args[1] -> IsArray())) {
        ThrowException(isolate, "Incorrect typing");
        return;
    }
    Local <Array> arr = Local <Array>::Cast(args[0]);
    Local <Array> arr0 = Local <Array>::Cast(args[1]);
    if (arr -> Length() - arr0 -> Length() != 0) {
        ThrowException(isolate, "Lengths are mismatched");
        return;
    }
    double * weights = ( double * ) malloc(arr -> Length() * sizeof(double));
    double * weights0 = ( double * ) malloc(arr0 -> Length() * sizeof(double));
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
        weights[i] = element -> NumberValue();
    }
    for (unsigned int i = 0; i < arr0 -> Length(); i ++) {
        Local <Value> element;
        if (arr0 -> Get(current, i).IsEmpty()) {
            ThrowException(isolate, "Cannot convert to local");
            return;
        }
        element = arr0 -> Get(current, i).ToLocalChecked();
        if (! element -> IsNumber()) {
            ThrowException(isolate, "Incorrect typing");
            return;
        }
        weights0[i] = element -> NumberValue();
    }
    generator.seed(seed);
    ArrayIterator <double> begin = weights;
    ArrayIterator <double> begin0 = weights0;
    ArrayIterator <double> end = weights + arr -> Length();
    std::piecewise_linear_distribution <double> dist (begin, end, begin0);
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

void Poisson(const FunctionCallbackInfo<Value>& args) {
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
    std::poisson_distribution <int> dist(doub1);
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

void StudentT(const FunctionCallbackInfo<Value>& args) {
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
    std::student_t_distribution <double> dist(doub1);
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

void UniformInt(const FunctionCallbackInfo<Value>& args) {
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
    std::uniform_int_distribution <int> dist(doub1, doub2);
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

void UniformReal(const FunctionCallbackInfo<Value>& args) {
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
    std::uniform_real_distribution <double> dist(doub1, doub2);
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

void Weibull(const FunctionCallbackInfo<Value>& args) {
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
    std::weibull_distribution <double> dist(doub1, doub2);
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
    NODE_SET_METHOD(exports, "exponential_distribution", Exponential);
    NODE_SET_METHOD(exports, "extreme_value_distribution", ExtremeValue);
    NODE_SET_METHOD(exports, "fisher_f_distribution", FisherF);
    NODE_SET_METHOD(exports, "gamma_distribution", Gamma);
    NODE_SET_METHOD(exports, "geometric_distribution", Geometric);
    NODE_SET_METHOD(exports, "lognormal_distribution", Lognormal);
    NODE_SET_METHOD(exports, "negative_binomial_distribution", NegativeBinomial);
    NODE_SET_METHOD(exports, "normal_distribution", Normal);
    NODE_SET_METHOD(exports, "gaussian_distribution", Normal);
    NODE_SET_METHOD(exports, "piecewise_constant_distribution", PiecewiseConstant);
    NODE_SET_METHOD(exports, "piecewise_linear_distribution", PiecewiseLinear);
    NODE_SET_METHOD(exports, "poisson_distribution", Poisson);
    NODE_SET_METHOD(exports, "student_t_distribution", StudentT);
    NODE_SET_METHOD(exports, "uniform_int_distribution", UniformInt);
    NODE_SET_METHOD(exports, "uniform_real_distribution", UniformReal);
    NODE_SET_METHOD(exports, "weibull_distribution", Weibull);
}

NODE_MODULE(random, init)

}