/*
 *  author: Mateus Evangelista
 *  license model:
*/

#ifndef INFO_STORAGE_H
#define INFO_STORAGE_H

#include <string>

struct MapPoint
{
    MapPoint(){}
    MapPoint(double longitude, double latitude, int altitude):
        m_Longitude(longitude), m_Latitude(latitude), m_Altitude(altitude){}
    double m_Longitude;
    double m_Latitude;
    int m_Altitude = 0;
    std::string str() const
    {
        return std::to_string(m_Longitude) + "," + std::to_string(m_Latitude) + "," + std::to_string(m_Altitude);
    }
};


struct SectorInfo
{
    SectorInfo(){}

    MapPoint m_SitePosition;
    std::string m_SiteName;
    std::string m_SectorName;
    int m_Identifier;
    double m_Angle;
    double m_Azimuth;

    std::string str() const
    {
        return  "Site: " + m_SiteName + "\n"
                + "longitude: " + std::to_string(m_SitePosition.m_Longitude) + "\n"
                + "latitude: " + std::to_string(m_SitePosition.m_Latitude) + "\n"
                + "altitude: " + std::to_string(m_SitePosition.m_Altitude);

    }

};


#endif // INFO_STORAGE_H
