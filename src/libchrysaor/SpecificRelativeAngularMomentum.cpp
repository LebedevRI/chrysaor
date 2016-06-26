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

#include "SpecificRelativeAngularMomentum.hpp"
#include "CelestialBody.hpp"                         // for CelestialBody
#include "OrbitalElements/OrbitalEccentricity.hpp"   // for OrbitalEccentricity
#include "OrbitalElements/SemiMajorAxis.hpp"         // for SemiMajorAxis
#include "OrbitalElements/SpecificOrbitalEnergy.hpp" // for SpecificOrbitalEnergy
#include <cassert>                                   // for assert
#include <cmath>                                     // for isfinite

SpecificRelativeAngularMomentum::operator double() const {
  assert(std::isfinite(value_));
  assert(value_ >= 0.0);

  return (value_);
}

SpecificRelativeAngularMomentum::SpecificRelativeAngularMomentum()
    : value_(0) {}

SpecificRelativeAngularMomentum::SpecificRelativeAngularMomentum(double srh)
    : value_(srh) {
  assert(std::isfinite(srh));
  assert(srh >= 0.0);
}

SpecificRelativeAngularMomentum::SpecificRelativeAngularMomentum(
    SemiMajorAxis sma, OrbitalEccentricity ecc, const CelestialBody *parentBody)
    : value_(0) {
  assert(parentBody);
  assert(std::isfinite(parentBody->mu_));
  assert(parentBody->mu_ >= 0);

  assert(std::isfinite(sma));

  assert(std::isfinite(ecc));
  assert(ecc >= 0.0);

  assert(std::isfinite((1.0 - (std::pow(ecc, 2.0))) * (parentBody->mu_) * sma));
  assert(((1.0 - (std::pow(ecc, 2.0))) * (parentBody->mu_) * sma) >= 0.0);

  value_ = std::sqrt((1.0 - (std::pow(ecc, 2.0))) * (parentBody->mu_) * sma);

  assert(std::isfinite(value_));
  assert(value_ >= 0.0);
}

SpecificRelativeAngularMomentum::SpecificRelativeAngularMomentum(
    SpecificOrbitalEnergy epsilon, OrbitalEccentricity ecc,
    const CelestialBody *parentBody)
    : value_(0) {
  assert(parentBody);
  assert(std::isfinite(parentBody->mu_));
  assert(parentBody->mu_ >= 0);

  assert(std::isfinite(epsilon));
  assert(epsilon != 0.0);

  assert(std::isfinite(ecc));
  assert(ecc >= 0.0);

  assert(std::isfinite(2.0 * epsilon));
  assert((2.0 * epsilon) != 0.0);

  assert(std::isfinite((std::pow(ecc, 2.0) * std::pow((parentBody->mu_), 2.0) -
                        std::pow((parentBody->mu_), 2.0)) /
                       (2.0 * epsilon)));
  assert(((std::pow(ecc, 2.0) * std::pow((parentBody->mu_), 2.0) -
           std::pow((parentBody->mu_), 2.0)) /
          (2.0 * epsilon)) >= 0.0);

  value_ = std::sqrt((std::pow(ecc, 2.0) * std::pow((parentBody->mu_), 2.0) -
                      std::pow((parentBody->mu_), 2.0)) /
                     (2.0 * epsilon));

  assert(std::isfinite(value_));
  assert(value_ >= 0.0);
}

SpecificRelativeAngularMomentum::SpecificRelativeAngularMomentum(
    double Vx, double altitude, const CelestialBody *parentBody)
    : value_(0) {
  assert(parentBody);
  assert(std::isfinite(parentBody->R_));
  assert(parentBody->R_ >= 0.0);

  assert(std::isfinite(Vx));
  assert(Vx >= 0.0);
  assert(Vx <= 11000.0);

  assert(std::isfinite(altitude));

  // all math assumes the radius to be from the center of patent body.
  altitude += parentBody->R_;

  assert(std::isfinite(altitude));
  assert(altitude > 0.0);

  // sqrt(abs(Vx)^2*abs(alt)^2)
  value_ = (Vx * altitude);

  assert(std::isfinite(value_));
  assert(value_ >= 0.0);
}
