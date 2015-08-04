The MIT License (MIT)

Copyright (c) 2015 S74nk0 - Stanko Krstić

#ifndef MACROS_H
#define MACROS_H

#define SUPER_SELF(SUPER, SELF)                                                \
  typedef SUPER Super;                                                         \
  typedef SELF Self


// Meyers (thread safe in nimamo problema z dealokacijo objekta)
#define SINGLETON(SELF)                                                        \
public:                                                                        \
  ~SELF() {}                                                                   \
  static SELF &getInstance() {                                                 \
    static SELF _instance;                                                     \
    return _instance;                                                          \
  }                                                                            \
private:                                                                       \
  SELF();



#define TYPE_CAST(TYPE, VALUE)                                                 \
  static_cast<std::underlying_type<TYPE>::type>(VALUE)

#define SIZE_T(VALUE) static_cast<size_t>(VALUE)

// #define TO_STR(DATA) std::string(#DATA).substr(std::string(#DATA).rfind(':') + 1, std::string(#DATA).size() - std::string(#DATA).rfind(':')).c_str()

#endif // MACROS_H
