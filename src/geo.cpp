#include "GeoIP.h"
#include <string>
namespace se{

GeoIP * geo_v4;
GeoIP * geoAS_v4;
GeoIP * geo_v6;
GeoIP * geoAS_v6;

void init_geoip(const std::string &geoipdir)
{
    std::string cc4;
    std::string as4;
    std::string cc6;
    std::string as6;

    cc4 = geoipdir + "GeoIP.dat";
    as4 = geoipdir + "GeoIPASNum.dat";
    cc6 = geoipdir + "GeoIPv6.dat";
    as6 = geoipdir + "GeoIPASNumv6.dat";

    geo_v4 = GeoIP_open(cc4.c_str(), GEOIP_MEMORY_CACHE);
    if (geo_v4 == NULL) {
        fprintf(stderr, "Error opening IPv4 Country GeoIP database\n");
    }
    geoAS_v4 = GeoIP_open(as4.c_str(), GEOIP_MEMORY_CACHE);
    if (geoAS_v4 == NULL) {
        fprintf(stderr, "Error opening IPv4 AS GeoIP database\n");
    }
    geo_v6 = GeoIP_open(cc6.c_str(), GEOIP_MEMORY_CACHE);
    if (geo_v6 == NULL) {
        fprintf(stderr, "Error opening IPv6 Country GeoIP database\n");
    }
    geoAS_v6 = GeoIP_open(as6.c_str(), GEOIP_MEMORY_CACHE);
    if (geoAS_v6 == NULL) {
        fprintf(stderr, "Error opening IPv6 AS GeoIP database\n");
    }
}

const char *lookup_cc(char const* host)
{
    const char* cc = NULL;
    const char* ipv6 = strchr(host, ':');
    if (ipv6 != NULL && geo_v6 != NULL){
        cc = GeoIP_country_code_by_addr_v6 (geo_v6, host);
    } else if (geo_v4 != NULL) {
        cc = GeoIP_country_code_by_addr (geo_v4, host);
    }
    if (cc != NULL) {
        return cc;
    } else {
        return "UNKNOWN";
    }
}

const char *lookup_as(char const* host)
{
    const char* org = NULL;
    const char* ipv6 = strchr(host, ':');
    if (ipv6 != NULL && geoAS_v6 != NULL){
        org = GeoIP_org_by_name_v6 (geoAS_v6, host);
    } else if (geoAS_v4 != NULL) {
        org = GeoIP_org_by_name (geoAS_v4, host);
    }
    if (org != NULL) {
        return org;
    } else {
        return "UNKNOWN";
    }
}
}
