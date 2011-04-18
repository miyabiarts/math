#pragma once

#include <cmath>

//! 2D vector
template < typename T = double >
struct Vector2
{
  Vector2< T >();
  Vector2< T >( const Vector2< T > & );
  Vector2< T >( T x, T y );

  template < typename T2 >
  operator Vector2< T2 > () const { return Vector2< T2 >( static_cast< T2 >( x ), static_cast< T2 >( y ) ); }
  
  
  Vector2< T > operator + () const;
  Vector2< T > operator - () const;
  
  Vector2< T > operator + ( const Vector2< T > &v ) const;
  Vector2< T > operator - ( const Vector2< T > &v ) const;
  Vector2< T > operator * ( T s ) const;
  Vector2< T > operator / ( T s ) const;
    
  Vector2< T > &operator += ( const Vector2< T > &);
  Vector2< T > &operator -= ( const Vector2< T > &);
  Vector2< T > &operator *= ( T );
  Vector2< T > &operator /= ( T );
  
  bool operator == ( const Vector2< T >& ) const;
  bool operator != ( const Vector2< T >& ) const;
  
  // static function
  /*!
    @brief normalize vector
  */
  static Vector2< T > &normalize( Vector2< T > &v,const Vector2< T > &v0 );
  /*!
    @brief calculate length
  */
  static T length( const Vector2< T > &v );
  /*!
    @brief calculate norm
  */
  static T norm( const Vector2< T > &v );
  /*!
    @brief calculate distance between vectors
  */
  static T distance( const Vector2< T > &v1, const Vector2< T > &v2 );
  /*!
    @brief calucalate inner product
  */
  static T dot( const Vector2< T > &v1,const Vector2< T > &v2 );
  /*!
    @brief calucalate outer product
  */
  static T ccw( const Vector2< T > &v1, const Vector2< T > &v2 );
  
  union
  {
    struct
    {
      T x, y;
    };
    T v[ 2 ];
  };
};

//
template< typename T >
inline Vector2< T >::Vector2()
{
  x = y = 0;
}

//
template< typename T >
inline Vector2< T >::Vector2( T x, T y )
{
  this->x = x;
  this->y = y;
}

//
template< typename T >
inline Vector2< T >::Vector2( const Vector2< T > &v )
{
  x = v.x;
  y = v.y;
}

//
template< typename T >
inline Vector2< T > Vector2< T >::operator +() const
{
  return Vector2< T >( x, y );
}

//
template< typename T >
inline Vector2< T > Vector2< T >::operator -() const
{
  return Vector2< T >( -x, -y );
}

//
template< typename T >
inline Vector2< T > Vector2< T >::operator +( const Vector2< T > &v ) const
{
  return Vector2< T >( x + v.x,y + v.y );
}

//
template< typename T >
inline Vector2< T > Vector2< T >::operator -( const Vector2< T > &v ) const
{
  return Vector2< T >( x - v.x, y - v.y );
}

//
template< typename T >
inline Vector2< T > Vector2< T >::operator *( T s ) const
{
  return Vector2< T >(x*s,y*s);
}

//
template< typename T >
inline Vector2< T > Vector2< T >::operator /( T s ) const
{
  return Vector2< T >( x / s, y / s );
}

//
template< typename T >
inline Vector2< T > &Vector2< T >::operator +=( const Vector2< T > &v )
{
  x += v.x;
  y += v.y;
  return *this;
}

//
template< typename T >
inline Vector2< T > &Vector2< T >::operator -=( const Vector2< T > &v )
{
  x -= v.x;
  y -= v.y;
  return *this;
}

//
template< typename T >
inline Vector2< T > &Vector2< T >::operator *=( T s )
{
  x *= s;
  y *= s;
  return *this;
}

//
template< typename T >
inline Vector2< T > &Vector2< T >::operator /=(T s)
{
  x /= s;
  y /= s;
  return *this;
}

//
template< typename T >
inline bool Vector2< T >::operator ==( const Vector2< T > &v ) const
{
  return ( x == v.x && y == v.y );
}

//
template< typename T >
inline bool Vector2< T >::operator !=(const Vector2< T > &v) const
{
  return !operator==(v);
}

//
template< typename T, typename T2 >
inline Vector2< T > operator * ( T2 s, const Vector2< T > &v )
{
  return Vector2< T >( v.x * s, v.y * s );
}

//
template< typename T >
inline Vector2< T > &Vector2< T >::normalize( Vector2< T > &v, const Vector2< T > &v0 )
{
  T l = length( v0 );
  if( l == 0.0 )
    {
      v = Vector2< T >();
      return v;
    }
  
  v = v0 / l;
  
  return v;
}

//
template< typename T >
inline T Vector2< T >::length( const Vector2< T > &v )
{
  return static_cast< T >( sqrt( static_cast< double >( v.x * v.x + v.y * v.y ) ) );
}

//
template< typename T >
inline T Vector2< T >::norm( const Vector2< T > &v )
{
  return v.x * v.x + v.y * v.y;
}

//
template< typename T >
inline T Vector2< T >::distance( const Vector2< T > &v1, const Vector2< T > &v2 )
{
  Vector2< T > v = v1 - v2;
  return length(v);
}

//
template< typename T >
inline T Vector2< T >::dot( const Vector2< T > &v1, const Vector2< T > &v2 )
{
  return v1.x * v2.x + v1.y * v2.y;
}

//
template< typename T >
inline T Vector2< T >::ccw( const Vector2< T > &v1, const Vector2< T > &v2 )
{
  return v1.x * v2.y - v1.y * v2.x;
}

/*!
  output stream
*/
template< typename T > 
std::ostream &operator<<( std::ostream &os, const Vector2< T > &v )
{
  os << v.x << ", " << v.y;
  return os;
}

typedef Vector2< unsigned char > Vector2UC;
typedef Vector2< int > Vector2I;
typedef Vector2< float>  Vector2F;
typedef Vector2< double > Vector2D;
