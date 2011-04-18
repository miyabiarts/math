#pragma once

#include <memory>
#include <cmath>

template< typename T > struct Vector3;
template< typename T > struct Quaternion;

//! 4x4 Matrix
template< typename T = double >
struct Matrix4
{
  Matrix4< T >();
  Matrix4< T >( T _11, T _12, T _13, T _14, T _21, T _22, T _23, T _24, T _31, T _32, T _33, T _34, T _41, T _42, T _43, T _44 );
  Matrix4< T >( const Matrix4< T > &m );
  
  T &operator () ( unsigned int row, unsigned int col );
  T  operator () ( unsigned int row, unsigned int col ) const;
  
  Matrix4< T > operator + () const;
  Matrix4< T > operator - () const;
  
  Matrix4< T > operator * ( const Matrix4< T > &m ) const;
  Matrix4< T > operator + ( const Matrix4< T > &m ) const;
  Matrix4< T > operator - ( const Matrix4< T > &m ) const;
  Matrix4< T > operator * ( T ) const;
  Matrix4< T > operator / ( T ) const;
  
  Matrix4< T > &operator *= ( const Matrix4< T > &m );
  Matrix4< T > &operator += ( const Matrix4< T > &m );
  Matrix4< T > &operator -= ( const Matrix4< T > &m );
  Matrix4< T > &operator *= ( T s );
  Matrix4< T > &operator /= ( T s );
  
  bool operator == ( const Matrix4< T > &m ) const;
  bool operator != ( const Matrix4< T > &m ) const;
  
  // static function
  /*!
    @biref create identity matrix
  */
  static Matrix4< T > &identity( Matrix4< T > &m );
  /*!
    @biref create translation matrix
  */
  static Matrix4< T > &translation( Matrix4< T > &m, T x, T y, T z );
  /*!
    @biref create translation matrix
  */
  static Matrix4< T > &translation( Matrix4< T > &m , const Vector3< T > &v );
  /*!
    @brief create x-axis rotation matrix    
  */
  static Matrix4< T > & rotationX( Matrix4< T > &m, T rad );
  /*!
    @brief create y-axis rotation matrix    
  */
  static Matrix4< T > & rotationY( Matrix4< T > &m, T rad );
  /*!
    @brief create z-axis rotation matrix    
  */
  static Matrix4< T > & rotationZ( Matrix4< T > &m, T rad );
  /*!
    @brief create yaw-pitch-roll rotation matrix    
  */
  static Matrix4< T > & rotationYawPitchRoll( Matrix4< T > &m, T yaw, T pitch, T roll );
  /*!
    @brief create any-axis rotation matrix    
  */
  static Matrix4< T > & rotationAxis( Matrix4< T > &m, const Vector3< T > &axis, T rad );
  /*!
    @brief create quaterninon rotation matrix    
  */
  static Matrix4< T > & rotationQuaternion( Matrix4< T > &m,const Quaternion< T > &q );
  /*!
    @brief create scaling matrix    
  */
  static Matrix4< T > & scaling( Matrix4< T > &m, T sx, T sy, T sz );
  /*!
    @brief create scaling matrix    
  */
  static Matrix4< T > & scaling( Matrix4< T > &m, const Vector3< T > &sv );  
  /*!
    @brief calculate determinant
  */
  static T determinant( const Matrix4< T > &m );
  /*!
    @brief calculate inverse matrix
  */
  static Matrix4< T > &inverse( Matrix4< T > &m, const Matrix4< T > &m0, T *det = 0 );
  /*!
    @brief create view matrix (left hand coordinate system)
  */
  static Matrix4< T > &viewLH( Matrix4< T > &m, const Vector3< T > &eyePos, const Vector3< T > &lookAt, const Vector3< T > &up );
  /*!
    @brief create view matrix (right hand coordinate system)
  */
  static Matrix4< T > &viewRH( Matrix4< T > &m, const Vector3< T > &eyePos, const Vector3< T > &lookAt, const Vector3< T > &up );
  /*!
    @brief create perspective matrix (left hand coordinate system)
  */
  static Matrix4< T > &perspectiveLH( Matrix4< T > &m, T fovy, T aspect, T zn, T zl );
  /*!
    @brief create perspective projection matrix (right hand coordinate system)
  */
  static Matrix4< T > &perspectiveRH( Matrix4< T > &m, T fovy, T aspect, T zn, T zl );
  /*!
    @brief create ortho projection matrix (left hand coordinate system)
  */
  static Matrix4< T > &orthoLH( Matrix4< T > &m, T w, T h, T zn, T zf );
  /*!
    @brief create ortho projection matrix (right hand coordinate system)
  */
  static Matrix4< T > &orthoRH( Matrix4< T > &m, T w, T h, T zn ,T zf );
  /*!
    @brief create screen matrix
  */
  static Matrix4< T > &screen( Matrix4< T > &m, T width, T height );
  /*!
    @brief transpose matrix
  */
  static Matrix4< T > &transpose( Matrix4< T > &m,const Matrix4< T > &m0 );

