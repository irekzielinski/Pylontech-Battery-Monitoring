#ifndef circ_buffer_h
#define circ_buffer_h

#include <stdlib.h>

/// <summary>
/// This class allows a fixed size circular buffer.
/// When push_back is called, oldest data is overwritten.
/// Does not use any dynamic allocators.
/// </summary>
template <class ItemType, int elementCnt> class circular_buffer
{
private:
  ItemType m_arr[elementCnt];
  int m_writePos;
  int m_size;

  void advanceWritePos()
  {
    if(m_size < elementCnt)
    {
      m_size++;
    }

    m_writePos++;
    if(m_writePos >= elementCnt)
    {
      m_writePos = 0;
    }
  }

  circular_buffer(const circular_buffer<ItemType, elementCnt>& rhs);
public:
  circular_buffer()
  {
    clear();
  }
  
  void operator=(const circular_buffer<ItemType, elementCnt>& rhs)
  {
    memcpy(m_arr, rhs.m_arr, sizeof(m_arr));
    m_size = rhs.m_size;
    m_writePos = rhs.m_writePos;
  }

  void push_back(const ItemType& item)
  {
    m_arr[m_writePos] = item;
    advanceWritePos();
  }
  
  void clear()
  {
    memset(m_arr,0,sizeof(m_arr));
    m_size = m_writePos = 0;
  }

  void sort()
  {
    if (size() < 2)
      return;
    
    bool swapped;
    do
    {
      swapped = false;
      for(int ix=0; ix<size()-1; ix++)
      {
        if(at(ix) > at(ix+1))
        {
          ItemType tmp = at(ix);
          at(ix) = at(ix+1);
          at(ix+1) = tmp;
          swapped = true;
        }
      }

    }while(swapped);
  }

  int size() const { return m_size; }
  bool isFull() const { return size() == elementCnt; }
  ItemType& operator[](int pos) {return at(pos);}

  ItemType& at(int pos) 
  {
    if(m_size < elementCnt)
    {
      return m_arr[pos];
    }

    int readPos = m_writePos + pos;
    if(readPos >= elementCnt)
    {
      readPos -= elementCnt;
    }

    return m_arr[readPos];
  }

#if _DEBUG_ENABLED
  void print() 
  {
    printf("---\n");
    for(int i=0; i<size(); i++)
    {
      printf("%d = %d\n", i, at(i));
    }
  }
#endif
};

#endif //circ_buffer_h