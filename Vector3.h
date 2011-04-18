#pragma once

#include <cmath>

template< typename T > struct Matrix4;

//! 3D vector
template< typename T >
struct Vector3
{
  Vector3< T >();
  Vector3< T >( const Vector3 & );
  Vector3< T >( T x ,T y, T z );
  virtual ~Vector3< T >(){}
  
  template < typename T2 >
  operator Vector3< T2 > () const { return Vector3< T2 >( static_cast< T2 >( x ), static_cast< T2 >( y ), static_cast< T2 >( z ) ); }
  
  Vector3< T > operator + () const;
  Vector3< T > operator - () const;
  
  Vector3< T > operator + ( const Vector3< T > &v ) const;
  Vector3< T > operator - ( const Vector3< T > &v ) const;
  Vector3< T > operator * ( T s ) const;
  Vector3< T > operator / ( T s ) const;
  

  Vector3< T > &operator += ( const Vector3 & );
  Vector3< T > &operator -= ( const Vector3 & );
  Vector3< T > &operator *= ( T );
  Vector3< T > &operator /= ( T );
  
  bool operator == ( const Vector3< T >& ) const;
  bool operator != ( const Vector3< T >& ) const;
  
  // static function
  /*!
    @brief normalize vector
  */
  static Vector3< T > &normalize(Vector3< T > &v, const Vector3< T > &v0);
  /*!
    @brief calculate length
  */
  static T length(const Vector3< T > &v);
  /*!
    @brief calculate norm
  */
  static T norm(const Vector3< T > &v);
  /*!
    @brief calculate distance between vectors
  */
  static T distance(const Vector3< T > &v1, const Vector3< T > &v2);
  /*!
    @brief calculate inner product
  */
  static T dot(const Vector3 &v1, const Vector3< T > &v2);
  /*!
    @brief calculate outer product
  */
  static Vector3< T > &cross(Vector3< T > &v, const Vector3< T > &v1, const Vector3< T > &v2);
  /*!
    @brief transformation (homogeneous)
  */
  static Vector3< T >	&transform( Vector3< T > &v, const Vector3< T > &v0, const Matrix4< T > &m );
  /*!
    @brief transformation
  */
  static Vector3< T >	&transformNormal( Vector3< T > &v, const Vector3< T > &v0, const Matrix4< T > &m );
  /*!
    @brief calculate intersection between ray and triangle
  */
  static bool intersectTri( const Vector3< T > &v0, const Vector3< T > &v1, const Vector3< T > &v2, const Vector3< T > &org, const Vector3< T > &dir, T *u = 0, T *v = 0, T *dist = 0 );
  
  union
  {
    struct
    {
      T x, y, z;
    };
    T v[ 3 ];
  };
};

template< typename T >
inline Vector3< T >::Vector3()
{
  x = y = z = 0;
}

template< typename T >
inline Vector3< T >::Vector3( T x, T y, T z )
{
  this->x = x;
  this->y = y;
  this->z = z;
}

template< typename T >
inline Vector3< T >::Vector3( const Vector3 &v )
{
  x = v.x;
  y = v.y;
  z = v.z;
}


template< typename T >
inline Vector3< T > Vector3< T >::operator +() const
{
  return Vector3< T >( x, y, z );
}

template< typename T >
inline Vector3< T > Vector3< T >::operator -() const
{
  return Vector3< T >( -x, -y, -z );
}

template< typename T >
inline Vector3< T > Vector3< T >::operator +( const Vector3< T > &v ) const
{
  return Vector3< T >( x + v.x, y + v.y,z+ v. z);
}

template< typename T >
inline Vector3< T > Vector3< T >::operator -( const Vector3< T > &v ) const
{
  return Vector3< T >( x- v.x, y - v.y, z - v.z );
}

template< typename T >
inline Vector3< T > Vector3< T >::operator * (T s ) const
{
  return Vector3< T >( x * s, y * s, z * s );
}

template< typename T >
inline Vector3< T > Vector3< T >::operator /( T s ) const
{
  return Vector3< T >( x / s, y / s, z / s );
}

