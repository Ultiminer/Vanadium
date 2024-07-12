#ifndef TEXT_METHODS_H_
#define TEXT_METHODS_H_

inline constexpr bool is_num(char c)noexcept
{
    return (c>45)&&(c<58); 
}
inline constexpr bool is_alpha(char c)noexcept
{
    return ((c>64)&&(c<91))||((c>96)&&(c<123))||c=='_'; 
}
inline constexpr bool is_alpha_num(char c)noexcept
{
    return is_num(c)||is_alpha(c); 
}
inline constexpr bool is_ignore(char c)noexcept
{
    return (c<'!');
}
inline constexpr bool is_special(char c)noexcept
{
    return (c=='\n')||((!is_ignore(c))&&(!is_alpha_num(c))); 
}




#endif