  union
  {
    struct
    {
      T _11,_12,_13,_14;
      T _21,_22,_23,_24;
      T _31,_32,_33,_34;
      T _41,_42,_43,_44;
    };
    T m[ 16 ];
  };
  
};

//
template< typename T >
inline Matrix4< T >::Matrix4()
{
  this->_11 = this->_12 = this->_13 = this->_14 = 0;
  this->_21 = this->_22 = this->_23 = this->_24 = 0;
  this->_31 = this->_32 = this->_33 = this->_34 = 0;
  this->_41 = this->_42 = this->_43 = this->_44 = 0;
}

//
template< typename T >
inline Matrix4< T >::Matrix4( T _11_, T _12_, T _13_, T _14_, 
			      T _21_, T _22_, T _23_, T _24_,
			      T _31_, T _32_, T _33_, T _34_,
			      T _41_, T _42_, T _43_, T _44_ )
{
  this->_11 = _11_;
  this->_12 = _12_;
  this->_13 = _13_;
  this->_14 = _14_;
  this->_21 = _21_;
  this->_22 = _22_;
  this->_23 = _23_;
  this->_24 = _24_;
  this->_31 = _31_;
  this->_32 = _32_;
  this->_33 = _33_;
  this->_34 = _34_;
  this->_41 = _41_;
  this->_42 = _42_;
  this->_43 = _43_;
  this->_44 = _44_;
}

//
template< typename T >
inline Matrix4< T >::Matrix4( const Matrix4< T > &m )
{
  this->_11 = m._11;
  this->_12 = m._12;
  this->_13 = m._13;
  this->_14 = m._14;
  this->_21 = m._21;
  this->_22 = m._22;
  this->_23 = m._23;
  this->_24 = m._24;
  this->_31 = m._31;
  this->_32 = m._32;
  this->_33 = m._33;
  this->_34 = m._34;
  this->_41 = m._41;
  this->_42 = m._42;
  this->_43 = m._43;
  this->_44 = m._44;
}

//
template< typename T >
inline T &Matrix4< T >::operator ()( unsigned int row, unsigned int col )
{
  return this->m[ row * 4 + col ];
}

//
template< typename T >
inline T Matrix4< T >::operator ()( unsigned int row, unsigned int col ) const
{
  return this->m[ row * 4 + col ];
}

//
template< typename T >
inline Matrix4< T > Matrix4< T >::operator +() const
{
  return Matrix4< T >( _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44 );
}

//
template< typename T >
inline Matrix4< T > Matrix4< T >::operator - () const
{
  return Matrix4< T >( -_11, -_12, -_13, -_14, -_21, -_22, -_23, -_24, -_31, -_32, -_33, -_34, -_41, -_42, -_43, -_44 );
}

//
template< typename T >
inline Matrix4< T > Matrix4< T >::operator *( const Matrix4< T > &m ) const
{
  return Matrix4< T >( 
		      _11*m._11 + _12*m._21 + _13*m._31 + _14*m._41,
		      _11*m._12 + _12*m._22 + _13*m._32 + _14*m._42,
		      _11*m._13 + _12*m._23 + _13*m._33 + _14*m._43,
		      _11*m._14 + _12*m._24 + _13*m._34 + _14*m._44,
		    
		      _21*m._11 + _22*m._21 + _23*m._31 + _24*m._41,
		      _21*m._12 + _22*m._22 + _23*m._32 + _24*m._42,
		      _21*m._13 + _22*m._23 + _23*m._33 + _24*m._43,
		      _21*m._14 + _22*m._24 + _23*m._34 + _24*m._44,
		    
		      _31*m._11 + _32*m._21 + _33*m._31 + _34*m._41,
		      _31*m._12 + _32*m._22 + _33*m._32 + _34*m._42,
		      _31*m._13 + _32*m._23 + _33*m._33 + _34*m._43,
		      _31*m._14 + _32*m._24 + _33*m._34 + _34*m._44,
		    
		      _41*m._11 + _42*m._21 + _43*m._31 + _44*m._41,
		      _41*m._12 + _42*m._22 + _43*m._32 + _44*m._42,
		      _41*m._13 + _42*m._23 + _43*m._33 + _44*m._43,
		      _41*m._14 + _42*m._24 + _43*m._34 + _44*m._44
		       );
}

