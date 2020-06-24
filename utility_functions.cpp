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

    int sidePoints = (sectorPoints.size() - 1)/2; //number of points of each side of the arc center
    //size_t numberPoints = sectorPoints.size() - 1; //number of points of the sector arc
    size_t arrayIndex = 0;
    for(int i = -sidePoints; i <= sidePoints ; i++)
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


std::pair<std::string,std::vector<SectorInfo>> read_csv(const std::string& inputFile)
{
    std::ifstream inputStream(inputFile, std::ios::in);
    std::vector<SectorInfo> sectors;

    std::istringstream iss;

    std::string line;
    std::string columnNames;

    if(inputStream.is_open())
    {

        std::getline(inputStream, columnNames); // getting column names
        //change the function to capture the column names
        while(std::getline(inputStream, line))
        {
            SectorInfo info;
            MapPoint siteLocation;

            std::replace(line.begin(), line.end(), ',',' ');
            iss.str(line.c_str());

            iss >> info.m_SiteName;
            iss >> info.m_SectorName;
            iss >> siteLocation.m_Latitude;
            iss >> siteLocation.m_Longitude;
            info.m_SitePosition = siteLocation;
            iss >> info.m_Azimuth;
            iss >> info.m_Angle;
            iss >> info.m_Identifier;

            sectors.push_back(info);
            iss.clear();
        }
        inputStream.close();
    }

    return {columnNames, sectors};
}


std::string create_site_syle(const SectorInfo& info)
{

    return {};
}


std::string create_sector_style(const SectorInfo& info)
{
    XmlBuilder style("Style id=\"", info.m_SectorName + "\"", "");
    XmlBuilder labelStyle("LabelStyle","","");
    XmlBuilder labelScale("scale", "", "0.500");
    XmlBuilder icon("IconStyle","","");
    XmlBuilder iconScale("scale","","0");
    XmlBuilder polyStyle("PolyStyle","","");
    XmlBuilder polyColor("color","","ff0000ff");
    XmlBuilder colorMode("colorMode","","normal");
    XmlBuilder fill("fill","","1");
    XmlBuilder outline("outline","","1");
    XmlBuilder lineStyle("LyneStyle","","");
    XmlBuilder lineColor("color","", "ff000000");
    XmlBuilder lineScale("scale","","1");
    XmlBuilder width("width","","1");

    labelStyle.add_child(labelScale);
    icon.add_child(iconScale);
    polyStyle.add_child(polyColor).add_child(colorMode).add_child(fill).add_child(outline);
    lineStyle.add_child(lineColor).add_child(lineScale).add_child(width);

    style.add_child(labelStyle).add_child(icon).add_child(polyStyle).add_child(lineStyle);

    return style.str();
}

std::string create_site_info(const SectorInfo& info)
{
    XmlBuilder style("Style id=\"", info.m_SiteName + "\"", "");
    XmlBuilder icon_style("IconStyle", "", "");
    XmlBuilder colormode("colormode","","normal");
    XmlBuilder scale("scale","","0.7");
    XmlBuilder icon("Icon", "","");
    XmlBuilder href("href","","");
    XmlBuilder label("LabelStyle","","");
    XmlBuilder labelscale("scale","","0.7000");

    icon.add_child(href);
    icon_style.add_child(colormode).add_child(scale).add_child(icon);
    label.add_child(labelscale);
    style.add_child(icon_style).add_child(label);

    return style.str();
}




