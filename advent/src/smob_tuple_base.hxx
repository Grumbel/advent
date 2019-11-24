/**
 */
template<class T>
class SmobTuple
{
private:
  T* data;
  SCM scm;

public:
  explicit SmobTuple () {
    data = 0;
    scm = SCM_BOOL_F;
    Guile::protect_object (scm);
  }

  SmobTuple (const SmobTuple<T>& obj)
    : data (obj.data), scm (obj.scm)
  {
    Guile::protect_object (scm);
  }

  explicit SmobTuple (SCM arg_scm) {
    scm = arg_scm;
    Guile::protect_object (scm);
    if (arg_scm != SCM_BOOL_F) {
      data = smobbox_cast<T>(scm);
    } else {
      data = 0;
    }
  }

  ~SmobTuple () {
    Guile::unprotect_object (scm);
  }

  SmobTuple<T>& operator=(const SmobTuple<T>& obj) {
    Guile::unprotect_object (scm);

    data = obj.data;
    scm  = obj.scm;

    Guile::protect_object (scm);

    return *this;
  }

  bool is_a (SCM smob)
  {
    return T::is_a (smob);
  }

  T* get () const {
    if (data == 0)
      {
	std::cout << "SmobTuple: Warring data = 0: "  << typeid (T).name () << std::endl;
	std::cout << "SmobTuple: Type: " << std::flush;
	scm_display(scm, scm_current_output_port());
        scm_newline(scm_current_output_port());
      }
    return data;
  }

  SCM get_scm () {
    return scm;
  }

  void mark () {
    scm_gc_mark (scm);
  }

  void set_scm (SCM arg_scm) {
    Guile::unprotect_object (scm);

    scm = arg_scm;
    Guile::protect_object (scm);

    data = smobbox_cast<T>(scm);
  }

  void release ()
  {
    Guile::unprotect_object (scm);
    data = 0;
    scm = SCM_BOOL_F;
    Guile::protect_object (SCM_BOOL_F);
  }

  bool operator==(const SmobTuple<T>& smob) const
  {
    return (data == smob.data);
  }
};

