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

#include "src/SemiMajorAxis.hpp"                   // for SemiMajorAxis
#include "src/CelestialBody.hpp"                   // for CelestialBody
#include "src/OrbitalEccentricity.hpp"             // for OrbitalEccentricity
#include "src/SpecificOrbitalEnergy.hpp"           // for SpecificOrbitalEnergy
#include "src/SpecificRelativeAngularMomentum.hpp" // for SpecificRelativeAngularMomentum
#include <cassert>                                 // for assert
#include <cmath>                                   // for pow

SemiMajorAxis::operator double() const {
  assert(std::isfinite(value_));

  return (value_);
}

SemiMajorAxis::SemiMajorAxis() : value_(0) {}

SemiMajorAxis::SemiMajorAxis(double sma) : value_(sma) {
  assert(std::isfinite(sma));
}

SemiMajorAxis::SemiMajorAxis(SpecificOrbitalEnergy epsilon,
                             CelestialBody *parentBody)
    : value_(0) {
  assert(std::isfinite(epsilon));
  assert(epsilon != 0.0);

  assert(parentBody);
  assert(std::isfinite(parentBody->mu_));
  assert(parentBody->mu_ >= 0);

  assert(std::isfinite(2.0 * epsilon));
  assert((2.0 * epsilon) != 0.0);

  value_ = (-parentBody->mu_) / (2.0 * epsilon);

  assert(std::isfinite(value_));
}

SemiMajorAxis::SemiMajorAxis(double ApR, double PeR) : value_(0) {
  assert(std::isfinite(ApR));
  assert(std::isfinite(PeR));

  value_ = (ApR + PeR) / 2.0;

  assert(std::isfinite(value_));
}

SemiMajorAxis::SemiMajorAxis(double ApA, double PeA, CelestialBody *parentBody)
    : value_(0) {
  assert(parentBody);
  assert(std::isfinite(parentBody->R_));
  assert(parentBody->R_ >= 0.0);

  assert(std::isfinite(ApA));
  assert(std::isfinite(PeA));

  // we got altitude, i.e. distance to the surface,
  // but we need distance to the center of mass
  const double ApR = ApA + parentBody->R_;
  const double PeR = PeA + parentBody->R_;

  assert(std::isfinite(ApR));
  assert(std::isfinite(PeR));

  value_ = SemiMajorAxis(ApR, PeR);

  assert(std::isfinite(value_));
}

SemiMajorAxis::SemiMajorAxis(OrbitalEccentricity ecc,
                             SpecificRelativeAngularMomentum srh,
                             CelestialBody *parentBody)
    : value_(0) {
  assert(parentBody);
  assert(std::isfinite(parentBody->mu_));
  assert(parentBody->mu_ >= 0);

  assert(std::isfinite(ecc));
  assert(ecc >= 0.0);

  assert(std::isfinite(srh));
  assert(srh >= 0.0);

  assert(std::isfinite(((1.0 - (std::pow(ecc, 2.0))) * (parentBody->mu_))));
  assert(((1.0 - (std::pow(ecc, 2.0))) * (parentBody->mu_)) != 0.0);

  value_ =
      (std::pow(srh, 2.0) / ((1.0 - (std::pow(ecc, 2.0))) * (parentBody->mu_)));

  assert(std::isfinite(value_));
}

SemiMajorAxis::SemiMajorAxis(double Vx, double Vy, double altitude,
                             CelestialBody *parentBody)
    : value_(0) {
  assert(parentBody);
  assert(std::isfinite(parentBody->mu_));
  assert(parentBody->mu_ >= 0);

  assert(std::isfinite(Vx));
  assert(Vx >= 0.0);
  assert(Vx <= 11000.0);

  assert(std::isfinite(Vy));
  assert(Vy >= -1000.0);
  assert(Vy <= 1000.0);

  assert(std::isfinite(parentBody->R_));
  assert(parentBody->R_ >= 0.0);

  assert(std::isfinite(altitude));

  // all math assumes the radius to be from the center of patent body.
  altitude += parentBody->R_;

  assert(std::isfinite(altitude));
  assert(altitude != 0.0);
  assert(altitude > 0.0);

  assert(std::isfinite((parentBody->mu_) / altitude));
  assert(((parentBody->mu_) / altitude) != 0.0);

  assert(std::isfinite((2.0 - ((std::pow(Vx, 2.0) + std::pow(Vy, 2.0)) /
                               ((parentBody->mu_) / altitude)))));
  assert(((2.0 - ((std::pow(Vx, 2.0) + std::pow(Vy, 2.0)) /
                  ((parentBody->mu_) / altitude)))) != 0.0);

  value_ = ((altitude) / (2.0 - ((std::pow(Vx, 2.0) + std::pow(Vy, 2.0)) /
                                 ((parentBody->mu_) / altitude))));

  assert(std::isfinite(value_));
}
