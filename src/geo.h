#ifndef GEO_H
#define GEO_H
namespace se{
const char *lookup_as(char const* host);
const char *lookup_cc(char const* host);

void init_geoip(const std::string &geoipdir);


}
#endif

