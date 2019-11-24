#ifndef HEADER_UTIL_HXX
#define HEADER_UTIL_HXX

inline std::string scm_to_cxxstring(SCM value)
{
  char* str = scm_to_utf8_string(value);
  std::string cxxstr = str;
  free(str);
  return cxxstr;
}

#endif

/* EOF */
