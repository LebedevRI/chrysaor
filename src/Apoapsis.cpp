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

#include "src/Apoapsis.hpp"
#include "src/Apsis.hpp"               // for Apsis
#include "src/OrbitalEccentricity.hpp" // for OrbitalEccentricity
#include "src/SemiMajorAxis.hpp"       // for SemiMajorAxis

Apoapsis::operator double() const { return (sma_ * (1.0 + ecc_)); }

Apoapsis::Apoapsis(SemiMajorAxis sma, OrbitalEccentricity ecc,
                   CelestialBody *parentBody)
    : Apsis(sma, ecc, parentBody) {}
