#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>
#include <array>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <QMessageBox>

#include "info_storage.h"
#include "xmlbuilder.h"


std::array<MapPoint, 14> calculate_points(double longitude, double latitude, double azimuth, double size);

MapPoint calculate_position(double longitude, double latitude, double bearing, double distance);


std::pair<std::string,std::vector<SectorInfo>> read_csv(const std::string& inputFile);


std::string create_site_syle(const SectorInfo& info);

std::string create_sector_style(const SectorInfo& info);

std::string create_site_info(const SectorInfo& info);


#endif // UTILITY_FUNCTIONS_H
