#pragma once

#include <cmath>

template< typename T > struct Vector3;
template< typename T > struct Matrix4;

//! Quaternion
template <typename T = double>
struct Quaternion
{
  Quaternion< T >();
  Quaternion< T >( T x,T y,T z,T w );
  Quaternion< T >( const Quaternion< T > &q );
  
  Quaternion< T > &operator =( const Quaternion< T > &q );
  
  Quaternion< T >  operator +() const;
  Quaternion< T >  operator -() const;
  
  Quaternion< T > operator +( const Quaternion< T > &q ) const;
  Quaternion< T > operator -( const Quaternion< T > &q ) const;
  Quaternion< T > operator *( const Quaternion< T > &q ) const;
  Quaternion< T > operator *( T s ) const;
  Quaternion< T > operator /( T s ) const;
  
  Quaternion< T >& operator +=( const Quaternion< T > &q );
  Quaternion< T >& operator -=( const Quaternion< T > &q );
  Quaternion< T >& operator *=( const Quaternion< T > &q );
  Quaternion< T >& operator *=( T s );
  Quaternion< T >& operator /=( T s );
  
  bool operator ==( const Quaternion< T > &q ) const;
  bool operator !=( const Quaternion< T > &q ) const;
  
  // static function
  /*!
    @brief create identity quaternion
  */
  static void identity( Quaternion< T > &q );
  /*!
    @brief normalize quoternion
  */
  static Quaternion< T > &normalize( Quaternion< T > &q, const Quaternion< T > &q0 );
  /*!
    @brief calculate length
  */
  static T	length( const Quaternion< T > &q );
  /*!
    @brief calculate norm
  */
  static T	norm( const Quaternion< T > &q );
  /*!
    @brief calculate conjugate quoternion
  */
  static Quaternion< T >	&conjugate( Quaternion< T > &q, const Quaternion< T > &q0 );
  /*!
    @brief calculate inverse quoternion
  */
  static Quaternion< T >	&inverse( Quaternion< T > &q, const Quaternion< T > &q0 );
  /*!
    @brief create yaw-pitch-roll rotation
  */
  static Quaternion< T >	&rotation( Quaternion< T > &q, T yaw, T pitch, T roll );
  /*!
    @brief create any-axis rotation
  */
  static Quaternion< T >	&rotationAxis( Quaternion< T > &q, const Vector3< T > &axis, T rad );
  /*!
    @brief convert to matrix
  */
  static Matrix4< T >		&toMatrix( Matrix4< T > &m, const Quaternion< T > &q );
  /*!
    @brief linear interpolation
  */
  template< typename T2 >
  static Quaternion< T > slerp( Quaternion< T > &q, const Quaternion< T > &q1, const Quaternion< T > &q2, T2 t );
   

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
inline Quaternion< T >::Quaternion()
{
  x = y = z = 0;
  w = 1;
}

//
template< typename T >
inline Quaternion< T >::Quaternion( T x, T y, T z, T w )
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

//
template< typename T >
inline Quaternion< T >::Quaternion( const Quaternion< T > &q )
{
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;
}


//
template< typename T >
inline Quaternion< T > &Quaternion< T >::operator =( const Quaternion< T > &q )
{
  if( this == &q ) return *this;
  
  x = q.x;
  y = q.y;
  z = q.z;
  w = q.w;
  
  return *this;
}

//
template< typename T >
inline Quaternion< T > Quaternion< T >::operator +() const
{
  return Quaternion< T >( x, y, z, w );
}

//
template< typename T >
inline Quaternion< T >  Quaternion< T >::operator -() const
{
  return Quaternion< T >( -x, -y, -z, -w );
}

//
template< typename T >
inline Quaternion< T > Quaternion< T >::operator +( const Quaternion< T > &q ) const
{
  return Quaternion< T >( x + q.x, y + q.y, z + q.z, w + q.w );
}

//
template< typename T >
inline Quaternion< T > Quaternion< T >::operator -( const Quaternion< T > &q ) const
{
  return Quaternion< T >( x - q.x, y - q.y, z - q.z, w - q.w );
}

//
template< typename T >
inline Quaternion< T > Quaternion< T >::operator *( const Quaternion< T > &q ) const
{
  Quaternion< T > t;
  
  t.x = -( y * q.z - z * q.y) + w * q.x + x * q.w;
  t.y = -( z * q.x - x * q.z) + w * q.y + y * q.w;
  t.z = -( x * q.y - y * q.x) + w * q.z + z * q.w;
  t.w = w * q.w - x * q.x - y * q.y - z * q.z;
  
  return t;
}

//
template< typename T >
inline Quaternion< T > Quaternion< T >::operator *( T s ) const
{
  return Quaternion< T >( x * s, y * s, z * s, w * s );
}

//
template< typename T >
inline Quaternion< T > Quaternion< T >::operator /( T s ) const
{
  T f = 1.0 / s;
  return operator *( f );
}

//
template< typename T >
inline Quaternion< T > operator *( T s, const Quaternion< T > &q )
{
	return Quaternion< T >( q.x * s, q.y * s, q.z * s, q.w * s );
}

//
template< typename T >
inline Quaternion< T > &Quaternion< T >::operator +=( const Quaternion< T > &q )
{
  x += q.x;
  y += q.y;
  z += q.z;
  w += q.w;
  
  return *this;
}

//
template< typename T >
inline Quaternion< T > &Quaternion< T >::operator -=( const Quaternion< T > &q )
{
  x -= q.x;
  y -= q.y;
  z -= q.z;
  w -= q.w;
  
  return *this;
}

//
template< typename T >
inline Quaternion< T > &Quaternion< T >::operator *=( const Quaternion< T > &q )
{
  Quaternion< T > t;
  t.x = -( y * q.z - z * q.y) + w * q.x + x * q.w;
  t.y = -( z * q.x - x * q.z) + w * q.y + y * q.w;
  t.z = -( x * q.y - y * q.x) + w * q.z + z * q.w;
  t.w = w * q.w - x * q.x - y * q.y - z * q.z;
  
  *this = t;
  
  return *this;	
}

//
template< typename T >
inline Quaternion< T > &Quaternion< T >::operator *=( T s )
{
  x *= s;
  y *= s;
  z *= s;
  w *= s;
  
  return *this;
}

//
template< typename T >
inline Quaternion< T > &Quaternion< T >::operator /=(T s)
{
  T f = 1.0f/s;
  return operator*=(f);
}

//
template< typename T >
inline bool Quaternion< T >::operator ==( const Quaternion< T > &q ) const
{
  return ( x==q.x && y==q.y && z==q.z && w == q.w );
}

//
template< typename T >
inline bool Quaternion< T >::operator !=( const Quaternion< T > &q ) const
{
  return !( operator==( q ) );
}

//
template< typename T >
inline void Quaternion< T >::identity( Quaternion< T > &q )
{
  q.x = q.y = q.z = 0;
  q.w = 1;
}

//
template< typename T >
inline Quaternion< T > &Quaternion< T >::normalize( Quaternion< T > &q, const Quaternion< T > &q0 )
{
  T l = length( q0 );
  if( l == 0.0 )
    {
      q = Quaternion< T >();
      return q;
    }
  
  q = q0 / l;
  
  return q;
}

//
template< typename T >
inline T Quaternion< T >::length( const Quaternion< T > &q )
{
  return sqrt( q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w );
}

//
template< typename T >
inline T Quaternion< T >::norm( const Quaternion< T > &q )
{
  return q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
}

#include "Matrix4.h"


template< typename T >
Quaternion< T > &Quaternion< T >::conjugate( Quaternion< T > &q, const Quaternion< T > &q0 )
{
  q = Quaternion< T >( -q0.x, -q0.y, -q0.z, q0.w );
  return q;
}

template< typename T >
Quaternion< T > &Quaternion< T >::inverse( Quaternion< T > &q, const Quaternion< T > &q0 )
{
  T l = length( q0 );
  if( l == 0 )
    {
      q = Quaternion< T >();
      return q;
    }
  
  conjugate( q, q0 );
  q /= l;
  return q;
}

template< typename T >
Quaternion< T > &Quaternion< T >::rotation( Quaternion< T > &q, T yaw, T pitch, T roll )
{
  Quaternion< T > qy,qp,qr;
  Matrix4< T > mrx,mry,mrz;
  
  rotationAxis(qp,Vector3< T >( 1, 0, 0 ), pitch );
  rotationAxis(qy,Vector3< T >( 0, 1, 0 ), yaw );
  rotationAxis(qr,Vector3< T >( 0, 0, 1 ), roll );
  
  q = qr * qp * qy;
  
  return q;
}

template< typename T >
Quaternion< T > &Quaternion< T >::rotationAxis( Quaternion< T > &q, const Vector3< T > &axis, T rad )
{
  T a = static_cast< T >( sin( static_cast< double >( rad ) / 2.0 ) );
  q.x = axis.x * a;
  q.y = axis.y * a;
  q.z = axis.z * a;
  q.w = static_cast< T >( cos( static_cast< double >( rad ) / 2 ) );
  
  normalize( q, q );
  
  return q;
}

template< typename T >
Matrix4< T > &Quaternion< T >::toMatrix( Matrix4< T > &m, const Quaternion< T > &q )
{
  m._11 = 1 - 2 * ( q.y * q.y + q.z * q.z );
  m._12 = 2 * ( q.x * q.y + q.z * q.w );
  m._13 = 2 * ( q.z * q.x - q.w * q.y );
  m._14 = 0;
  
  m._21 = 2 * ( q.x * q.y - q.z * q.w );
  m._22 = 1 - 2 * ( q.z * q.z + q.x * q.x );
  m._23 = 2 * ( q.y * q.z + q.w * q.x );
  m._24 = 0;
  
  m._31 = 2 * ( q.z * q.x + q.w * q.y );
  m._32 = 2 * ( q.y * q.z - q.x * q.w );
  m._33 = 1 - 2 * ( q.y * q.y + q.x * q.x );
  m._34 = 0;
  
  m._41 = m._42 = m._43 = 0;
  m._44 = 1;
  
  return m;
}

template< typename T, typename T2 >
static Quaternion< T > slerp( Quaternion< T > &q, const Quaternion< T > &q1, const Quaternion< T > &q2, T2 t )
{
  double a = static_cast< double >( q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w );
  double b = 1.0 - a * a;
  if( b == 0.0 )
    {
      q = q1;
    }
  else
    {
      double a2 = acos( a );
      double b2 = sqrt( b );
      double c = a2 * t;

      double t0 = sin( a2 - c ) / b2;
      double t1 = sin( c ) / b2;

      q = q1 * t0 + q2 * t1;
    }

  return q;
}

/*!
  output stream
*/
template< typename T > 
std::ostream &operator<<( std::ostream &os, const Quaternion< T > &q )
{
  os << q.x << ", " << q.y << ", " << q.z << ", " << q.w;
  return os;
}

typedef Quaternion< unsigned char >	QuaternionUC;
typedef Quaternion< int >	QuaternionI;
typedef Quaternion< float >	QuaternionF;
typedef Quaternion< double >	QuaternionD;