//
template< typename T >
inline Matrix4< T > Matrix4< T >::operator +( const Matrix4< T > &m ) const
{
  return Matrix4< T >( 
		      _11+m._11,_12+m._12,_13+m._13,_14+m._14,
		      _21+m._21,_22+m._22,_23+m._23,_24+m._24,
		      _31+m._31,_32+m._32,_33+m._33,_34+m._34,
		      _41+m._41,_42+m._42,_43+m._43,_44+m._44
		       );
}

//
template< typename T >
inline Matrix4< T > Matrix4< T >::operator - (  const Matrix4< T > &m ) const
{
  return Matrix4< T >( 
		      _11-m._11,_12-m._12,_13-m._13,_14-m._14,
		      _21-m._21,_22-m._22,_23-m._23,_24-m._24,
		      _31-m._31,_32-m._32,_33-m._33,_34-m._34,
		      _41-m._41,_42-m._42,_43-m._43,_44-m._44
		       );
}

//
template< typename T >
inline Matrix4< T > Matrix4< T >::operator * ( T s ) const
{
  return Matrix4< T >( 
		      _11*s,_12*s,_13*s,_14*s,
		      _21*s,_22*s,_23*s,_24*s,
		      _31*s,_32*s,_33*s,_34*s,
		      _41*s,_42*s,_43*s,_44*s
		       );
}

//
template< typename T >
inline Matrix4< T > Matrix4< T >::operator / ( T s ) const
{
  T f = 1/s;
  return operator * ( f );
}

