/*
 *  lower.hpp
 *  Author: Ryan Krattiger
 *
 *  Namespace: numlib
 *  Brief: Upper Triangle Matrix Form class implementation.
 */

template <class Type>
numlib::LowerTriangle<Type>::LowerTriangle(
  std::size_t const &n):
  data_((n*(n+1))/2),
  n_(n)
{
}

template <class Type>
numlib::LowerTriangle<Type>::LowerTriangle(
  std::size_t const &n,
  std::size_t const &m):
  data_((n*(n+1))/2),
  n_(n)
{
}

template <class Type>
numlib::LowerTriangle<Type>&
numlib::LowerTriangle<Type>::operator = (
  numlib::LowerTriangle<Type> cpy)
{
  swap(*this,cpy);

  return *this;
}

template <class Type>
numlib::LowerTriangle<Type>::LowerTriangle(
  Matrix<Type,LowerTriangle> const &src):
  LowerTriangle(static_cast<const LowerTriangle<Type>&>(src))
{
}

template <class Type>
numlib::LowerTriangle<Type>::LowerTriangle(
  LowerTriangle<Type> const &src):
  data_(src.data_),
  n_(src.n_)
{
}

template <class Type>
numlib::LowerTriangle<Type>::LowerTriangle(
  LowerTriangle<Type> &&other):
  data_(std::move(other.data_)),
  n_(other.n_)
{}

template <class Type>
template <template <class> class F>
numlib::LowerTriangle<Type>
numlib::LowerTriangle<Type>::operator + (
  Matrix<Type,F> const &rhs) const
{
  numlib::LowerTriangle<Type> ret(*this);
  return ret+=rhs;
}

template <class Type>
template <template <class> class F>
numlib::LowerTriangle<Type>&
numlib::LowerTriangle<Type>::operator += (
  Matrix<Type,F> const &rhs)
{
  if(N()!=rhs.N()||M()!=rhs.M())
    throw DimensionMismatch("Matrix addition with operator += failed");

  for(std::size_t i=0; i<N(); ++i)
  {
    for(std::size_t j=0; j<i+1; ++j)
    {
      this->operator[]({i,j}) += rhs[{i,j}];
    }
  }
  return *this;
}

template <class Type>
template <template <class> class F>
numlib::LowerTriangle<Type>
numlib::LowerTriangle<Type>::operator - (
  Matrix<Type,F> const &rhs) const
{
  numlib::LowerTriangle<Type> ret(*this);
  return ret-=rhs;
}

template <class Type>
template <template <class> class F>
numlib::LowerTriangle<Type>&
numlib::LowerTriangle<Type>::operator -= (
  Matrix<Type,F> const &rhs)
{
  if(N()!=rhs.N()||M()!=rhs.M())
    throw DimensionMismatch("Matrix addition with operator += failed");

  for(std::size_t i=0; i<N(); ++i)
  {
    for(std::size_t j=0; j<i+1; ++j)
    {
      this->operator[]({i,j}) -= rhs[{i,j}];
    }
  }
  return *this;
}

template <class Type>
template <template <class> class F>
numlib::Matrix<Type,numlib::Dense>&
numlib::LowerTriangle<Type>::operator * (
  Matrix<Type,F> const &rhs) const
{
  if(M() != rhs.N())
    throw numlib::DimensionMismatch(
      "numlib::LowerTriangle<Type>operator *(Matrix<Type,F> const &rhs)");

  Matrix<Type,Dense>* ret = new Dense<Type>(N(), rhs.M());

  for(std::size_t i=0; i<N(); ++i)
  {
    for(std::size_t j=0; j<rhs.M(); ++j)
    {
      ret[{i,j}] = 0;
      for(std::size_t k=0; k<i+1; ++k)
      {
        ret->operator[]({i,j}) += this->operator[]({i,k})*rhs[{k,j}];
      }
    }
  }

  return *ret;
}

template <class Type>
numlib::Vector<Type>
numlib::LowerTriangle<Type>::operator * (
  Vector<Type> const &rhs) const
{
  if(M() != rhs.get_size())
    throw DimensionMismatch("LowerTriangle::operator *(Vector): Vector");

  Vector<Type> ret(rhs);

  for(std::size_t i=0; i<N(); ++i)
  {
    ret[i] = 0;
    for(std::size_t k=0; k<i+1; ++k)
    {
      ret[i] += this->operator[]({i,k})*rhs[k];
    }
  }

  return ret;
}

template <class Type>
inline Type
numlib::LowerTriangle<Type>::operator[](
  std::initializer_list<std::size_t> ij) const
{
  if(ij.size() != 2 || *(ij.begin()) >= N() || *(ij.begin()+1) >= M())
    throw RangeException("LowerTriangle op []");

  std::size_t i(*(ij.begin())), j(*(ij.begin()+1));

  if(j<=i)
  {
    return data_[(i)*(i+1)/2 + j];
  }
  else
    return __empty_const__;
}

template <class Type>
inline Type&
numlib::LowerTriangle<Type>::operator[](
  std::initializer_list<std::size_t> ij)
{
  if(ij.size() != 2 || *(ij.begin()) >= N() || *(ij.begin()+1) >= M())
    throw RangeException("LowerTriangle op []");

    std::size_t i(*(ij.begin())), j(*(ij.begin()+1));

  if(j<=i)
  {
    return data_[(i)*(i+1)/2 + j];
  }
  else
  {
    dummy = 0;
    return dummy;
  }
}

// Clone idiom for copying
template <class Type>
std::shared_ptr<numlib::LowerTriangle<Type>>
numlib::LowerTriangle<Type>::clone() const
{
  return std::shared_ptr<LowerTriangle<Type>>(new LowerTriangle<Type>(*this));
}

template <class Type>
std::size_t
numlib::LowerTriangle<Type>::N() const
{
  return n_;
}

template <class Type>
std::size_t
numlib::LowerTriangle<Type>::M() const
{
  return n_;
}

template <class Type>
inline bool
numlib::LowerTriangle<Type>::checki(
    std::size_t const i) const
{
  return (n_)&&(i<n_);
}

template <class Type>
inline bool
numlib::LowerTriangle<Type>::checkj(
    std::size_t const j) const
{
  return (n_)&&(j<n_);
}

template <class Type>
void numlib::swap(
  LowerTriangle<Type> &d1,
  LowerTriangle<Type> &d2)
{
  using std::swap;
  std::swap(d1.data_,d2.data_);
  std::swap(d1.n_, d2.n_);
  return;
}

template <class Type>
void
numlib::LowerTriangle<Type>::print(
  std::ostream &out) const
{
  if(n_>0)
  {
    for(std::size_t i=0; i<n_; ++i)
    {
      for(std::size_t j=0; j<i+1; ++j)
      {
        out << std::left << std::setw(output::__width__)
            << std::setprecision(output::__precision__) <<  std::scientific
            << this->operator[]({i,j}) << ' ';
      }
      out << '\n';
    }
  }
  return;
}
