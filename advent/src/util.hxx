#ifndef HEADER_UTIL_HXX
#define HEADER_UTIL_HXX

inline std::string scm_to_cxxstring(SCM value)
{
  char* str = scm_to_utf8_string(value);
  std::string cxxstr = str;
  free(str);
  return cxxstr;
}

inline SCM gh_c_define_public_gsubr(const char* name, int req, int opt, int rst, scm_t_subr fcn)
{
  SCM scm = scm_c_define_gsubr(name, req, opt, rst, fcn);
  scm_c_export(name);
  return scm;
}

#endif

/* EOF */
