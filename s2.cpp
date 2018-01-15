#include "phpx.h"
#include <iostream>
#include <s2/s2latlng.h>
#include <s2/s2cap.h>
#include <s2/s2region_coverer.h>

#define EARTH_RADIUS 6371.01

using namespace php;
using namespace std;


double radius2height (double radius) {
    return 1 - sqrt(1 - pow((radius / EARTH_RADIUS), 2));
}

double height2radius (double height) {
    return sqrt(1 - pow(1 - height, 2)) * EARTH_RADIUS;
}

PHPX_FUNCTION(s2_cellid)
{
    if (args.count() != 2) {
        php::error(E_ERROR, "args: lat, lng");
    }

    Variant latV = args[0];
    Variant lngV = args[1];
    //Variant i = Variant();


    if (!latV.isFloat() || !lngV.isFloat()) {
        php::error(E_ERROR, "lat, lng must is float.");
    }

    double lat = latV.toFloat();
    double lng = lngV.toFloat();

    S2LatLng ll = S2LatLng::FromDegrees(lat, lng);
    S2Point point = ll.Normalized().ToPoint() ;
    S2CellId cellid = S2CellId(ll.Normalized());

    long cellidL = (long) cellid.id();
    Variant cellidV = Variant(cellidL);
    //ostringstream oss;
    //oss << cellid.id();
    //string cellidstring = oss.str();

    retval = cellidV;
    //retval = cellidstring;
}

PHPX_FUNCTION(s2_getconver)
{
    if (args.count() != 4) {
        php::error(E_ERROR, "args: lat, lng, radius, maxcell");
    }

    Variant latV = args[0];
    Variant lngV = args[1];
    Variant radiusV = args[2];
    Variant maxcellV = args[3];


    if (!latV.isFloat() || !lngV.isFloat() || !radiusV.isFloat()) {
        php::error(E_ERROR, "lat, lng, radius must is float.");
    }

    if (!maxcellV.isInt()) {
        php::error(E_ERROR, "maxcell must is int.");
    }

    double lat = latV.toFloat();
    double lng = lngV.toFloat();

    S2LatLng ll = S2LatLng::FromDegrees(lat, lng);
    S2Point point = ll.Normalized().ToPoint() ;
    S2Cap cap = S2Cap::FromCenterHeight(point, radius2height(2000/1000));

    S2RegionCoverer::Options options;
    options.set_min_level(0);
    options.set_max_level(30);
    options.set_level_mod(1);
    options.set_max_cells(maxcellV.toInt());

    S2RegionCoverer rc = S2RegionCoverer(options);

    S2CellUnion cells = rc.GetCovering(cap);

    std::vector<S2CellId>::const_iterator iter;

    Array ret;
    for (iter=cells.begin();iter!=cells.end();iter++)
    {
        Array item;
//        ostringstream oss1;
//        ostringstream oss2;
//        oss1 << iter->id();
//        oss2 << iter->next().id();
//
//        string cell = oss1.str();
//        string cellnext = oss2.str();
        long cellL = (long) iter->id();
        long cellnextL = (long) iter->next().id();
        Variant cellV = Variant(cellL);
        Variant cellnextV = Variant(cellnextL);
        item.append(cellV);
        item.append(cellnextV);
        ret.append(item);
    }

    retval = ret;
}


PHPX_EXTENSION()
{
    Extension *extension = new Extension("s2", "0.0.1");
    extension->registerFunction(PHPX_FN(s2_getconver));
    extension->registerFunction(PHPX_FN(s2_cellid));

    extension->info(
    {
            "s2test support", "enabled"
    },
    {
            { "author", "wayhood" },
            { "version", extension->version },
            { "date", "2018-01-11" },
    });
    return extension;
}
