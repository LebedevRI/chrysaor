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

#include "Stage.hpp"
#include <cstddef>

double Stage::dm() const {
  return (static_cast<double>(thrust_) / static_cast<double>(isp1_ * g0));
}

double Stage::maxT() const {
  return (static_cast<double>(fm_ * isp1_ * g0) / static_cast<double>(thrust_));
}

double Stage::TWR() const {
  return (static_cast<double>(thrust_) / static_cast<double>(launchMass_ * g0));
}

Stage::Stage(std::size_t launchMass, std::size_t thrust, std::size_t isp0,
             std::size_t isp1, std::size_t fm, std::size_t A)
    : launchMass_(launchMass), thrust_(thrust), isp0_(isp0), isp1_(isp1),
      fm_(fm), A_(A) {}
