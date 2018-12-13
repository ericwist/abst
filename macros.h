// Macro helpers 
// by Eric Wistrand
// Nov. 2016
#pragma once

// Macro that calls a COM method returning HRESULT value.
#define CHK_HR(stmt)                                                           \
  do {                                                                         \
    hr = (stmt);                                                               \
    if (FAILED(hr))                                                            \
      goto Cleanup;                                                            \
  } while (0)

// Macro to verify memory allcation.
#define CHK_ALLOC(p)                                                           \
  do {                                                                         \
    if (!(p)) {                                                                \
      hr = E_OUTOFMEMORY;                                                      \
      goto Cleanup;                                                            \
    }                                                                          \
  } while (false)

// Macro that releases a COM object if not NULL.
#define SAFE_RELEASE(p)                                                        \
  do {                                                                         \
    if ((p)) {                                                                 \
      (p)->Release();                                                          \
      (p) = NULL;                                                              \
    }                                                                          \
  } while (false)

// Macros to safe delete objects and arrays
#define SAFE_DELETE(p)                                                         \
  do {                                                                         \
    if (p) {                                                                   \
      delete p;                                                                \
      p = 0;                                                                   \
    }                                                                          \
  } while (false)

#define SAFE_DELETEA(p)                                                        \
  do {                                                                         \
    if (p) {                                                                   \
      delete[] p;                                                              \
      p = 0;                                                                   \
    }                                                                          \
  } while (false)

#define FATAL_NULL(e)                                                          \
  do {                                                                         \
    if ((e) == 0) {                                                            \
      printf("Fatal at %s : %d\n", __FILE__, __LINE__);                        \
      __debugbreak();                                                          \
      getchar();                                                               \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (false)

//Contiguous memory allocation
using namespace std;

template <class T> inline void Alloc(T**& a, int n, int m)
{
    T* d, **dp;
    FATAL_NULL(d = new (nothrow) T[n * m]);
    FATAL_NULL(dp = new (nothrow) T*[n]);
    for (int i = 0; i < n; i++)
    {
        dp[i] = &d[i * m];
    }
    a = dp;
};

template <class T> inline void Free(T**& a)
{
    SAFE_DELETEA(a[0]);
    SAFE_DELETEA(a);
};


