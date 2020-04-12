//
// Created by akumar on 12-04-2020.
//

#ifndef PGPAINKILLER_MAYBE_H
#define PGPAINKILLER_MAYBE_H

#include <string>
#include <functional>

using namespace std;

template<typename T>
struct Maybe {
    T just;
    bool isNothing;
};

template<typename T>
Maybe<T> *makeMaybe(T just, bool isNothing) {
//    Maybe<T>* maybe = (struct Maybe<T>*) malloc (sizeof(struct Maybe<T>));
    Maybe<T>* maybe = new Maybe<T>();
    maybe->just = just;
    maybe->isNothing = isNothing;
    return maybe;
}

template<typename T>
Maybe<T> *makeNothing() {
//    Maybe<T>* maybe = (struct Maybe<T>*) malloc (sizeof(struct Maybe<T>));
    Maybe<T>* maybe = new Maybe<T>();
    maybe->isNothing = true;
    return maybe;
}

template<typename T>
Maybe<T> *Just(T just) {
    return makeMaybe(just, false);
}

template<typename T>
Maybe<T> *Nothing() {
    return makeNothing<T>();
}

template<typename T>
bool isNothing(Maybe<T> *maybe) {
    return maybe == NULL || maybe->isNothing;
}

template<typename T>
string toString(Maybe<T> *maybe) {
    return isNothing(maybe) ? "Nothing" : "Just " + to_string(maybe->just);
}

template<typename A, typename B>
Maybe<B> *map(function<B(A)> f, Maybe<A> *maybe) {
    return isNothing(maybe) ? Nothing<B>() : Just(f(maybe->just));
}

template<typename A, typename B>
Maybe<B> *operator>>=(Maybe<A> *maybe, function<Maybe<B> *(A)> f) {
    return isNothing(maybe) ? Nothing<B>() : f(maybe->just);
}


#endif //PGPAINKILLER_MAYBE_H
