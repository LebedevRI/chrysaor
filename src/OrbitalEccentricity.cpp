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

#include "src/OrbitalEccentricity.hpp"
#include "src/CelestialBody.hpp" // for CelestialBody
#include <cassert>               // for assert
#include <cmath>                 // for pow, isfinite, fmax, sqrt

OrbitalEccentricity::operator double() const { return (value_); }

OrbitalEccentricity::OrbitalEccentricity() : value_(0) {}

OrbitalEccentricity::OrbitalEccentricity(double eccentricity)
    : value_(eccentricity) {
  assert(std::isfinite(eccentricity));
  assert(eccentricity >= 0.0);
}

OrbitalEccentricity::OrbitalEccentricity(double ApR, double PeR) : value_(0) {
  assert(std::isfinite(ApR));
  assert(std::isfinite(PeR));

  assert(ApR >= PeR);

  assert(std::isfinite(ApR - PeR));
  assert(std::isfinite(ApR + PeR));
  assert((ApR + PeR) != 0.0);

  value_ = ((ApR - PeR) / (ApR + PeR));

  assert(std::isfinite(value_));
  assert(value_ >= 0.0);
}

OrbitalEccentricity::OrbitalEccentricity(double ApA, double PeA,
                                         CelestialBody *parentBody)
    : value_(0) {
  assert(parentBody);
  assert(std::isfinite(parentBody->R_));
  assert(parentBody->R_ >= 0.0);

  assert(std::isfinite(ApA));
  assert(std::isfinite(PeA));

  assert(ApA >= PeA);

  assert(std::isfinite(ApA - PeA));
  assert(std::isfinite(PeA + ApA));
  assert(std::isfinite(2.0 * (parentBody->R_)));

  assert(std::isfinite(2.0 * (parentBody->R_) + (PeA + ApA)));
  assert((2.0 * (parentBody->R_) + (PeA + ApA)) != 0.0);

  value_ = ((ApA - PeA) / (2.0 * (parentBody->R_) + (PeA + ApA)));

  // or:
  // value_ = ((ApA) / (2.0*(parentBody->R_) + (PeA + ApA))) - ((PeA) /
  // (2.0*(parentBody->R_) + (PeA + ApA)));

  assert(std::isfinite(value_));
  assert(value_ >= 0.0);
}

OrbitalEccentricity::OrbitalEccentricity(double Vx, double Vy, double altitude,
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

  assert(parentBody->mu_ != 0.0);

  // FIXME: awful precision due to fp
  // sqrt(alt^2*Vx^4 + alt^2*Vx^2*Vy^2 + mu^2 - 2*alt*mu*Vx^2) / mu
  // std::sqrt(((std::pow(altitude, 2.0))*(std::pow(Vx, 4.0)) +
  // (std::pow(altitude, 2.0))*(std::pow(Vx, 2.0))*(std::pow(Vy, 2.0)) +
  // (std::pow(parentBody->mu_, 2.0)) -
  // 2.0*altitude*(parentBody->mu_)*(std::pow(Vx, 2.0))) /
  // (std::pow(parentBody->mu_, 2.0)))

  // sqrt(mu^2 + alt^2*Vx^4 + alt^2*Vx^2*Vy^2 - 2*alt*mu*Vx^2) / mu
  //

  value_ = std::sqrt(
      ((std::pow(altitude, 2.0)) * (std::pow(Vx, 4.0)) +
       (std::pow(altitude, 2.0)) * (std::pow(Vx, 2.0)) * (std::pow(Vy, 2.0)) +
       (std::pow(parentBody->mu_, 2.0)) -
       2.0 * altitude * (parentBody->mu_) * (std::pow(Vx, 2.0))) /
      (std::pow(parentBody->mu_, 2.0)));

  // FIXME: !!!!!
  value_ = std::fmax(value_, 0.0);

  assert(std::isfinite(value_));
  assert(value_ >= 0.0);
}
