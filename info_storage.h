#ifndef INFO_STORAGE_H
#define INFO_STORAGE_H

struct MapPoint
{
    MapPoint(){}
    MapPoint(double longitude, double latitude, int altitude):
        longitude(longitude), latitude(latitude), altitude(altitude){}
    double longitude;
    double latitude;
    int altitude = 0;
};


#endif // INFO_STORAGE_H
