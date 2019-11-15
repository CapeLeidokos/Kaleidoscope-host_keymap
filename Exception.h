#pragma once

#include <sstream>
#include <exception>

class Exception
{
   public:
      
      ~Exception() noexcept(false) {
         throw std::runtime_error{s_.str()};
      }
      
      template<typename _T>
      Exception &operator<<(const _T &t) {
         s_ << t;
         return *this;
      }
      
   private:
      
      std::ostringstream s_;
};
