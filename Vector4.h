#pragma once

#include <cmath>

template< typename T > struct Matrix4;

//! 4D vector
template< typename T = double >
struct Vector4
{
  Vector4< T >();
  Vector4< T >( const Vector4< T > & );
  Vector4< T >( T x, T y, T z, T w );
  

  template < typename T2 >
  operator Vector4< T2 > () const { return Vector4< T2 >( static_cast< T2 >( x ), static_cast< T2 >( y ), static_cast< T2 >( z ), static_cast< T2 >( w ) ); }
  
  Vector4< T > operator + () const;
  Vector4< T > operator - () const;
  
  Vector4< T > operator + ( const Vector4< T > &v ) const;
  Vector4< T > operator - ( const Vector4< T > &v ) const;
  Vector4< T > operator * ( T s ) const;
  Vector4< T > operator / ( T s ) const;
  
  
  Vector4< T > &operator += ( const Vector4< T > &);
  Vector4< T > &operator -= ( const Vector4< T > &);
  Vector4< T > &operator *= ( T );
  Vector4< T > &operator /= ( T );
  
  bool operator == ( const Vector4< T >& ) const;
  bool operator != ( const Vector4< T >& ) const;
  
  // static function
  /*!
    @brief normalize vector    
  */
  static Vector4< T > &normalize( Vector4< T > &v, const Vector4< T > &v0 );
  /*!
    @brief calculate length
  */
  static T length( const Vector4< T > &v );
  /*!
    @brief calculate norm
  */
  static T norm( const Vector4< T > &v );
  /*!
    @brief calculate distance between vectors
  */
  static T distance( const Vector4< T > &v1, const Vector4< T > &v2 );
  /*!
    @brief calucalate inner product
  */
  static T dot( const Vector4< T > &v1, const Vector4< T > &v2 );
  /*!
    @brief transformation
  */
  static void transform( Vector4< T > &o, const Vector4< T > &v, const Matrix4< T > &m );
  
  union
  {
    struct
    {
      T x, y, z, w;
    };
    T v[ 4 ];
  };
};

//
template< typename T >
inline Vector4< T >::Vector4()
{
  x = y = z = w = 0;
}

//
template< typename T >
inline Vector4< T >::Vector4( T x, T y, T z, T w )
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

//
template< typename T >
inline Vector4< T >::Vector4( const Vector4< T > &v )
{
  x = v.x;
  y = v.y;
  z = v.z;
  w = v.w;
}

//
template< typename T >
inline Vector4< T > Vector4< T >::operator +() const
{
  return Vector4< T >( x, y, z, w );
}

//
template< typename T >
inline Vector4< T > Vector4< T >::operator -() const
{
  return Vector4< T >( -x, -y, -z, -w );
}

//
template< typename T >
inline Vector4< T > Vector4< T >::operator +( const Vector4< T > &v ) const
{
  return Vector4< T >( x + v.x, y + v.y, z + v.z, w + v.w );
}

//
template< typename T >
inline Vector4< T > Vector4< T >::operator -( const Vector4< T > &v ) const
{
  return Vector4< T >( x - v.x, y - v.y, z - v.z, w- v.w );
}

//
template< typename T >
inline Vector4< T > Vector4< T >::operator *( T s ) const
{
  return Vector4< T >( x * s, y * s, z * s, w * s );
}

//
template< typename T, typename T2 >
inline Vector4< T > operator *( T2 s, const Vector4< T > &v )
{
  return Vector4< T >( v.x * s, v.y * s, v.z * s, v.w * s );
}

//
template< typename T >
inline Vector4< T > Vector4< T >::operator /(T s) const
{
  return Vector4< T >( x / s, y / s, z / s,w / s );
}

//
template< typename T >
inline Vector4< T > &Vector4< T >::operator +=( const Vector4< T > &v )
{
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;
  return *this;
}

//
template< typename T >
inline Vector4< T > &Vector4< T >::operator -=( const Vector4< T > &v )
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;
  return *this;
}

//
template< typename T >
inline Vector4< T > &Vector4< T >::operator *=( T s )
{
  x *= s;
  y *= s;
  z *= s;
  w *= s;
  return *this;
}

//
template< typename T >
inline Vector4< T > &Vector4< T >::operator /=( T s )
{
  x /= s;
  y /= s;
  z /= s;
  w /= s;
  return *this;
}

//
template< typename T >
inline bool Vector4< T >::operator ==( const Vector4< T > &v ) const
{
  return ( x==v.x && y==v.y && z==v.z && w==v.w );
}

//
template< typename T >
inline bool Vector4< T >::operator !=( const Vector4< T > &v ) const
{
  return !operator==( v );
}

//
template< typename T >
inline Vector4< T > &Vector4< T >::normalize( Vector4< T > &v, const Vector4< T > &v0 )
{
  T l = length( v0 );
  if(l == 0)
    {
      v = Vector4< T >();
      return v;
    }
  
  *v = *v0 / l;
  
  return v;
}

//
template< typename T >
inline T Vector4< T >::length(const Vector4< T > &v)
{
  return sqrt( v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w );
}

//
template< typename T >
inline T Vector4< T >::norm( const Vector4< T > &v )
{
  return ( v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w );
}

//
template< typename T >
inline T Vector4< T >::distance( const Vector4< T > &v1, const Vector4< T > &v2 )
{
  Vector4< T > v = v1 - v2;
  return length( v );
}

//
template< typename T >
inline T Vector4< T >::dot( const Vector4< T > &v1, const Vector4< T > &v2 )
{
  return ( v1.x * v2.x  +v1.y * v2.y + v1.z * v2.z + v1.w * v2.w );
}


#include "Matrix4.h"
//
template< typename T >
void Vector4< T >::transform( Vector4< T > &o, const Vector4< T > &v,const Matrix4< T > &m )
{
  Vector4< T > t;
  t.x = v.x * m._11 + v.y * m._21 + v.z * m._31 + v.w * m._41;
  t.y = v.x * m._12 + v.y * m._22 + v.z * m._32 + v.w * m._42;
  t.z = v.x * m._13 + v.y * m._23 + v.z * m._33 + v.w * m._43;
  t.w = v.x * m._14 + v.y * m._24 + v.z * m._34 + v.w * m._44;
  o = t;
}

/*!
  output stream
*/
template< typename T > 
std::ostream &operator<<( std::ostream &os, const Vector4< T > &v )
{
  os << v.x << ", " << v.y << ", " << v.z << ", " << v.w;
  return os;
}

typedef Vector4< unsigned char > Vector4UC;
typedef Vector4< int > Vector4I;
typedef Vector4<float>	Vector4F;
typedef	Vector4<double>	Vector4D;
