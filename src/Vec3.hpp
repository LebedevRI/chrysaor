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

#include <cmath>
#include <iostream>

class Vec3 {
public:
  double x_;
  double y_;
  double z_;

  bool operator==(Vec3 rhs) const {
    return (x_ == rhs.x_ && y_ == rhs.y_ && z_ == rhs.z_);
  }

  Vec3 operator+(Vec3 rhs) const {
    return Vec3(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
  }
  Vec3 operator+=(Vec3 rhs) {
    *this = *this + rhs;
    return *this;
  }

  Vec3 operator-(Vec3 rhs) const {
    return Vec3(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_);
  }
  Vec3 operator-=(Vec3 rhs) {
    *this = *this - rhs;
    return *this;
  }

  Vec3 operator*(Vec3 rhs) const {
    return Vec3(x_ * rhs.x_, y_ * rhs.y_, z_ * rhs.z_);
  }
  Vec3 operator*=(Vec3 rhs) {
    *this = *this * rhs;
    return *this;
  }

  Vec3 operator/(Vec3 rhs) const {
    return Vec3(x_ / rhs.x_, y_ / rhs.y_, z_ / rhs.z_);
  }
  Vec3 operator/=(Vec3 rhs) {
    *this = *this / rhs;
    return *this;
  }

  Vec3 operator+(double scalar) const {
    return Vec3(x_ + scalar, y_ + scalar, z_ + scalar);
  }
  Vec3 operator+=(double scalar) {
    *this = *this + scalar;
    return *this;
  }

  Vec3 operator-(double scalar) const {
    return Vec3(x_ - scalar, y_ - scalar, z_ - scalar);
  }
  Vec3 operator-=(double scalar) {
    *this = *this - scalar;
    return *this;
  }

  Vec3 operator*(double scalar) const {
    return Vec3(x_ * scalar, y_ * scalar, z_ * scalar);
  }
  Vec3 operator*=(double scalar) {
    *this = *this * scalar;
    return *this;
  }

  Vec3 operator/(double scalar) const {
    return Vec3(x_ / scalar, y_ / scalar, z_ / scalar);
  }
  Vec3 operator/=(double scalar) {
    *this = *this / scalar;
    return *this;
  }

  /**
   * @brief euclidean norm, L^2-Norm
   *
   * @return double
   */
  double norm() const { return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_); }

  /**
   * @brief dot product
   *
   * @return double
   */
  double dot(Vec3 rhs) const {
    return (x_ * rhs.x_ + y_ * rhs.y_ + z_ * rhs.z_);
  }

  Vec3 cross(Vec3 rhs) const {
    return Vec3(y_ * rhs.z_ - z_ * rhs.y_, z_ * rhs.x_ - x_ * rhs.z_,
                x_ * rhs.y_ - y_ * rhs.x_);
  }

  Vec3() : x_(0.0), y_(0.0), z_(0.0) {}
  Vec3(double x, double y, double z) : x_(x), y_(y), z_(z) {}
  Vec3(double (&v)[3]) : x_(v[0]), y_(v[1]), z_(v[2]) {}
};

std::ostream &operator<<(::std::ostream &os, const Vec3 &bar);
