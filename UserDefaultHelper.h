The MIT License (MIT)

Copyright (c) 2015 S74nk0 - Stanko Krstić

#pragma once

#include "cocos2d.h"
#include <type_traits>

/// START SPECIALIZE
#define SPECIALIZE(TYPE, FUN_NAME)                                             \
  template <>                                                                  \
  inline TYPE getValueForKey(const char *pKey, const TYPE &value) {            \
    return cocos2d::UserDefault::getInstance()->get##FUN_NAME##ForKey(pKey,    \
                                                                      value);  \
  \
}                                                                         \
  \
template<> inline void                                                         \
  setValueForKey(const char *pKey, const TYPE &value) {                        \
    cocos2d::UserDefault::getInstance()->set##FUN_NAME##ForKey(pKey, value);   \
  \
}                                                                         \
  \
template<> inline TYPE                                                         \
  getValueForKey(const std::string &pKey, const TYPE &value) {                 \
    return getValueForKey(pKey.c_str(), value);                                \
  \
}                                                                         \
  \
template<> inline void                                                         \
  setValueForKey(const std::string &pKey, const TYPE &value) {                 \
    setValueForKey(pKey.c_str(), value);                                       \
  \
}
/// END SPECIALIZE

/// START COMPILE_TIME_CHECKED
#define COMPILE_TIME_CHECKED(TYPE, FUN_NAME)                                   \
  \
template<typename T> \
inline TYPE get##FUN_NAME##ForKey(const char *pKey, const T &value) {          \
    static_assert(std::is_same<T, TYPE>::value, "TYPE MISMATCH");              \
    return cocos2d::UserDefault::getInstance()->get##FUN_NAME##ForKey(pKey,    \
                                                                      value);  \
  \
}                                                                         \
  \
template<typename T> \
inline void set##FUN_NAME##ForKey(const char *pKey, const T &value) {          \
    static_assert(std::is_same<T, TYPE>::value, "TYPE MISMATCH");              \
    cocos2d::UserDefault::getInstance()->set##FUN_NAME##ForKey(pKey, value);   \
  \
}                                                                         \
  \
template<typename T> \
inline TYPE get##FUN_NAME##ForKey(const std::string &pKey, const T &value) {   \
    return get##FUN_NAME##ForKey(pKey, value);                                 \
  \
}                                                                         \
  \
template<typename T> \
inline void set##FUN_NAME##ForKey(const std::string &pKey, const T &value) {   \
    set##FUN_NAME##ForKey(pKey.c_str(), value);                                \
  \
} \
/// END COMPILE_TIME_CHECKED

namespace UserDefaultHelper {

// write changes to file
inline void flush() { cocos2d::UserDefault::getInstance()->flush(); }
// both functions must be specialized (we use the SPECIALIZE), otherwise we get
// an error
template <typename T>
inline T getValueForKey(const char *pKey, const T &value) {
  static_assert(false, "TYPE NOT SUPPORTED");
  return value;
}
template <typename T>
inline void setValueForKey(const char *pKey, const T &value) {
  static_assert(false, "TYPE NOT SUPPORTED");
}
template <typename T>
inline T getValueForKey(const std::string &pKey, const T &value) {
  static_assert(false, "TYPE NOT SUPPORTED");
  return value;
}
template <typename T>
inline void setValueForKey(const std::string &pKey, const T &value) {
  static_assert(false, "TYPE NOT SUPPORTED");
}

/// Supported types
// bool
SPECIALIZE(bool, Bool)
// int
SPECIALIZE(int, Integer)
// float
SPECIALIZE(float, Float)
// double
SPECIALIZE(double, Double)
// std::string
SPECIALIZE(std::string, String)
// cocos2d::Data
SPECIALIZE(cocos2d::Data, Data)

// bool
COMPILE_TIME_CHECKED(bool, Bool)
// int
COMPILE_TIME_CHECKED(int, Integer)
// float
COMPILE_TIME_CHECKED(float, Float)
// double
COMPILE_TIME_CHECKED(double, Double)
// std::string
COMPILE_TIME_CHECKED(std::string, String)
// cocos2d::Data
COMPILE_TIME_CHECKED(cocos2d::Data, Data)

} // END UserDefaultHelper
