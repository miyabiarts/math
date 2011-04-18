#pragma once

#include <cmath>

template< typename T > struct Vector3;
template< typename T > struct Vector4;

//! Plane
template< typename T = double >
struct Plane
{
  Plane< T >();
  Plane< T >( T a, T b, T c, T d );
  Plane< T >( const Plane< T > &plane );
  

  template< typename T2 >
  operator Plane< T2 > () const { return Plane< T2 >(static_cast< T2 >( a ), static_cast< T2 >( b ), static_cast< T2 >( c ), static_cast< T2 >( d ) ); }

  
  Plane< T > &operator *=(T);
  Plane< T > &operator /=(T);
  
  Plane< T > operator +() const;
  Plane< T > operator -() const;
  Plane< T > operator *( T s ) const;
  Plane< T > operator /( T s ) const;
  
  bool operator ==( const Plane< T > &p ) const;
  bool operator !=( const Plane< T > &p ) const;
  
  // static function
  /*!
    @brief create plane from 3 points
  */
  static void createFromPoints( Plane< T > &out, const Vector3< T > *v );
  /*!
    @brief create plane from point and normal vector
  */
  static void createFromPointNormal( Plane< T > &out, const Vector3< T > &v, const Vector3< T > &normal );
  /*!
    @brief calculate intersection between ray and plane
  */
  static bool intersectLine( Vector3< T > &pos, const Plane< T > &plane, const Vector3< T > &start, const Vector3< T > &dir, T *dist = 0 );
  /*!
    @brief calucalate inner product
  */
  static T dot( const Plane< T > &plane, const Vector4< T > &v );
  /*!
    @brief calucalate inner product
  */
  static T dot( const Plane< T > &plane, const Vector3< T > &v );
  /*!
    @brief calucalate inner product
  */
  static T dotNormal( const Plane< T > &plane, const Vector3< T > &v );
  
  union
  {
    struct
    {
      T a, b, c, d;
    };
    T v[ 4 ];
  };
};

//
template< typename T >
inline Plane< T >::Plane()
{
  this->a = 0;
  this->b = 0;
  this->c = 0;
  this->d = 1;
}

//
template< typename T >
inline Plane< T >::Plane( T a, T b, T c, T d )
{
  this->a = a;
  this->b = b;
  this->c = c;
  this->d = d;
}

//
template< typename T >
inline Plane< T >::Plane( const Plane< T > &p )
{
  this->a = p.a;
  this->b = p.b;
  this->c = p.c;
  this->d = p.d;
}

//
template< typename T >
inline Plane< T > &Plane< T >::operator *=( T s )
{
  a *= s;
  b *= s;
  c *= s;
  d *= s;
  return *this;
}

//
template< typename T >
inline Plane< T > &Plane< T >::operator /=( T s )
{
  T f = 1.0 / s;
  return operator *=( f );
}

//
template< typename T >
inline Plane< T > Plane< T >::operator +() const
{
  return Plane< T >( a, b, c , d );
}

//
template< typename T >
inline Plane< T > Plane< T >::operator -() const
{
  return Plane< T >( -a, -b, -c, -d );
}

//
template< typename T >
inline Plane< T > Plane< T >::operator *( T s ) const
{
  return Plane< T >( a * s, a * b, a * c, a * d );
}

//
template< typename T >
inline Plane< T > Plane< T >::operator /(T s) const
{
  T f = 1.0 / s;
  return operator *( f );
}

//
template< typename T, typename T2 >
inline Plane< T > operator *( T2 s, const Plane< T > &p )
{
  return Plane< T >( p.a * s, p.b * s, p.c * s, p.d * s );
}

//
template< typename T >
inline bool Plane< T >::operator ==( const Plane< T > &p ) const
{
  return ( a==p.a && b==p.b && c==p.c && d==p.d );
}

//
template< typename T >
inline bool Plane< T >::operator !=( const Plane< T > &p ) const
{
  return !operator ==( p );
}

#include "Vector3.h"


//
template< typename T >
void Plane< T >::createFromPoints( Plane< T > &out, const Vector3< T > *v )
{
  Vector3< T > v1 = v[ 1 ] - v[ 0 ];
  Vector3< T > v2 = v[ 2 ] - v[ 0 ];
  Vector3< T > axis;
  Vector3< T >::cross( axis, v1, v2 );
  Vector3< T >::normalize( axis, axis );
  
  createFromPointNormal( out, v[ 0 ], axis );
}

//
template< typename T >
void Plane< T >::createFromPointNormal( Plane< T > &out, const Vector3< T > &v, const Vector3< T > &normal )
{
  T d = -( normal.x * v.x + normal.y * v.y + normal.z * v.z );
  
  out = Plane< T >( normal.x, normal.y, normal.z, d );
}

//
template< typename T >
bool Plane< T >::intersectLine( Vector3< T > &pos, const Plane< T > &plane, const Vector3< T > &org, const Vector3< T > &dir, T *dist )
{
  Vector3< T > N( plane.a, plane.b, plane.c );
  
  T c = Vector3< T >::dot( N, dir );
  if( c == 0 )
    {
      return false;
    }
 
  T t = -( Vector3< T >::dot( N, org ) + plane.d ) / c;
  
  pos = org + dir * t;
  
  if( dist )
    {
      *dist = t;
    }
  
  return true;
}

//
template< typename T >
T Plane< T >::dot( const Plane< T > &plane, const Vector4< T > &v )
{
  return plane.a*v.x + plane.b*v.y + plane.c*v.z + plane.d * v.w;
}

//
template< typename T >
T Plane< T >::dot( const Plane< T > &plane, const Vector3< T > &v )
{
  return plane.a * v.x + plane.b * v.y + plane.c * v.z + plane.d;
}

//
template< typename T >
T Plane< T >::dotNormal( const Plane< T > &plane, const Vector3< T > &v )
{
  return plane.a * v.x + plane.b * v.y + plane.c * v.z;
}

/*!
  output stream
*/
template< typename T > 
std::ostream &operator<<( std::ostream &os, const Plane< T > &p )
{
  os << p.a << ", " << p.b << ", " << p.c << ", " << p.d;
  return os;
}

typedef Plane< unsigned char > PlaneUC;
typedef Plane< int > PlaneI;
typedef Plane< float > PlaneF;
typedef Plane< double > PlaneD;
