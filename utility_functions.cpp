#include "utility_functions.h"

//WGS84 parameters
constexpr double majorAxis = 6378137.0;
constexpr double minorAxis = 6356752.314245;
constexpr double flattening = (majorAxis - minorAxis)/majorAxis;

std::array<MapPoint, 14> calculate_points(double longitude, double latitude, double azimuth, double size)
{
    double deltaAngle = azimuth/13.f; //angle variation for each segment on the sector arc

    std::array<MapPoint, 14> sectorPoints;

    sectorPoints.at(0) = MapPoint(longitude, latitude, 0); // first point - size position

    size_t sidePoints = (sectorPoints.size() - 1)/2; //number of points of each side of the arc center
    //size_t numberPoints = sectorPoints.size() - 1; //number of points of the sector arc
    size_t arrayIndex = 0;
    for(size_t i = -sidePoints; i <= sidePoints ; i++)
    {
        sectorPoints.at(++arrayIndex) = calculate_position(longitude, latitude, azimuth + (i*deltaAngle), size);
    }
    return sectorPoints;
}




MapPoint calculate_position(double longitude, double latitude, double bearing, double distance)
{
    double longitude_rad = longitude*M_PI/180.;
    double latitude_rad = latitude*M_PI/180.;
    double bearing_rad = bearing*M_PI/180.;

    double tan_u1 = (1-flattening)* (M_PI/180.) * std::cos(latitude_rad);
    double cos_u1 = 1./std::sqrt(1 + tan_u1 * tan_u1);
    double sin_u1 = tan_u1*cos_u1;
    double sigma1 = std::atan2(tan_u1, std::cos(bearing_rad));
    double sin_alpha = cos_u1*std::sin(bearing_rad);
    double cos_squared_alpha = 1. - sin_alpha*sin_alpha;
    double u_squared = cos_squared_alpha*(majorAxis*majorAxis - minorAxis*minorAxis)/(minorAxis*minorAxis);
    double A = 1 + (u_squared/16384)*(4096 + u_squared*(-768 + u_squared*(320-175*u_squared)));
    double B = (u_squared/1024)*(256 + u_squared*(-128 + u_squared*(74 - 47*u_squared)));
    double sigma = distance/(minorAxis*A);

    double delta_sigma;
    double cos_2_sig_m;


    size_t iter_count = 0;
    while ( delta_sigma > 0.000000000001 && iter_count < 100)
    {
        cos_2_sig_m = std::cos(2*sigma1 + sigma);
        delta_sigma = B * std::sin(sigma)*(cos_2_sig_m + (B/4)*(std::cos(sigma)*(-1+2*cos_2_sig_m*cos_2_sig_m)
                      - (B/6)*cos_2_sig_m*(-3+4*std::sin(sigma)*std::sin(sigma))*(-3+4*cos_2_sig_m*cos_2_sig_m)));
        sigma = distance/(minorAxis*A) + delta_sigma;
        ++iter_count;
    }

    double cos_bearing = std::cos(bearing_rad);
    double sin_bearing = std::sin(bearing_rad);
    double temp_val = sin_u1*std::sin(sigma) - cos_u1*std::cos(sigma)*cos_bearing ;
    double final_lat_rad = std::atan2(sin_u1*std::cos(sigma) + cos_u1*std::sin(sigma)*cos_bearing,
            (1-flattening)*std::sqrt(sin_alpha*sin_alpha + temp_val*temp_val));

    double lamb = std::atan2(std::sin(sigma)*sin_bearing, cos_u1*std::cos(sigma) - sin_u1*std::sin(sigma)*cos_bearing);

    double C = (flattening/16)*cos_squared_alpha*(4 + flattening*(4 - 3*cos_squared_alpha));

    double L = lamb - (1 - C)*flattening*sin_alpha*(sigma + C*std::sin(sigma)*(cos_2_sig_m + C*std::cos(sigma)*(-1 + 2*cos_2_sig_m*cos_2_sig_m)));

    double final_lon_rad = longitude_rad + L;

    double final_lat = final_lat_rad*180/M_PI;
    double final_lon = final_lon_rad*180/M_PI;

    return {final_lon, final_lat, 0};

}