template< typename T >
inline Vector3< T > &Vector3< T >::operator +=( const Vector3< T > &v )
{
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

template< typename T >
inline Vector3< T > &Vector3< T >::operator -=( const Vector3< T > &v )
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

template< typename T >
inline Vector3< T > &Vector3< T >::operator *=( T s )
{
  x *= s;
  y *= s;
  z *= s;
  return *this;
}

template< typename T >
inline Vector3< T > &Vector3< T >::operator /=( T s )
{
  x /= s;
  y /= s;
  z /= s;
  return *this;
}

template< typename T >
inline bool Vector3< T >::operator ==( const Vector3< T > &v ) const
{
  return (x==v.x && y==v.y && z==v.z);
}

template< typename T >
inline bool Vector3< T >::operator !=( const Vector3< T > &v ) const
{
  return !operator==( v );
}

template< typename T >
inline T Vector3< T >::dot( const Vector3< T > &v1, const Vector3< T > &v2 )
{
  return ( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z );
}


template< typename T >
inline Vector3< T > &Vector3< T >::cross( Vector3< T > &v, const Vector3< T > &v1, const Vector3< T > &v2 )
{
	v = Vector3< T >(v1.y*v2.z - v1.z*v2.y ,v1.z*v2.x - v1.x*v2.z ,v1.x*v2.y - v1.y*v2.x);
	return v;
}

//!
template< typename T, typename T2 >
inline Vector3< T > operator * ( T2 s, const Vector3< T > &v )
{
	return Vector3< T >(v.x*s,v.y*s,v.z*s);
}

//
template< typename T >
inline Vector3< T > &Vector3< T >::normalize( Vector3< T > &v, const Vector3 &v0 )
{
  T l = length(v0);
  if(l == 0)
    {
      v = Vector3();
      return v;
    }
  
  v = v0 / l;
  return v;
}

//
template< typename T >
inline T Vector3< T >::length( const Vector3 &v )
{
  return sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}

//
template< typename T >
inline T Vector3< T >::norm( const Vector3 &v )
{
  return ( v.x * v.x + v.y * v.y + v.z * v.z );
}

//
template< typename T >
inline T Vector3< T >::distance( const Vector3 &v1, const Vector3 &v2 )
{
  Vector3< T > v = v1 - v2;
  return length( v );
}

//
template< typename T >
bool Vector3< T >::intersectTri( const Vector3< T > &v0, const Vector3< T > &v1, const Vector3< T > &v2, const Vector3< T > &org, const Vector3< T > &dir, T *u, T *v, T *dist )
{
  // 面の法線を求める
  Vector3< T > t1 = v1 - v0;
  Vector3< T > t2 = v2 - v0;
  Vector3< T > N;
  Vector3< T >::cross( N, t1, t2 );
  Vector3::normalize( N, N );
  
  Vector3< T > va = org - v0;
  T t = -Vector3< T >::dot(va,N) / Vector3< T >::dot( dir,N );
  
  Vector3< T > p = org + t * dir;


  Vector3< T > vp0 = v0 - p;
  Vector3< T > vp1 = v1 - p;
  Vector3< T > vp2 = v2 - p;

  Vector3< T > d1 = v1 - v0;
  Vector3< T > c;
  Vector3< T >::cross( c, vp0, d1 );
  double c0 = Vector3< T >::dot( c, N );
  
  d1 = v2 - v1;
  Vector3< T >::cross( c, vp1, d1 );
  double c1 = Vector3< T >::dot( c, N );

  d1 = v0 - v2;
  Vector3< T >::cross( c, vp2, d1 );
  double c2 = Vector3< T >::dot( c, N );

  if( c0 >= 0.0 && c1 >= 0.0 && c2 >= 0.0 )    
    {
      if( dist )
	{
	  *dist = t;
	}
      
      if(u && v)
	{
	  T l1 = Vector3< T >::norm( t1 );
	  T l2 = Vector3< T >::norm( t2 );
	  T c12 = Vector3< T >::dot( t1, t2 );
	  T S = static_cast< T >( sqrt( static_cast< double >( l1 * l2 - c12 * c12 ) ) ) / 2;
	  
	  T l2p = Vector3< T >::norm( vp2 );
	  T c2p = Vector3< T >::dot( vp2 , t2 );
	  T Su = static_cast< T >( sqrt( static_cast< double >( l2 * l2p - c2p * c2p ) ) ) / 2;
	  
	  T l1p = Vector3< T >::norm( vp1 );
	  T c1p = Vector3< T >::dot( vp1, t1 );
	  T Sv = static_cast< T >( sqrt( static_cast< double >( l1 * l1p - c1p * c1p ) ) ) / 2;
	  
	  
	  *u = Su / S;
	  *v = Sv / S;
	}

      return true;
    }
  return false;
}


#include "Matrix4.h"



template< typename T >
Vector3< T > &Vector3< T >::transform( Vector3< T > &v, const  Vector3< T > &v0, const Matrix4< T > &m )
{
  Vector3< T > t;
  t.x = v0.x * m._11 + v0.y * m._21 + v0.z * m._31 + m._41;
  t.y = v0.x * m._12 + v0.y * m._22 + v0.z * m._32 + m._42;
  t.z = v0.x * m._13 + v0.y * m._23 + v0.z * m._33 + m._43;
  T w = v0.x * m._14 + v0.y * m._24 + v0.z * m._34 + m._44;
  if( w == 0 )
    {
      return v;
    }
 
  t.x /= w;
  t.y /= w;
  t.z /= w;
  
  v = t;

  return v;
}


template< typename T >
Vector3< T > &Vector3< T >::transformNormal( Vector3< T > &v, const Vector3< T > &v0, const Matrix4< T > &m )
{
  Vector3< T > t;
  t.x = v0.x * m._11 + v0.y * m._21 + v0.z * m._31;
  t.y = v0.x * m._12 + v0.y * m._22 + v0.z * m._32;
  t.z = v0.x * m._13 + v0.y * m._23 + v0.z * m._33;
  T w = v0.x * m._14 + v0.y * m._24 + v0.z * m._34;
  if( w == 0 ) 
    {
      return v;
    }
  
  t.x /= w;
  t.y /= w;
  t.z /= w;
  
  v = t;
  
  return v;
}


/*!
  出力
*/
template< typename T > 
std::ostream &operator<<( std::ostream &os, const Vector3< T > &v )
{
  os << v.x << ", " << v.y << ", " << v.z;
  return os;
}

typedef Vector3< unsigned char > Vector3UC;
typedef Vector3< int > Vector3I;
typedef Vector3<float>	Vector3F;
typedef Vector3<double>	Vector3D;
