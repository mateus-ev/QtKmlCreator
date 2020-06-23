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



std::array<MapPoint, 14> calculate_points(double longitude, double latitude, double azimuth, double size);

MapPoint calculate_position(double longitude, double latitude, double bearing, double distance);


std::pair<std::string,std::vector<SectorInfo>> read_csv(const std::string& inputFile);




#endif // UTILITY_FUNCTIONS_H
