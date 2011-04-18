#pragma once

//! Color
template< typename T = unsigned char >
struct Color
{  
  Color< T >();
  Color< T >( const Color< T > & );
  Color< T >( T r, T g, T b, T a );


  Color< T > operator + () const;
  Color< T > operator - () const;

  Color< T > operator + ( const Color< T > &c ) const;
  Color< T > operator - ( const Color< T > &c ) const;
  Color< T > operator * ( T s ) const;
  Color< T > operator / ( T s ) const;

  Color< T > &operator += (const Color< T > &);
  Color< T > &operator -= (const Color< T > &);
  Color< T > &operator *= (T);
  Color< T > &operator /= (T);

  Color< T > &operator=(const Color< T > &c);

  bool operator == ( const Color< T > & ) const;
  bool operator != ( const Color< T > & ) const;

  union
  {
    struct
    {
      T r, g, b, a;
    };
    T v[ 4 ];
  };
};


//
template< typename T >
inline Color< T >::Color() : 
  r( 0 ), g( 0 ), b( 0 ), a( 0 ) 
{

}

//
template< typename T >
inline Color< T >::Color( const Color< T > &c )
{
  this->r = c.r;
  this->g = c.g;
  this->b = c.b;
  this->a = c.a;
}

//
template< typename T >
Color< T >::Color( T r, T g, T b, T a )
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}


//
template< typename T >
inline Color< T > &Color< T >::operator=( const Color< T > &c )
{
  if( this == &c )
    {
      return *this;
    }
  
  this->r = c.r;
  this->g = c.g;
  this->b = c.b;
  this->a = c.a;
  
  return *this;
}


//
template< typename T >
inline Color< T > Color< T >::operator +() const
{
  return Color< T >( r, g, b, a );
}

//
template< typename T >
inline Color< T > Color< T >::operator -() const
{
  return Color< T >( -r, -g, -b, -a );
}

//
template< typename T >
inline Color< T > Color< T >::operator +( const Color< T > &c ) const
{
  return Color< T >( r + c.r, g + c.g, b + c.b, a + c.a );
}

//
template< typename T >
inline Color< T > Color< T >::operator -( const Color< T > &c ) const
{
  return Color< T >( r - c.r, g - c.g, b - c.b, a-c.a );
}

//
template< typename T >
inline Color< T > Color< T >::operator *( T s ) const
{
  return Color< T >( r * s, g * s, b * s, a * s );
}

//
template< typename T >
inline Color< T > Color< T >::operator /( T s ) const
{
  double t = 1.0 / s;
  return ( *this ) * t;
}

//
template< typename T >
inline Color< T > &Color< T >::operator += ( const Color< T > &c )
{
  r += c.r;
  g += c.g;
  b += c.b;
  a += c.a;
  return *this;
}

//
template< typename T >
inline Color< T > &Color< T >::operator -= ( const Color< T > &c )
{
  r -= c.r;
  g -= c.g;
  b -= c.b;
  a -= c.a;
  return *this;
}

//
template< typename T >
inline Color< T > &Color< T >::operator *= ( T s )
{
  r *= s;
  g *= s;
  b *= s;
  a *= s;
  return *this;
}

//
template< typename T >
inline Color< T > &Color< T >::operator /= ( T s )
{
  double t = 1.0 / s;
  r *= t;
  g *= t;
  b *= t;
  a *= t;
  return *this;
}

//
template< typename T >
inline bool Color< T >::operator == ( const Color< T > &c ) const
{
  return ( r == c.r && g == c.g && b == c.b && a == c.a );
}

//
template< typename T >
inline bool Color< T >::operator != ( const Color< T > &c ) const
{
  return !operator ==( c );
}


//
template< typename T, typename T2 >
inline Color< T > operator * ( T2 s, const Color< T > &c )
{
  return Color< T >( c.r * s, c.g * s, c.b * s, c.a );
}

/*!
  output stream
*/
template< typename T > 
std::ostream &operator<<( std::ostream &os, const Color< T > &c )
{
  os << c.r << ", " << c.g << ", " << c.b << ", " << c.a;
  return os;
}


typedef Color< unsigned char > ColorUC;
typedef Color< int > ColorI;
typedef Color< float > ColorF;
typedef Color< double > ColorD;

