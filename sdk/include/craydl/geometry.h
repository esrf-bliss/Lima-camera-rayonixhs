//Some geometry classes for Rayonix
//Justin Anderson
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <algorithm>

namespace craydl {

//! A cartesian point class
template<typename T>
class Point {
   public:
      //! Default constructor, sets to zero
      Point() { x_ = 0; y_ = 0; }

      //! Constructor with given x, y values
      Point(const T& x, const T& y) { x_ = x; y_ = y; };

      //! Return x coordinate value
      /*! \return x coordinate value */
      T x() const { return x_; } 

      //! Return y coordinate value
      /*! \return y coordinate value */
      T y() const { return y_; } 

      //! moves x coordinate to x and returns orginal value of x
      T move_x_to( const T x) { T tmp = x_; x_ = x; return tmp; }

      //! moves y coordinate to y and returns orginal value of y
      T move_y_to( const T y) { T tmp = y_; y_ = y; return tmp; }

      //! moves point to coordinates x,y and returns original coordinates
      Point<T> move_to( const T x, const T y) { Point<T> tmp(move_x_to(x), move_y_to(y)); return tmp; }

      //! moves point to point p and returns original point
      Point<T> move_to( const Point<T> &p) { Point<T> tmp(move_x_to(p.x()), move_y_to(p.y())); return tmp; }

      double distance( const Point<T> &p ) const {
	 double dx = p.x() - x();	  
	 double dy = p.y() - y();	  
	 double x2 = pow(dx, 2.);
	 double y2 = pow(dy, 2.);

	 return sqrt(x2 + y2);
      }


   private:
      //! The internal storage of x value
      T x_;

      //! The internal storage of y value
      T y_;
};

//! A cartesian line class
template<typename T>
class Line {
   public:
      //! Default constructor, sets to zero
      Line() { p0_ = Point<T>(0, 0); p1_ = Point<T>(0, 0); }

      //! Constructor with given points defining the line
      /* \param p0 the first point describing the line
         \param p1 the second point describing the line */
      Line(const Point<T> &p0, const Point<T> &p1) { p0_ = p0; p1_ = p1; }

      //! Constructor with given point values defining the line
      /* \param x0 the x coordinate of the first point describing the line
         \param y0 the y coordinate of the first point describing the line
         \param x1 the x coordinate of the second point describing the line
         \param y1 the y coordinate of the second point describing the line */
      Line(const T x0, const T y0, const T x1, const T y1) { 
	 p0_ = Point<T>(x0, y0); 
	 p1_ = Point<T>(x1, y1); 
      }

      //! Returns the first point describing the line
      /*!  \return the first point describing the line */
      Point<T> p0() const { return p0_; } 

      //! Returns the second point describing the line
      /*!  \return the second point describing the line */
      Point<T> p1() const { return p1_; } 

      /*! \brief Return the x value of the first point describing the line
	  \return the x value of the first point describing the line */
      T x0() const { return p0_.x(); }
      
      /*! \brief Return the y value of the first point describing the line
	  \return the y value of the first point describing the line */
      T y0() const { return p0_.y(); }
      
      /*! \brief Return the x value of the second point describing the line
	  \return the x value of the second point describing the line */
      T x1() const { return p1_.x(); }
      
      /*! \brief Return the y value of the second point describing the line
	  \return the y value of the second point describing the line */
      T y1() const { return p1_.y(); }

      //! Return left-edge of bounding rectangle
      /*! \return Left-most distance */
      T left() const { return std::min(p0_.x(), p1_.x()); }
      
      //! Return right-edge of bounding rectangle
      /*! \return Right-most distance */
      T right() const { return std::max(p0_.x(), p1_.x()); }
      
      //! Return top-edge of bounding rectangle
      /*! \return Top-most distance */
      T top() const { return std::min(p0_.y(), p1_.y()); }
      
      //! Return bottom-edge of bounding rectangle
      /*! \return Bottom-most distance */
      T bottom() const { return std::max(p0_.y(), p1_.y()); }

      //! Return left-most point
      /*! \return Left-most point */
      Point<T> left_point() const { if (p0_.x() < p1_.x()) return p0_; else return p1_; }
      
      //! Return right-most point
      /*! \return Right-most point */
      Point<T> right_point() const { if (p1_.x() > p0_.x()) return p1_; else return p0_; }

      //! Return top-most point
      /*! \return Top-most point */
      Point<T> top_point() const { if (p0_.y() < p1_.y()) return p0_; else return p1_; }
      
      //! Return bottom-most point
      /*! \return Bottom-most point */
      Point<T> bottom_point() const { if (p1_.y() > p0_.y()) return p1_; else return p0_; }

      /*! \brief Return the length of the line
          \return The length of the line */
      double length() const {
	 double dx = std::abs(p1_.x() - p0_.x());
	 double dy = std::abs(p1_.y() - p0_.y());
	 
	 double dx2 = pow(dx, 2);
	 double dy2 = pow(dy, 2);

	 return (sqrt(dx2 + dy2));
      }

      //! moves line to coordinates p0,p1 and returns orginal coordinates
      Line<T> move_to(const Point<T> &p0, const Point<T> &p1) { Line<T> tmp(p0_.move_to(p0), p1_.move_to(p1)); return tmp; }

      //! moves line to line l and returns original line
      Line<T> move_to(const Line<T> &l) { Line<T> tmp(p0_.move_to(l.p0()), p1_.move_to(l.p1())); return tmp; }

      //! move left-most coordinates to p0 and right-most coordinates to p1
      //! return original Line
      Line<T> normalize() {
	 return move_to(left_point, right_point);
      }

