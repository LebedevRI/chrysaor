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

#include "OrbitalElements/Periapsis.hpp"
#include "OrbitalElements/Apsis.hpp"               // for Apsis
#include "OrbitalElements/OrbitalEccentricity.hpp" // for OrbitalEccentricity
#include "OrbitalElements/SemiMajorAxis.hpp"       // for SemiMajorAxis

Periapsis::operator double() const { return (sma_ * (1.0 - ecc_)); }

Periapsis::Periapsis(SemiMajorAxis sma, OrbitalEccentricity ecc,
                     const CelestialBody *parentBody)
    : Apsis(sma, ecc, parentBody) {}
