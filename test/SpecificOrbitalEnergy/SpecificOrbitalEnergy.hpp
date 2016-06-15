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

#pragma once

#include "test/EllipticalOrbit.hpp"
#include <gtest/gtest.h> // for AssertHelper, ASSERT_NO_THROW, ASSE...
#include <iomanip>       // for operator<<

class SpecificOrbitalEnergyTest
    : public ::testing::TestWithParam<EllipticalOrbitData> {};

INSTANTIATE_TEST_CASE_P(Kerbin, SpecificOrbitalEnergyTest,
                        testing::ValuesIn(KerbinEllipticalOrbitData));

INSTANTIATE_TEST_CASE_P(Earth, SpecificOrbitalEnergyTest,
                        testing::ValuesIn(EarthEllipticalOrbitData));
