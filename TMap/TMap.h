#pragma once
#include <iostream>
#include <stack>
#include <string.h>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

template<class TK, class TV>
class TMap;

template<class TK, class TV>
class TSortMap;

template<class TK, class TV>
class TNode
{
protected:
  TK key;
  TV val;
public:
  TNode(TK k = 0, TV v = 0);
  TNode(const TNode& p);

  TK GetKey();
  TV GetVal();

  void SetKey(TK k);
  void SetVal(TV v);

  TNode& operator =(const TNode& p);

  bool operator == (TNode& p);
  bool operator > (TNode& p);
  bool operator < (TNode& p);

  friend class TMap<TK, TV>;
  friend class TSortMap<TK, TV>;
  //גûגמה ג פאיכ
  template<class TK, class TV>
  friend ofstream& operator<<(ofstream& out, const TNode<TK, TV>& N);
};

template<class TK, class TV>
class TMap
{
protected:
  TNode<TK, TV>* mas;
  int size;
  int count;

  void Resize(int newSize);

public:
  TMap(int size_);
  TMap(const TMap& p);
  virtual ~TMap();

  virtual TV& operator[](TK i);

  virtual TV Find(TK k);
  virtual void Delete(TK k);
  virtual void Add(TK k, TV v);

  friend class TNode<TK, TV>;
  //גûגמה ג פאיכ
  template<class TK, class TV>
  friend ofstream& operator<< (ofstream& out, TMap<TK, TV>& M);
};

template <class TK, class TV>
class TIterSortMap;

template <class TK, class TV>
class TSortMap : public TMap<TK, TV>
{
public:
  TSortMap(int size_ = 1000);
  TSortMap(int size_, TNode<TK, TV>* m);
  TSortMap(const TSortMap& p);

  virtual TV& operator[](TK i);

  virtual TV Find(TK k);
  virtual void Delete(TK k);
  virtual void Add(TK k, TV v);

  friend class TNode<TK, TV>;
  friend class TIterSortMap<TK, TV>;

  TIterSortMap<TK, TV> GetBegin();
};

template <class TK, class TV>
class TIterSortMap
{
protected:
  TSortMap<TK, TV>& map;
  int index;
public:
  TIterSortMap(TSortMap<TK, TV>& p, int ind = 0);
  void GoNext();
  void GoPrev();
  TNode<TK, TV>& Get();
  bool IsGoNext();
  bool IsGoPrev();
  bool operator==(TIterSortMap<TK, TV> iter);
};

// Node

template<class TK, class TV>
TNode<TK, TV>::TNode(TK k, TV v)
{
  key = k;
  val = v;
}

template<class TK, class TV>
TNode<TK, TV>::TNode(const TNode& p)
{
  this->key = p.key;
  this->val = p.val;
}

template<class TK, class TV>
TK TNode<TK, TV>::GetKey()
{
  return key;
}

template<class TK, class TV>
TV TNode<TK, TV>::GetVal()
{
  return val;
}

template<class TK, class TV>
void TNode<TK, TV>::SetKey(TK k)
{
  key = k;
}

