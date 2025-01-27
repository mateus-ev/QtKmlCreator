/*
 *  author: Mateus Evangelista
 *  license model: GPLv3
*/

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


std::array<MapPoint, 14> calculate_points(double longitude, double latitude, double azimuth, double angle, double size);

MapPoint calculate_position(double longitude, double latitude, double bearing, double distance);


std::pair<std::string,std::vector<SectorInfo>> read_csv(const std::string& inputFile);


std::string create_site_info(const SectorInfo& info, bool siteLabel);

std::string create_sector_style(const SectorInfo& info, std::string color, bool randomColor);

std::string create_site_style(const SectorInfo& info);

std::string create_sector(const SectorInfo& info, int size, bool sectorIdentifier, bool sectorLabel);

std::string change_color_name_endian(const std::string color);


#endif // UTILITY_FUNCTIONS_H