      //! return a normalized copy of this Line without modifying the original object
      Line<T> normalized() const {
	 return Line<T>(left_point, right_point);
      }

   private:
      //! Internal storage of first point describing the line
      Point<T> p0_;

      //! Internal storage of second point describing the line
      Point<T> p1_;
   
};

//! A cartesian rectangle class
template<typename T>
class Rect {
   public:
      /*! \brief Default constructor, sets to zero */
      Rect() { p0_ = Point<T>(0, 0); p1_ = Point<T>(0, 0); }

      /*! \brief Constructor with given points describing the rectangle
          \param p0 the first point describing the rectangle
          \param p1 the second point describing the rectangle */
      Rect(const Point<T> &p0, const Point<T> &p1) { p0_ = p0; p1_ = p1; }

      /*! \brief Constructor with given values for points describing the rectangle
          \param x0 the x value of the first point describing the rectangle
          \param y0 the y value of the first point describing the rectangle
          \param x1 the x value of the second point describing the rectangle
          \param y1 the y value of the second point describing the rectangle */
      Rect(const T& x0, const T& y0, const T& x1, const T& y1) { 
	 p0_ = Point<T>(x0, y0);
	 p1_ = Point<T>(x1, y1);
      }

      /*! \brief Returns the first point describing the rectangle
          \return the first point describing the rectangle */
      Point<T> p0() const { return p0_; }

      /*! \brief Returns the second point describing the rectangle
          \return the second point describing the rectangle */
      Point<T> p1() const { return p1_; }

      /*! \brief Return the x value of the first point describing the rectangle 
	  \return the x value of the first point describing the rectangle */
      T x0() const { return p0_.x(); }
      
      /*! \brief Return the y value of the first point describing the rectangle 
	  \return the y value of the first point describing the rectangle */
      T y0() const { return p0_.y(); }
      
      /*! \brief Return the x value of the second point describing the rectangle 
	  \return the x value of the second point describing the rectangle */
      T x1() const { return p1_.x(); }
      
      /*! \brief Return the y value of the second point describing the rectangle 
	  \return the y value of the second point describing the rectangle */
      T y1() const { return p1_.y(); }
      
      /*! \brief Returns the width of the rectangle
          \return the width of the rectangle - as the difference between x1 and x0 */
      T width() const {
	 T dx = std::max<T>(p0_.x(), p1_.x()) - std::min<T>(p0_.x(), p1_.x());
	 return dx;
      }

      /*! \brief Returns the height of the rectangle
          \return the height of the rectangle - as the difference between y1 and y0 */
      T height() const {
	 T dy = std::max<T>(p0_.y(), p1_.y()) - std::min<T>(p0_.y(), p1_.y());
	 return dy;
      }

      /*! \brief Return the y value of the top of the rectangle
          \return the y value of the top of the rectangle */
      T top() const { return std::max(p0_.y(), p1_.y()); }
      
      /*! \brief Return the y value of the bottom of the rectangle
          \return the y value of the bottom of the rectangle */
      T bottom() const { return std::min(p0_.y(), p1_.y()); }
      
      /*! \brief Return the x value of the left side of the rectangle
          \return the x value of the left side of the rectangle */
      T left() const { return std::min(p0_.x(), p1_.x()); }
      
      /*! \brief Return the x value of the right side of the rectangle
          \return the x value of the right side of the rectangle */
      T right() const { return std::max(p0_.x(), p1_.x()); }

      /*! \brief Return the top left coordinate of the rectangle
          \return the top left coordinate of the rectangle */
      Point<T> topleft() const { return Point<T>(left(), top()); }
      
      /*! \brief Return the top right coordinate of the rectangle
          \return the top right coordinate of the rectangle */
      Point<T> topright() const { return Point<T>(right(), top()); }
      
      /*! \brief Return the bottom left coordinate of the rectangle
          \return the bottom left coordinate of the rectangle */
      Point<T> bottomleft() const { return Point<T>(left(), bottom()); }
      
      /*! \brief Return the bottom right coordinate of the rectangle
          \return the bottom right coordinate of the rectangle */
      Point<T> bottomright() const { return Point<T>(right(), bottom()); }

      /*! \brief Return the area of the rectangle
          \return The area of the rectangle, i.e. w x h */
      T area() const {
	 return width() * height();
      }

      //! moves rect to coordinates p0,p1 and returns orginal coordinates
      Rect<T> move_to(const Point<T> &p0, const Point<T> &p1) { Rect<T> tmp(p0_.move_to(p0), p1_.move_to(p1)); return tmp; }

      //! moves rect to rect r and returns original rect
      Rect<T> move_to(const Rect<T> &r) { Rect<T> tmp(p0_.move_to(r.p0()), p1_.move_to(r.p1())); return tmp; }

      //! move lower coordinates to p0 and higher coordinates to p1
      //! return original Rect
      Rect<T> normalize()
      { 
	 //if (p0_.x() > p1_.x()) { p1_.move_x_to(p0_.move_x_to(p1_.x())); }
	 //if (p0_.y() > p1_.y()) { p1_.move_y_to(p0_.move_y_to(p1_.y())); }
         return move_to(bottomleft(), topright());
      }

      //! return a normalized copy of this Rect without modifying the original object
      Rect<T> normalized() const
      { 
	 Rect<T> TRect = *this;
	 TRect.normalize();
	 return TRect;
      }

   private:
      //! Internal storage of first point describing the rectangle
      Point<T> p0_;

      //! Internal storage of second point describing the rectangle
      Point<T> p1_;
};

}

#endif