template<class TK, class TV>
void TNode<TK, TV>::SetVal(TV v)
{
  val = v;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator == (TNode& p)
{
  return this->key == p.key;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator > (TNode& p)
{
  return this->key > p.key;
}

template<class TK, class TV>
bool TNode<TK, TV>::operator < (TNode& p)
{
  return this->key < p.key;
}

template<class TK, class TV>
TNode<TK, TV>& TNode<TK, TV>::operator =(const TNode<TK, TV>& p)
{
  this->key = p.key;
  this->val = p.val;
  return *this;
}

template<class TK, class TV>
ofstream& operator<<(ofstream& out, const TNode<TK, TV>& N)
{
  out << N.key << ": " << N.val;
  return out;
}

// Map

template<class TK, class TV>
void TMap<TK, TV>::Resize(int newSize)
{
  if (newSize <= 0)
    throw - 1;

  TNode<TK, TV>* newMas = new TNode<TK, TV>[newSize];
  for (int i = 0; i < min(newSize, size); i++)
  {
    newMas[i] = mas[i];
  }

  delete[] mas;
  mas = newMas;
  size = newSize;
}

template<class TK, class TV>
TMap<TK, TV>::TMap(int size_)
{
  if (size_ <= 0)
    throw - 1;
  this->size = size_;
  this->count = 0;
  this->mas = new TNode<TK, TV>[size];
}

template<class TK, class TV>
TMap<TK, TV>::TMap(const TMap<TK, TV>& p)
{
  this->size = p.size;
  this->count = p.count;
  this->mas = new TNode<TK, TV>[p.size];
  for (int i = 0; i < p.count; i++)
    this->mas[i] = p.mas[i];
}

template <class TK, class TV>
TMap<TK, TV>::~TMap() {
  if (mas != 0)
    delete[] mas;
  mas = 0;
  size = 0;
  count = 0;
}

template<class TK, class TV>
TV& TMap<TK, TV>::operator[](TK i)
{
  for (size_t j = 0; j < count; j++)
  {
    if (mas[j].key == i)
    {
      return mas[j].val;
    }
  }
  count++;
  if (count == size)
    Resize(2 * size);
  mas[count - 1].key = i;
  mas[count - 1].val = '0';
  return mas[count - 1].val;
}

template<class TK, class TV>
TV TMap<TK, TV>::Find(TK k)
{
  for (int i = 0; i < count; i++)
  {
    if (mas[i].key == k)
      return mas[i].val;
  }

  throw - 1;
}

template<class TK, class TV>
void TMap<TK, TV>::Delete(TK k)
{
  for (int i = 0; i < count; i++)
  {
    if (mas[i].key == k)
    {
      for (int j = i; j < count - 1; j++)
        mas[j] = mas[j + 1];
      count--;
    }
  }
}

template<class TK, class TV>
void TMap<TK, TV>::Add(TK k, TV v)
{
  mas[count].key = k;
  mas[count].val = v;
  count++;
  if (count == size)
    Resize(size * 2);
}

template<class TK, class TV>
ofstream& operator<<(ofstream& out, TMap<TK, TV>& M)
{
  for (int i = 0; i < M.count; i++)
    out << M.mas[i] << ' ';
  return out;
}

// SortMap

template <class TK, class TV>
TSortMap<TK, TV>::TSortMap(int size_, TNode<TK, TV>* m)
{
  this->mas = new TNode<TK, TV>[size_];
  for (int i = 0; i < size_; i++)
    this->mas[i] = m[i];

  TNode<TK, TV> tmp;
  for (int i = size_ - 1; i > 0; i--)
    for (int j = 0; j < i; j++)
      if (this->mas[j] < this->mas[j + 1])
      {
        tmp = this->mas[j];
        this->mas[j] = this->mas[j + 1];
        this->mas[j + 1] = tmp;
      }
}

template <class TK, class TV>
TSortMap<TK, TV>::TSortMap(int size_) :TMap<TK, TV>::TMap(size_) {}

template <class TK, class TV>
TSortMap<TK, TV>::TSortMap(const TSortMap& p) : TMap<TK, TV>::TMap(p) {}

template <class TK, class TV>
TV& TSortMap<TK, TV>::operator[](TK i)
{
  int l = 0;
  int r = this->count;

  while (r - l > 1)
  {
    int c = (l + r) / 2;
    if (this->mas[c].key == i)
      return this->mas[c].val;
    if (this->mas[c].key > i)
    {
      r = c;
    }
    else
    {
      l = c;
    }
  }
  if (this->mas[l].key == i)
    return this->mas[l].val;
  else
    throw - 1;
}

template <class TK, class TV>
TV TSortMap<TK, TV>::Find(TK k)
{
  int l = 0, r = this->count;
  int c;
  while (l < r)
  {
    c = (l + r) / 2;
    if (k == this->mas[c].key)
      return this->mas[c].val;
    if (k < this->mas[c].key)
    {
      r = c;
    }
    else
    {
      l = c;
    }
  }
  throw - 1;
}

template <class TK, class TV>
void TSortMap<TK, TV>::Delete(TK k)
{
  int ind = -1;
  int l = 0, r = this->count;
  while (r - l > 1)
  {
    int c = (l + r) / 2;
    if (this->mas[c].key == k)
    {
      ind = c;
      break;
    }
    if (this->mas[c].key > k)
      r = c;
    else
      l = c;
  }
  if (ind == -1)
  {
    if (l == 0)
      ind = l;
    else if (r == count)
      ind = r;
    else
      ind = l;
  }
  if (this->mas[ind].key != k)
    throw - 1;

  for (int i = ind; i < this->count - 1; i++)
    this->mas[i] = this->mas[i + 1];

  this->count--;
}

template <class TK, class TV>
void TSortMap<TK, TV>::Add(TK k, TV v)
{
  int ind = -1;
  TNode<TK, TV> node(k, v);
  int l = 0, r = this->count;
  while (r - l > 1)
  {
    int c = (l + r) / 2;
    if (this->mas[c] == node)
    {
      ind = c;
      break;
    }
    if (this->mas[c] > node)
      r = c;
    else
      l = c;
  }
  if (ind == -1)
  {
    if (l == 0 && r == count)
    {
      if (this->mas[l] > node)
        ind = l;
      else
        ind = r;
    }
    else
      if (l == 0)
        ind = l;
      else if (r == count)
        ind = r;
      else
        ind = l;
  }

  this->count++;

  if (this->count >= this->size)
    TMap<TK, TV>::Resize(2 * this->size);

  for (int i = this->count - 1; i > ind; i--)
  {
    this->mas[i] = this->mas[i - 1];
  }
  this->mas[ind] = node;
}

template<class TK, class TV>
TIterSortMap<TK, TV> TSortMap<TK, TV>::GetBegin()
{
  return TIterSortMap<TK, TV>(*this, 0);
}

// TIterSortMap

template<class TK, class TV>
TIterSortMap<TK, TV>::TIterSortMap(TSortMap<TK, TV>& p, int ind) :map(p), index(ind) {}

template<class TK, class TV>
void TIterSortMap<TK, TV>::GoNext()
{
  if (IsGoNext())
    this->index++;
  else
    throw - 1;
}

template<class TK, class TV>
void TIterSortMap<TK, TV>::GoPrev()
{
  if (IsGoPrev())
    this->index--;
  else
    throw - 1;
}

template<class TK, class TV>
TNode<TK, TV>& TIterSortMap<TK, TV>::Get()
{
  return this->map.mas[this->index];
}

template<class TK, class TV>
bool TIterSortMap<TK, TV>::IsGoNext()
{
  if (this->index + 1 < this->map.count)
    return true;
  return false;
}

template<class TK, class TV>
bool TIterSortMap<TK, TV>::IsGoPrev()
{
  if (this->index - 1 > -1)
    return true;
  return false;
}

template<class TK, class TV>
bool TIterSortMap<TK, TV>::operator==(TIterSortMap<TK, TV> iter)
{
  if (this->map == iter.map && this->index == iter.index)
    return true;
  return false;
}