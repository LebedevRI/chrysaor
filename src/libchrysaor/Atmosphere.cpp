/*
 *    This file is part of chrysaor.
 *    copyright (c) 2016 Roman Lebedev.
 *
 *    chrysaor is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    chrysaor is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with chrysaor.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Atmosphere.hpp"
#include "Curve/AbstractCurve.hpp" // for AbstractCurve
#include "IdealGas.hpp"            // for IdealGas
#include <cassert>                 // for assert
#include <cmath>                   // for isfinite

double Atmosphere::Pressure(double altitude) const {
  assert(std::isfinite(altitude));
  assert(altitude >= 0.0);

  const double p = (*pressure_)[altitude];

  assert(std::isfinite(p));
  assert(p >= 0.0);

  return p;
}

double Atmosphere::Temperature(double altitude) const {
  assert(std::isfinite(altitude));
  assert(altitude >= 0.0);

  const double t = (*temperature_)[altitude];

  assert(std::isfinite(t));
  assert(t >= 0.0);

  return t;
}

double Atmosphere::Density(double altitude) const {
  assert(std::isfinite(altitude));
  assert(altitude >= 0.0);

  assert(std::isfinite(Pressure(altitude)));
  assert(std::isfinite(Temperature(altitude)));

  const double rho =
      IdealGas::Density(Pressure(altitude), Temperature(altitude));

  assert(std::isfinite(rho));
  assert(rho >= 0.0);

  return rho;
}

Atmosphere::Atmosphere(AbstractCurve<LinearCurvePoint> *atmPressure,
                       AbstractCurve<LinearCurvePoint> *atmTemperature)
    : pressure_(atmPressure), temperature_(atmTemperature) {
  assert(atmPressure);
  assert(atmTemperature);

  assert(atmPressure->size() != 0);
  assert(atmTemperature->size() != 0);
}
