#include <windows.h>
#include <locale.h>
#include <vector>
#include <iostream>
#include <string>



class big_integer
{
public:
    big_integer():number(NULL) {};
    big_integer(std::vector<int> vec_a) : number(std::move(vec_a)) {};
  
    big_integer(std::string a) 
    { for (const auto ex : a)
        {
        number.push_back(ex-48);
        } 
    };

    big_integer(big_integer&& a) noexcept { *this = a; }

    ~big_integer() {};


  big_integer& operator = (big_integer& other) 
    {
        return *this = other;
    }

  big_integer& operator = (big_integer&& other) noexcept
  {
      this->number=other.number;
      return *this;
  }

  big_integer operator +( big_integer& other)
  {
   std::vector<int> left=(this->number);
   std::vector<int> right= (other.number);
   std::vector<int> sum;

   int buf = 0;
   int up = 0;
   int left_size = left.size();
   int right_size = right.size();
   int size_max = max(left_size, right_size);

   if (left_size == right_size) 
   {
       
   }
   else if (left_size < right_size)
   {
       int adding_zeros = right_size - left_size;
       for (int i = 0; i < adding_zeros; ++i)
       {
           left.insert(left.begin(), 0);
       }
   }
   else
   {
       int adding_zeros = left_size - right_size;
       for (int i = 0; i < adding_zeros; ++i)
       {
           right.insert(right.begin(), 0);
       }
   }

   for (int i = size_max - 1; i >= 0; --i)
   {

       buf = (left[i]) +  (right[i]) + up;
          
       if (buf < 10) 
       { sum.push_back(buf); up = 0; }
       else if (buf == 10) 
       {
           sum.push_back(0); up = 1;
       }
       else
       {
           sum.push_back(buf - 10); up = 1;
       }

       if (i == 0 && up == 1) { sum.push_back(up); }

   }
       std::reverse(sum.begin(), sum.end());
   return big_integer(sum);
  }

    big_integer operator *(big_integer& other ) 
  {
      std::vector<int>top;
      std::vector<int>down;
      int raz = 0;
      int des = 0;
      
      int size_max = max(this->number.size(), other.number.size());
      int size_min = min(this->number.size(), other.number.size());

      if (this->number.size() > other.number.size()) { top = (this->number); down = (other.number); }
      else { top = (other.number); down =(this->number); }

      std::vector<std::vector<int>> mas_vec;
      mas_vec.resize(size_max);
      for (int i = 0; i < size_min; ++i)
      {
          int buf = 0;
          int rec = 0;

          for (int j = 0; j < size_max; ++j)
          {
              buf = (top[size_max-1-j] * down[size_min-1 - i]) + des;
              if (buf > 10) 
              {
              rec = buf % 10;
              des = (buf - rec) / 10; 
              }
              else if (buf == 10)
              {
                  rec = 0;
                  des = 1; 
              }
              else // buf<10
              {
                  rec = buf;
                  des = 0;
              }

              mas_vec[i].insert(mas_vec[i].begin(), rec);  
              
              if (size_max - 1 == j && des != 0) { mas_vec[i].insert(mas_vec[i].begin(), des); des = 0; }////////////////////////////////////////вооООООТТТ ТУТУТУТТУТТУ ОШИИИБКА ВАААААЛЕЕЕРАААА
              if (size_max - 1 == j)
              { for (int x = 0; x < raz; ++x) { mas_vec[i].push_back(0); } }
          }
          ++raz;
      }

         big_integer mult;  
        
         for (int i = 0; i < mas_vec.size(); i++) 
      {
      std::vector<int> a = (mas_vec[i]);

          
       
         big_integer buf_mult(a);
        
         mult = mult + buf_mult;

      }

       return  mult;
  }

 friend std::ostream& operator << (std::ostream &out, big_integer& a)
  {
      for (auto const ex : a.number)
      {
             std::cout << ex;
      }
      return out;
  }

private:
    std::vector<int> number;
};

 
 
int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

    auto number1 = big_integer("10");
    auto number2 = big_integer("10");
    auto result = number1 + number2;
    auto result2 = number1 * number2;
    auto result3 = number1 * result2;
  std::cout <<"operator * " << result2 <<" operator r3 * " << result3 << "  operator +" << result; // 193099
    return 0;
}