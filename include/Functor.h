//////////////////////////////////////////////////////////////////////
/// @file   Functor.h
/// @author Ryan Krattiger
/// @brief  A functor class that holds a function with two inputs and 
///         one output.
//////////////////////////////////////////////////////////////////////

#ifndef ABSTRACT_FUNCTOR_XY_H
#define ABSTRACT_FUNCTOR_XY_H

template <class T>
class AFunctorxy
{
public:
  virtual T operator()(const T& x, const T& y) = 0;
};  

#endif // ABSTRACT_FUNCTOR_XY_H