/* $Id: geoip.c,v 1.6 2002/11/19 21:21:38 sean Exp $ */

#include "ruby_geoip.h"
#include "GeoIP.h"

VALUE geoip_country_code_by_addr(VALUE self, VALUE addr) {
  fast_geoip *fgi;
  char *cc;

  Check_Type(addr, T_STRING);
  Data_Get_Struct(self, fast_geoip, fgi);
  cc = (char *)GeoIP_country_code_by_addr(fgi->db, STR2CSTR(addr));
  if (cc == NULL) {
    return(Qnil);
  } else {
    return(rb_str_new2(cc));
  }
}


void geoip_free(fast_geoip *fgi) {
  if (fgi->db != NULL)
    GeoIP_delete(fgi->db);
  free(fgi);
}


VALUE geoip_open(int argc, VALUE *argv, VALUE class) {
  fast_geoip *fgi;
  VALUE filename;

  if (argc == 1) {
    rb_scan_args(argc, argv, "01", &filename);
    Check_Type(filename, T_STRING);
  } else
    rb_raise(rb_eArgError, "wrong number of arguments (needs 1 : filename of db)");
    
  fgi = ALLOC(fast_geoip);
  fgi->db = GeoIP_open(STR2CSTR(filename), GEOIP_MEMORY_CACHE);
  return(Data_Wrap_Struct(class, 0, geoip_free, fgi));
}


VALUE geoip_database_info(VALUE self) {
  fast_geoip *fgi;
  Data_Get_Struct(self, fast_geoip, fgi);
  return(rb_str_new2(GeoIP_database_info(fgi->db)));
}


void Init_fastgeoip(void) {
  cFastGeoIP = rb_define_class("FastGeoIp", rb_cObject);
  eFastGeoIPError = rb_define_class_under(cFastGeoIP, "Error", rb_eException);

  rb_define_singleton_method(cFastGeoIP, "open", geoip_open, -1);

  rb_define_method(cFastGeoIP, "country_code_by_addr", geoip_country_code_by_addr, 1);
  rb_define_method(cFastGeoIP, "database_info", geoip_database_info, 0);
}
