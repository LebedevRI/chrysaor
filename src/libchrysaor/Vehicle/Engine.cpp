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

#include "Vehicle/Engine.hpp"
#include <cassert> // for assert
#include <cmath>   // for isfinite

double Engine::thrust(double p) const {
  assert(std::isfinite(p));
  assert(p >= 0.0);

  assert(thrust_.size() > 0);

  return thrust_[p];
}

double Engine::isp(double p) const {
  assert(std::isfinite(p));
  assert(p >= 0.0);

  assert(isp_.size() > 0);

  return isp_[p];
}

double Engine::exhaustVelocity(double p) const {
  assert(std::isfinite(p));
  assert(p >= 0.0);

  assert(isp_.size() > 0);

  assert(std::isfinite(g0));
  assert(std::isfinite(isp_[p]));

  const double v = isp_[p] * g0;

  assert(std::isfinite(v));

  return v;
}

double Engine::massFlow(double p) const {
  assert(std::isfinite(p));
  assert(p >= 0.0);

  assert(thrust_.size() > 0);
  assert(isp_.size() > 0);

  assert(std::isfinite(g0));
  assert(std::isfinite(isp_[p]));
  assert(g0 != 0.0);
  assert((isp_[p]) != 0.0);
  assert((isp_[p] * g0) != 0.0);

  const double dm = thrust_[p] / (isp_[p] * g0);

  assert(std::isfinite(dm));

  return dm;
}

Engine::Engine() {}

Engine::Engine(double thrust0, double isp0)
    : thrust_(AbstractCurve<LinearCurvePoint>({LinearCurvePoint(0, thrust0)})),
      isp_(AbstractCurve<LinearCurvePoint>({LinearCurvePoint(0, isp0)})) {
  assert(thrust_.size() == 1);
  assert(isp_.size() == 1);
}

Engine::Engine(AbstractCurve<LinearCurvePoint> thrust,
               AbstractCurve<LinearCurvePoint> isp)
    : thrust_(thrust), isp_(isp) {
  assert(thrust.size() > 0);
  assert(isp.size() > 0);
}
