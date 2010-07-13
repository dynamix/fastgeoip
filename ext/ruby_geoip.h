#ifndef __RUBY_GEOIP_H__
#define __RUBY_GEOIP_H__

#include <ruby.h>
#include <rubyio.h>
#include "GeoIP.h"

VALUE cFastGeoIP;
VALUE eFastGeoIPError;

typedef struct fast_geoip {
  GeoIP *db;
} fast_geoip;

#endif
