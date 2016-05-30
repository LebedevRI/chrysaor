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

class CubicCurvePoint {
private:
  /**
  * @brief point position
  */
  double x;

  /**
  * @brief point value
  */
  double y;

  /**
  * @brief tangent out
  */
  double outTangent;

  /**
  * @brief tangent in
  */
  double inTangent;

public:
  // all getters return the x-coordinate of current point
  double operator()() const { return (this->x); };
  double operator*() const { return (this->x); };

  // converter returns the y-coordinate of current point
  operator double() const { return (this->y); }

  //
  // void operator=(const CubicCurvePoint & b) { this->x = b.x; this->y = b.y;
  // this->outTangent = b.outTangent; this->inTangent = b.inTangent; }

  // all comparison is key-based.

  bool operator==(const CubicCurvePoint &b) const { return (this->x == b.x); };
  bool operator<(const CubicCurvePoint &b) const { return (this->x < b.x); };

  bool operator!=(const CubicCurvePoint &b) const {
    return !(this->operator==(b));
  };
  bool operator>(const CubicCurvePoint &b) const {
    return !(this->operator<(b));
  };

  bool operator<=(const CubicCurvePoint &b) const {
    return !(this->operator>(b));
  };
  bool operator>=(const CubicCurvePoint &b) const {
    return !(this->operator<(b));
  };

  CubicCurvePoint(double x, double y, double outTangent, double inTangent)
      : x(x), y(y), outTangent(outTangent), inTangent(inTangent) {}
};
