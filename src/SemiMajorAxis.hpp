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

#include "src/CelestialBody.hpp" // for CelestialBody
#include <cassert>               // for assert
#include <cmath>                 // for pow

/**
 * @brief semi-major axis class
 *
 * The semi-major axis is the one half of major axis.
 * In geometry, the major axis is the longest diameter of an ellipse.
 * It is a line segment with ends at the widest points of the perimeter,
 * that runs through the center and both foci.
 *
 * It a nutshell, semi-major axis is the radius of an orbit at the orbit's
 * 2 most distant points.
 *
 * In special case of circle (orbit with eccentricity of 0), the
 * semi-major axis is the radius.
 *
 * \see https://en.wikipedia.org/wiki/Semi-major_and_semi-minor_axes
 */
class SemiMajorAxis {
private:
  /**
   * @brief the semi-major axis [m]
   *
   */
  double value_;

public:
  /**
   * @brief returns the semi-major axis [m]
   *
   * @return double
   */
  operator double() const { return (value_); }

  /**
   * @brief dummy constructor.
   *
   */
  SemiMajorAxis() : value_(0){};

  /**
   * @brief sets SMA to the passed value
   *
   * @param sma length of semi-major axis [m]
   */
  SemiMajorAxis(double sma) : value_(sma) { assert(std::isfinite(sma)); };

  /**
   * @brief calculates length of semi-major axis from passed orbit's Ap and Pe.
   *
   * For circular orbit, the semi-major axis is the radius.
   *
   * Else, from the geometry of an ellipse, \f$2a=r_p+r_a\f$
   *
   * Thus, the semi-major axis is half the sum of radiuses at the orbit's 2
   * Apsis:
   * \f$a={{{r_a+r_p}}\over{2}}\f$
   *
   * According to herbie, it is the most precise version given the
   * expected input data range (error = 0.0 bits).
   * See math/orbit/sma-from-r1-and-r2.rkt
   *
   * @param ApR radius of the orbit, at the orbit's farthest point (apoapsis)
   * [m]
   * @param PeR radius of the orbit, at the orbit's nearest point (periapsis)
   * [m]
   */
  SemiMajorAxis(double ApR, double PeR) : value_(0) {
    assert(std::isfinite(ApR));
    assert(std::isfinite(PeR));

    value_ = (ApR + PeR) / 2.0;

    assert(std::isfinite(value_));
  };

  /**
   * @brief calculates length of semi-major axis from passed orbit's Ap and Pe.
   *
   * For circular orbit, the semi-major axis is the radius.
   *
   * Else, from the geometry of an ellipse, \f$2a=r_p+r_a\f$
   *
   * Thus, the semi-major axis is half the sum of radiuses at the orbit's 2
   * Apsis:
   * \f$a={{{r_a+r_p}}\over{2}}\f$
   *
   * According to herbie, it is the most precise version given the
   * expected input data range (error = 0.0 bits).
   * See math/orbit/sma-from-r1-and-r2.rkt
   *
   * @param ApA altitude, from the surface of the parent body, at the orbit's
   * farthest point (apoapsis) [m]
   * @param PeA altitude, from the surface of the parent body, at the orbit's
   * nearest point (periapsis) [m]
   * @param parentBody the parent body
   */
  SemiMajorAxis(double ApA, double PeA, CelestialBody *parentBody) : value_(0) {
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
  };

  /**
   * @brief calculates SMA from given velocity vector and altitude.
   *
   * By definition, given 2 velocity's components, \f$V_x\f$ and \f$V_y\f$,
   * the velocity magnitude is: \f$v = \sqrt{V_x^2+V_y^2}\f$.
   *
   * Vis-viva equation, orbital-energy-invariance law:
   * \f$v^2={\mu\left({2\over{r}}-{1\over{a}}\right)}\f$
   *
   * Where \f$\mu\f$ is the standard gravitational parameter,
   * \f$r\f$ is the distance between the orbiting bodies, and
   * \f$a\f$ is the length of the semi-major axis.
   *
   * From Vis-viva equation, we can find \f$a\f$:
   *
   * \f$v^2={\mu\left({2\over{r}}-{1\over{a}}\right)}\f$
   *
   * \f$v^2={{{2\mu}\over{r}}-{\mu\over{a}}}\f$
   *
   * \f${\mu\over{a}}={{{2\mu}\over{r}}-v^2}\f$
   *
   * \f${1\over{a}}={{2\over{r}}-{v^2\over{\mu}}}\f$
   *
   * \f$a={1\over{{2\over{r}}-{v^2\over{\mu}}}}\f$
   *
   * However, for the reasons of floating-point precision, we'll use
   * optimized version:
   * \f$a={r\over{2-{{V_x^2+V_y^2}\over{{\mu}\over{r}}}}}\f$.
   *
   * According to herbie, it is the most precise version given the
   * expected input data range (error = 0.0 bits).
   * See math/orbit/sma.rkt
   *
   * \see https://en.wikipedia.org/wiki/Orbital_speed
   * \see https://en.wikipedia.org/wiki/Vis-viva_equation
   * \see https://en.wikipedia.org/wiki/Orbital_mechanics#Velocity
   *
   * @param Vx horizontal velocity [m/s]
   * @param Vy vertical velocity [m/s]
   * @param altitude altitude, from the surface of the parent body [m]
   * @param parentBody the parent body
   */
  SemiMajorAxis(double Vx, double Vy, double altitude,
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
};
