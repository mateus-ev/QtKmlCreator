#include "utility_functions.h"

//WGS84 parameters
constexpr double majorAxis = 6378137.f;
constexpr double minorAxis = 6356752.314245f;
constexpr double flattening = (majorAxis - minorAxis)/majorAxis;

std::array<MapPoint, 14> calculate_points(double longitude, double latitude, double azimuth, double angle, double size)
{
    std::array<MapPoint, 14> sectorPoints;

    double deltaAngle = static_cast<double>(angle)/(sectorPoints.size()-2); //angle variation for each segment on the sector arc

    sectorPoints.at(0) = MapPoint(longitude, latitude, 0); // first point - size position

    double segmentAngle;

    for(size_t i = 1; i < sectorPoints.size() ; i++)
    {
        segmentAngle = azimuth + (static_cast<int>(i) - static_cast<int>(sectorPoints.size()/2))*deltaAngle;
        sectorPoints.at(i) = calculate_position(longitude, latitude, segmentAngle, size);

    }
    return sectorPoints;
}


MapPoint calculate_position(double longitude, double latitude, double bearing, double distance)
{
    double longitude_rad = longitude*M_PI/180.0;
    double latitude_rad = latitude*M_PI/180.0;
    double bearing_rad = bearing*M_PI/180.0;

    double tan_u1 = (1.0-flattening) * std::tan(latitude_rad);
    double cos_u1 = 1.0/std::sqrt(1.0 + tan_u1*tan_u1);
    double sin_u1 = tan_u1*cos_u1;
    double sigma1 = std::atan2(tan_u1, std::cos(bearing_rad));
    double sin_alpha = cos_u1*std::sin(bearing_rad);
    double cos_squared_alpha = 1.0 - sin_alpha*sin_alpha;
    double u_squared = cos_squared_alpha*(majorAxis*majorAxis - minorAxis*minorAxis)/(minorAxis*minorAxis);
    double A = 1.0 + (u_squared/16384.0)*(4096.0 + u_squared*(-768.0 + u_squared*(320.0-175.0*u_squared)));
    double B = (u_squared/1024.0)*(256.0 + u_squared*(-128.0 + u_squared*(74.0 - 47.0*u_squared)));
    double sigma = distance/(minorAxis*A);

    double delta_sigma = 1.0;
    double cos_2_sig_m;


    size_t iter_count = 0;
    while ( delta_sigma > 0.00000000000001 && iter_count < 200)
    {
        cos_2_sig_m = std::cos(2.0*sigma1 + sigma);
        delta_sigma = B * std::sin(sigma)*(cos_2_sig_m + (B/4.0)*(std::cos(sigma)*(-1.0+2.0*cos_2_sig_m*cos_2_sig_m)
                      - (B/6.0)*cos_2_sig_m*(-3.0+4.0*std::sin(sigma)*std::sin(sigma))*(-3.0+4.0*cos_2_sig_m*cos_2_sig_m)));
        sigma = distance/(minorAxis*A) + delta_sigma;
        ++iter_count;
    }

    double cos_bearing = std::cos(bearing_rad);
    double sin_bearing = std::sin(bearing_rad);
    double temp_val = sin_u1*std::sin(sigma) - cos_u1*std::cos(sigma)*cos_bearing;
    double final_lat_rad = std::atan2(sin_u1*std::cos(sigma) + cos_u1*std::sin(sigma)*cos_bearing,
            (1.f-flattening)*std::sqrt(sin_alpha*sin_alpha + temp_val*temp_val));

    double lamb = std::atan2(std::sin(sigma)*sin_bearing, cos_u1*std::cos(sigma) - sin_u1*std::sin(sigma)*cos_bearing);

    double C = (flattening/16.0)*cos_squared_alpha*(4.0 + flattening*(4.0 - 3.0*cos_squared_alpha));

    double L = lamb - (1.0 - C)*flattening*sin_alpha*(sigma + C*std::sin(sigma)*(cos_2_sig_m + C*std::cos(sigma)*(-1.0 + 2.0*cos_2_sig_m*cos_2_sig_m)));

    double final_lon_rad = longitude_rad + L;

    double final_lat = final_lat_rad*180.0/M_PI;
    double final_lon = final_lon_rad*180.0/M_PI;

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


std::string create_site_info(const SectorInfo& info)
{
    XmlBuilder placemark("Placemark","","");
    XmlBuilder name(info.m_SiteName,"","");
    XmlBuilder styleUrl("styleUrl", "", "#"+info.m_SiteName);
    XmlBuilder description("description","", info.str());
    XmlBuilder point("Point","","");
    XmlBuilder coordinates("coordinates","",info.m_SitePosition.str());

    point.add_child(coordinates);

    placemark.add_child(name).add_child(styleUrl).add_child(description).add_child(point);

    return placemark.str();
}

std::string create_sector_style(const SectorInfo& info)
{
    XmlBuilder style("Style"," id=\""+ info.m_SectorName + "\"", "");
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

std::string create_site_style(const SectorInfo& info)
{
    XmlBuilder style("Style"," id=\""+ info.m_SiteName + "\"", "");
    XmlBuilder icon_style("IconStyle", "", "");
    XmlBuilder colormode("colormode","","normal");
    XmlBuilder scale("scale","","0.7");
    XmlBuilder icon("Icon", "","");
    XmlBuilder href("href","","SymbolBts_New.png");
    XmlBuilder label("LabelStyle","","");
    XmlBuilder labelscale("scale","","0.7000");

    icon.add_child(href);
    icon_style.add_child(colormode).add_child(scale).add_child(icon);
    label.add_child(labelscale);
    style.add_child(icon_style).add_child(label);

    return style.str();
}

std::string create_sector(const SectorInfo& info, int size)
{
    XmlBuilder placemark("Placemark","","");
    XmlBuilder name("name","",std::to_string(info.m_Identifier));
    XmlBuilder styleUrl("styleUrl","","#"+info.m_SectorName);
    XmlBuilder multigeo("MultiGeometry","","");
    XmlBuilder polygon("Polygon","","");
    XmlBuilder extrude("extrude","","1");
    XmlBuilder altitude("altitudeMode","","clampToGround");
    XmlBuilder outer("outerBoundaryIs","","");
    XmlBuilder linear("LinearRing","","");

    std::string sectorGeoPoints;
    auto geometry_points = [=](SectorInfo site)
    {
        return calculate_points(site.m_SitePosition.m_Longitude, site.m_SitePosition.m_Latitude, site.m_Azimuth, site.m_Angle, size);
    };

    auto points = geometry_points(info);
    for(const auto& element: points)
        sectorGeoPoints += element.str() + " ";

    sectorGeoPoints = sectorGeoPoints.substr(0, sectorGeoPoints.size()-1);


    XmlBuilder geometry_coordinates("coordinates","",sectorGeoPoints);
    XmlBuilder point("Point","","");
    XmlBuilder point_coordinate("coordinate", "", points[points.size()/2].str());

    linear.add_child(geometry_coordinates);
    outer.add_child(linear);
    polygon.add_child(extrude).add_child(altitude).add_child(outer);

    point.add_child(point_coordinate);
    multigeo.add_child(polygon).add_child(point);

    placemark.add_child(name).add_child(styleUrl).add_child(multigeo);

    return placemark.str();

}




