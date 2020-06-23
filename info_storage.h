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
        return  m_SiteName + "\n"
                + m_SectorName + "\n"
                + "identifier: " + std::to_string(m_Identifier) + "\n"
                + "latitude: " + std::to_string(m_SitePosition.m_Latitude) + "\n"
                + "longitude: " + std::to_string(m_SitePosition.m_Longitude) + "\n"
                + "altitude: " + std::to_string(m_SitePosition.m_Altitude) + "\n"
                + "azimuth: " + std::to_string(m_Azimuth) + "\n"
                + "angle: " + std::to_string(m_Angle) + "\n";
    }

};


#endif // INFO_STORAGE_H