//
template< typename T, typename T2 >
inline Matrix4< T > operator * ( T2 s,const Matrix4< T > &m )
{
  return Matrix4< T >( 
		      m._11*s,m._12*s,m._13*s,m._14*s,
		      m._21*s,m._22*s,m._23*s,m._24*s,
		      m._31*s,m._32*s,m._33*s,m._34*s,
		      m._41*s,m._42*s,m._43*s,m._44*s
		       );
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::operator *=( const Matrix4< T > &m )
{
  Matrix4< T > tmp( 
		   _11*m._11 + _12*m._21 + _13*m._31 + _14*m._41,
		   _11*m._12 + _12*m._22 + _13*m._32 + _14*m._42,
		   _11*m._13 + _12*m._23 + _13*m._33 + _14*m._43,
		   _11*m._14 + _12*m._24 + _13*m._34 + _14*m._44,
		 
		   _21*m._11 + _22*m._21 + _23*m._31 + _24*m._41,
		   _21*m._12 + _22*m._22 + _23*m._32 + _24*m._42,
		   _21*m._13 + _22*m._23 + _23*m._33 + _24*m._43,
		   _21*m._14 + _22*m._24 + _23*m._34 + _24*m._44,
		 
		   _31*m._11 + _32*m._21 + _33*m._31 + _34*m._41,
		   _31*m._12 + _32*m._22 + _33*m._32 + _34*m._42,
		   _31*m._13 + _32*m._23 + _33*m._33 + _34*m._43,
		   _31*m._14 + _32*m._24 + _33*m._34 + _34*m._44,
		 
		   _41*m._11 + _42*m._21 + _43*m._31 + _44*m._41,
		   _41*m._12 + _42*m._22 + _43*m._32 + _44*m._42,
		   _41*m._13 + _42*m._23 + _43*m._33 + _44*m._43,
		   _41*m._14 + _42*m._24 + _43*m._34 + _44*m._44 );
  *this = tmp;
  
  return *this;
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::operator += ( const Matrix4< T > &m )
{
  this->_11 += m._11;
  this->_12 += m._12;
  this->_13 += m._13;
  this->_14 += m._14;
  
  this->_21 += m._21;
  this->_22 += m._22;
  this->_23 += m._23;
  this->_24 += m._24;
  
  this->_31 += m._31;
  this->_32 += m._32;
  this->_33 += m._33;
  this->_34 += m._34;
  
  this->_41 += m._41;
  this->_42 += m._42;
  this->_43 += m._43;
  this->_44 += m._44;
  
  return *this;
}


template< typename T >
inline Matrix4< T > &Matrix4< T >::operator -= ( const Matrix4< T > &m )
{
  this->_11 -= m._11;
  this->_12 -= m._12;
  this->_13 -= m._13;
  this->_14 -= m._14;
  
  this->_21 -= m._21;
  this->_22 -= m._22;
  this->_23 -= m._23;
  this->_24 -= m._24;
  
  this->_31 -= m._31;
  this->_32 -= m._32;
  this->_33 -= m._33;
  this->_34 -= m._34;
  
  this->_41 -= m._41;
  this->_42 -= m._42;
  this->_43 -= m._43;
  this->_44 -= m._44;
  
  return *this;
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::operator *= ( T s )
{
  this->_11 *= s;
  this->_12 *= s;
  this->_13 *= s;
  this->_14 *= s;
  
  this->_21 *= s;
  this->_22 *= s;
  this->_23 *= s;
  this->_24 *= s;
  
  this->_31 *= s;
  this->_32 *= s;
  this->_33 *= s;
  this->_34 *= s;
  
  this->_41 *= s;
  this->_42 *= s;
  this->_43 *= s;
  this->_44 *= s;
  
  return *this;
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::operator /= ( T s )
{
  T f = 1/s;
  
  return operator *=( f );
  
  return *this;
}

//
template< typename T >
inline bool Matrix4< T >::operator == ( const Matrix4< T > &m ) const
{
  return ( memcmp( this,&m,sizeof( Matrix4< T > ) )==0 )?true:false;
}

//
template< typename T >
inline bool Matrix4< T >::operator != ( const Matrix4< T > &m ) const
{
  return !operator==( m );
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::identity( Matrix4< T > &m )
{
  m._11 = m._22 = m._33 = m._44 = 1;
  m._12 = m._13 = m._14 = 0;
  m._21 = m._23 = m._24 = 0;
  m._31 = m._32 = m._34 = 0;
  m._41 = m._42 = m._43 = 0;
  return m;
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::translation( Matrix4< T > &m, T x, T y, T z )
{
  m._11 = m._22 = m._33 = 1;
  m._12 = m._13 = m._14 = 0;
  m._21 = m._23 = m._24 = 0;
  m._31 = m._32 = m._34 = 0;
  m._41 = x; m._42 = y; m._43 = z; m._44 = 1;
  return m;
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::translation( Matrix4< T > &m, const Vector3< T > &v )
{
  return translation( m, v.x, v.y, v.z );
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::rotationX( Matrix4< T > &m, T rad )
{
  m._11 = 1;
  m._12 = 0;
  m._13 = 0;
  m._14 = 0;
  
  m._21 = 0;
  m._22 = static_cast< T >( cos( static_cast<double>( rad ) ) );
  m._23 = static_cast< T >( sin( static_cast<double>( rad ) ) );
  m._24 = 0;
  
  m._31 = 0;
  m._32 = -static_cast< T >( sin( static_cast<double>( rad ) ) );
  m._33 = static_cast< T >( cos( static_cast<double>( rad ) ) );
  m._34 = 0;
  
  m._41 = 0;
  m._42 = 0;
  m._43 = 0;
  m._44 = 1;
  return m;
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::rotationY( Matrix4< T > &m, T rad )
{
  m._11 = static_cast< T >( cos( static_cast<double>( rad ) ) );
  m._12 = 0;
  m._13 = -static_cast< T >( sin( static_cast<double>( rad ) ) );
  m._14 = 0;
  
  m._21 = 0;
  m._22 = 1;
  m._23 = 0;
  m._24 = 0;
  
  m._31 = static_cast< T >( sin( static_cast<double>( rad ) ) );
  m._32 = 0;
  m._33 = static_cast< T >( cos( static_cast<double>( rad ) ) );
  m._34 = 0;
  
  m._41 = 0;
  m._42 = 0;
  m._43 = 0;
  m._44 = 1;
  return m;
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::rotationZ( Matrix4< T > &m, T rad )
{
  m._11 = static_cast< T >( cos( static_cast<double>( rad ) ) );
  m._12 = static_cast< T >( sin( static_cast<double>( rad ) ) );
  m._13 = 0;
  m._14 = 0;
  
  m._21 = -static_cast< T >( sin( static_cast<double>( rad ) ) );
  m._22 = static_cast< T >( cos( static_cast<double>( rad ) ) );
  m._23 = 0;
  m._24 = 0;
  
  m._31 = 0;
  m._32 = 0;
  m._33 = 1;
  m._34 = 0;
  
  m._41 = 0;
  m._42 = 0;
  m._43 = 0;
  m._44 = 1;
  return m;
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::scaling( Matrix4< T > &m, T sx, T sy, T sz )
{
  identity( m );
  m._11 *= sx;
  m._22 *= sy;
  m._33 *= sz;
  return m;
}

//
template< typename T >
Matrix4< T > & Matrix4< T >::scaling( Matrix4< T > &m, const Vector3< T > &sv )
{
  return scaling( m, sv.x, sv.y, sv.z );
}

//
template< typename T >
inline T Matrix4< T >::determinant( const Matrix4< T > &m )
{
  return m._11*m._22*m._33*m._44 + m._11*m._23*m._34*m._42 + m._11*m._24*m._32*m._43
    + m._12*m._21*m._34*m._43 + m._12*m._23*m._31*m._44 + m._12*m._24*m._33*m._41
    + m._13*m._21*m._32*m._44 + m._13*m._22*m._34*m._41 + m._13*m._24*m._31*m._42
    + m._14*m._21*m._33*m._42 + m._14*m._22*m._31*m._43 + m._14*m._23*m._32*m._41
    - m._11*m._22*m._34*m._43 - m._11*m._23*m._32*m._44 - m._11*m._24*m._33*m._42
    - m._12*m._21*m._33*m._44 - m._12*m._23*m._34*m._41 - m._12*m._24*m._31*m._43
    - m._13*m._21*m._34*m._42 - m._13*m._22*m._31*m._44 - m._13*m._24*m._32*m._41
    - m._14*m._21*m._32*m._43 - m._14*m._22*m._33*m._41 - m._14*m._23*m._31*m._42;
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::inverse( Matrix4< T > &m, const Matrix4< T > &m0, T *det )
{
  T d = determinant( m0 );
  
  if( det ) * det = d;
  if( d == 0 ) return m;
  
  Matrix4< T > t;
  t._11 = m0._22*m0._33*m0._44 + m0._23*m0._34*m0._42 + m0._24*m0._32*m0._43 - m0._22*m0._34*m0._43 - m0._23*m0._32*m0._44 - m0._24*m0._33*m0._42;
  t._12 = m0._12*m0._34*m0._43 + m0._13*m0._32*m0._44 + m0._14*m0._33*m0._42 - m0._12*m0._33*m0._44 - m0._13*m0._34*m0._42 - m0._14*m0._32*m0._43;
  t._13 = m0._12*m0._23*m0._44 + m0._13*m0._24*m0._42 + m0._14*m0._22*m0._43 - m0._12*m0._24*m0._43 - m0._13*m0._22*m0._44 - m0._14*m0._23*m0._42;
  t._14 = m0._12*m0._24*m0._33 + m0._13*m0._22*m0._34 + m0._14*m0._23*m0._32 - m0._12*m0._23*m0._34 - m0._13*m0._24*m0._32 - m0._14*m0._22*m0._33;
  
  t._21 = m0._21*m0._34*m0._43 + m0._23*m0._31*m0._44 + m0._24*m0._33*m0._41 - m0._21*m0._33*m0._44 - m0._23*m0._34*m0._41 - m0._24*m0._31*m0._43;
  t._22 = m0._11*m0._33*m0._44 + m0._13*m0._34*m0._41 + m0._14*m0._31*m0._43 - m0._11*m0._34*m0._43 - m0._13*m0._31*m0._44 - m0._14*m0._33*m0._41;
  t._23 = m0._11*m0._24*m0._43 + m0._13*m0._21*m0._44 + m0._14*m0._23*m0._41 - m0._11*m0._23*m0._44 - m0._13*m0._24*m0._41 - m0._14*m0._21*m0._43;
  t._24 = m0._11*m0._23*m0._34 + m0._13*m0._24*m0._31 + m0._14*m0._21*m0._33 - m0._11*m0._24*m0._33 - m0._13*m0._21*m0._34 - m0._14*m0._23*m0._31;
  
  t._31 = m0._21*m0._32*m0._44 + m0._22*m0._34*m0._41 + m0._24*m0._31*m0._42 - m0._21*m0._34*m0._42 - m0._22*m0._31*m0._44 - m0._24*m0._32*m0._41;
  t._32 = m0._11*m0._34*m0._42 + m0._12*m0._31*m0._44 + m0._14*m0._32*m0._41 - m0._11*m0._32*m0._44 - m0._12*m0._34*m0._41 - m0._14*m0._31*m0._42;
  t._33 = m0._11*m0._22*m0._44 + m0._12*m0._24*m0._41 + m0._14*m0._21*m0._42 - m0._11*m0._24*m0._42 - m0._12*m0._21*m0._44 - m0._14*m0._22*m0._41;
  t._34 = m0._11*m0._24*m0._32 + m0._12*m0._21*m0._34 + m0._14*m0._22*m0._31 - m0._11*m0._22*m0._34 - m0._12*m0._24*m0._31 - m0._14*m0._21*m0._32;
  
  t._41 = m0._21*m0._33*m0._42 + m0._22*m0._31*m0._43 + m0._23*m0._32*m0._41 - m0._21*m0._32*m0._43 - m0._22*m0._33*m0._41 - m0._23*m0._31*m0._42;
  t._42 = m0._11*m0._32*m0._43 + m0._12*m0._33*m0._41 + m0._13*m0._31*m0._42 - m0._11*m0._33*m0._42 - m0._12*m0._31*m0._43 - m0._13*m0._32*m0._41;
  t._43 = m0._11*m0._23*m0._42 + m0._12*m0._21*m0._43 + m0._13*m0._22*m0._41 - m0._11*m0._22*m0._43 - m0._12*m0._23*m0._41 - m0._13*m0._21*m0._42;
  t._44 = m0._11*m0._22*m0._33 + m0._12*m0._23*m0._31 + m0._13*m0._21*m0._32 - m0._11*m0._23*m0._32 - m0._12*m0._21*m0._33 - m0._13*m0._22*m0._31;
  
  m = t / d;
  return m;
}

//
template< typename T >
inline Matrix4< T > &Matrix4< T >::transpose( Matrix4< T > &m, const Matrix4< T > &m0 )
{
  Matrix4< T > tm = m0;
  for( int i = 0; i < 4; ++i )
    {
      for( int j = 0; j < 4; ++j )
	{
	  m.m[ i * 4 + j ] = tm.m[ j * 4 + i ];
	}
    }
  return m;
}


#include "Vector3.h"
#include "Quaternion.h"

//
template< typename T >
Matrix4< T > & Matrix4< T >::rotationQuaternion( Matrix4< T > &m, const Quaternion< T > &q )
{
  Quaternion< T >::toMatrix( m, q );
  return m;
}

//
template< typename T >
Matrix4< T > & Matrix4< T >::rotationYawPitchRoll( Matrix4< T > &m, T yaw, T pitch, T roll )
{
  Matrix4< T > mrx,mry,mrz;
  rotationX( mrx, pitch );
  rotationY( mry, yaw );
  rotationZ( mrz, roll );
  
  m = mrz * mrx * mry;
  return m;
}

//
template< typename T >
Matrix4< T > & Matrix4< T >::rotationAxis( Matrix4< T > &m, const Vector3< T > &axis, T rad )
{
  Quaternion< T > q;
  Quaternion< T >::rotationAxis( q, axis, rad );
  rotationQuaternion( m, q );
  return m;
}

//
template< typename T >
Matrix4< T > & Matrix4< T >::viewLH( Matrix4< T > &m, const Vector3< T > &eyePos, const Vector3< T > &lookAt, const Vector3< T > &up )
{
  Vector3< T > axisz = lookAt - eyePos;
  Vector3< T >::normalize( axisz, axisz );
  
  Vector3< T > axisx;
  Vector3< T >::cross( axisx, up, axisz );
  Vector3< T >::normalize( axisx, axisx );
  
  Vector3< T > axisy;
  Vector3< T >::cross( axisy, axisz, axisx );
  
  m = Matrix4< T >( 
		   axisx.x, axisy.x, axisz.x,0,
		   axisx.y, axisy.y, axisz.y,0,
		   axisx.z, axisy.z, axisz.z,0,
		   -Vector3< T >::dot( axisx, eyePos ), -Vector3< T >::dot( axisy, eyePos ), -Vector3< T >::dot( axisz, eyePos ), 1 );
  return m;
}

//
template< typename T >
Matrix4< T > & Matrix4< T >::viewRH( Matrix4< T > &m, const Vector3< T > &eyePos, const Vector3< T > &lookAt,const Vector3< T > &up )
{
  Vector3< T > axisz = eyePos - lookAt;
  Vector3< T >::normalize( axisz, axisz );
  
  Vector3< T > axisx;
  Vector3< T >::cross( axisx, up, axisz );
  Vector3< T >::normalize( axisx, axisx );
  
  Vector3< T > axisy;
  Vector3< T >::cross( axisy, axisz, axisx );
  
  m = Matrix4< T >( 
		   axisx.x, axisy.x, axisz.x,0,
		   axisx.y, axisy.y, axisz.y,0,
		   axisx.z, axisy.z, axisz.z,0,
		   -Vector3< T >::dot( axisx, eyePos ), -Vector3< T >::dot( axisy, eyePos ), -Vector3< T >::dot( axisz, eyePos ), 1 );
  return m;
}

//
template< typename T >
Matrix4< T > & Matrix4< T >::perspectiveLH( Matrix4< T > &m,T fovy,T aspect,T zn,T zf )
{
  T y = static_cast< T >( 1.0/tan( static_cast<double>( fovy/2.0 ) ) );
  T x = y / aspect;
  m = Matrix4< T >( 
		   x, 0, 0, 0,
		   0, y, 0, 0,
		   0, 0, zf / ( zf - zn ), 1,
		   0, 0, -zn * zf / ( zf - zn ), 0
		    );
  return m;
}

//
template< typename T >
Matrix4< T > & Matrix4< T >::perspectiveRH( Matrix4< T > &m,T fovy,T aspect,T zn,T zf )
{
  T y = static_cast< T >( 1.0/tan( static_cast<double>( fovy/2.0 ) ) );
  T x = y / aspect;
  m = Matrix4< T >( 
		   x, 0, 0, 0,
		   0, y, 0, 0,
		   0, 0, zf / ( zn - zf ), -1,
		   0, 0, -zn * zf / ( zf - zn ), 0
		    );
  return m;
}

//
template< typename T >
Matrix4< T > & Matrix4< T >::orthoLH( Matrix4< T > &m,T w,T h,T zn,T zf )
{
  m = Matrix4< T >( 
		   static_cast< T >( 2.0 / w ), 0, 0, 0,
		   0, static_cast< T >( 2.0 / h ), 0, 0,
		   0, 0, static_cast< T >( 1.0 /( zf - zn ) ), 0,
		   0, 0, static_cast< T >( zn / ( zn - zf ) ), 1
		    );
  return m;
}

//
template< typename T >
Matrix4< T > & Matrix4< T >::orthoRH( Matrix4< T > &m, T w, T h, T zn, T zf )
{
  m = Matrix4< T >( 
		   static_cast< T >( 2.0/w ), 0, 0, 0,
		   0, static_cast< T >( 2.0/h ), 0, 0,
		   0, 0, static_cast< T >( 1.0/( zn-zf ) ), 0,
		   0, 0, static_cast< T >( zn/( zn-zf ) ), 1
		    );
  return m;
}

//
template< typename T >
Matrix4< T > & Matrix4< T >::screen( Matrix4< T > &m, T width, T height )
{
  T w = width/2;
  T h = height/2;
  m = Matrix4< T >( w, 0, 0, 0,
		    0, -h, 0, 0,
		    0, 0, 1, 0,
		    w, h, 0, 1
		    );
  return m;
}

/*!
  @brief output stream
*/
template< typename T > 
std::ostream &operator<<( std::ostream &os, const Matrix4< T > &m )
{
  os << m._11 << ", " << m._12 << ", " << m._13 << ", " << m._14 << std::endl;
  os << m._21 << ", " << m._22 << ", " << m._23 << ", " << m._24 << std::endl;
  os << m._31 << ", " << m._32 << ", " << m._33 << ", " << m._34 << std::endl;
  os << m._41 << ", " << m._42 << ", " << m._43 << ", " << m._44;
  return os;
}
			  

typedef Matrix4< unsigned char > Matrix4UC;
typedef Matrix4< int >           Matrix4I;
typedef Matrix4< float >	 Matrix4F;
typedef Matrix4< double >	 Matrix4D;
