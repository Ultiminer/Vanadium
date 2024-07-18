#ifndef COMPILER_H_
#define COMPILER_H_

#include "config.h"
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "text_methods.h"


template<typename T>
inline bool contains(const std::vector<T>& vec, const T& item)noexcept
{
    for(auto& el:vec)if(el==item)return true;
    return false; 
}

enum class TokenType{
NONE, 
LINT, 
LFLOAT,
LSTRING,
DEF_STR,
DEF_VOID,
DEF_INT8,
DEF_INT16,
DEF_INT32,
DEF_INT64,
DEF_UINT8,
DEF_UINT16,
DEF_UINT32,
DEF_UINT64,
DEF_FLOAT32,
DEF_FLOAT64,
DEF_MUT,
DEF_NAME,
DEF_CONST,
DEF_FUNCTION,
RETURN,
EXIT, 
STDOUT,
SEMICOLON,
ASSIGN_OPERATOR, 
PLUS_OPERATOR, 
MINUS_OPERATOR, 
MODULO_OPERATOR,
PROD_OPERATOR, 
DIV_OPERATOR,
GREATER_OPERATOR,
SMALLER_OPERATOR,
NOT_OPERATOR,
BRACKET_ON,
BRACKET_CLOSE, 
SQUARE_ON,
SQUARE_CLOSE, 
CURLY_ON,
CURLY_CLOSE,
ENTRY_POINT,
LINE_BREAK,
ASSERT,
INCLUDE,
COPY,
FOR,
WHILE,
STR_TO_INT,
STR_TO_FLOAT,
INT_TO_FLOAT,
INT_TO_STR,
FLOAT_TO_INT,
FLOAT_TO_STR,
STRUCT,
IFSTREAM,
OFSTERAM,
GETLINE
};
inline std::unordered_map<std::string,TokenType> trivialTokens={
{"i64",TokenType::DEF_INT64},{"i32",TokenType::DEF_INT32},{"i16",TokenType::DEF_INT16},{"i8",TokenType::DEF_INT8},
{"u64",TokenType::DEF_UINT64},{"u32",TokenType::DEF_UINT32},{"u16",TokenType::DEF_UINT16},{"u8",TokenType::DEF_UINT8},
{"f64",TokenType::DEF_FLOAT64},{"f32",TokenType::DEF_FLOAT32},{"mut",TokenType::DEF_MUT},{";",TokenType::SEMICOLON},
{"print",TokenType::STDOUT},{"=",TokenType::ASSIGN_OPERATOR},{"+",TokenType::PLUS_OPERATOR},{"-",TokenType::MINUS_OPERATOR},
{"*",TokenType::PROD_OPERATOR},{"/",TokenType::DIV_OPERATOR},{"CONST",TokenType::DEF_CONST},
{"{",TokenType::CURLY_ON},{"}",TokenType::CURLY_CLOSE},{"(",TokenType::BRACKET_ON},{")",TokenType::BRACKET_CLOSE}
,{"[",TokenType::SQUARE_ON},{"]",TokenType::SQUARE_CLOSE},{"fn",TokenType::DEF_FUNCTION},{"start",TokenType::ENTRY_POINT}
,{"return",TokenType::RETURN},{"\n",TokenType::LINE_BREAK},{"void",TokenType::DEF_VOID},{"str",TokenType::DEF_STR},
{">",TokenType::GREATER_OPERATOR},{"<",TokenType::SMALLER_OPERATOR},{"!",TokenType::NOT_OPERATOR},
{"assert",TokenType::ASSERT},{"import", TokenType::INCLUDE},{"copy", TokenType::COPY},
{"for",TokenType::FOR},{"while",TokenType::WHILE},{"%",TokenType::MODULO_OPERATOR},
{"str_to_int",TokenType::STR_TO_INT},{"str_to_float",TokenType::STR_TO_FLOAT},
{"float_to_int",TokenType::FLOAT_TO_INT},{"int_to_float",TokenType::INT_TO_FLOAT},
{"float_to_str",TokenType::FLOAT_TO_STR},{"int_to_str",TokenType::INT_TO_STR}
,{"struct",TokenType::STRUCT},{"inFile",TokenType::IFSTREAM},{"outFile",TokenType::OFSTERAM},{"get_line",TokenType::GETLINE}
};
struct Token{
TokenType t; 
std::string value; 
};
using TokenList=std::vector<Token>;
using SepList= std::vector<std::string>; 
using CCode=std::string; 

inline SepList seperate(const char* path)noexcept
{
    assert(path!=nullptr, "path was not set");
    std::ifstream in{path,std::ios::binary};
    std::string line=""; 
    std::string word=""; 
    SepList list; 
    bool comment=false;
    bool longComment=false;
    bool CPP=false;
    while(std::getline(in,line))
    {
        for(size_t i=0; i<line.size();i++)
        {
            if(line.at(i)=='\"'){list.push_back(word);word="";comment=!comment;};
            if(i+1<line.size()&&line.at(i)=='/'&&line.at(i+1)=='/')comment=true;
            if(i+1<line.size()&&line.at(i)=='/'&&line.at(i+1)=='*')longComment=true;
            if(i+1<line.size()&&line.at(i)=='*'&&line.at(i+1)=='/')longComment=false;
            if(i+2<line.size()&&line.at(i)=='*'&&line.at(i+1)=='|'&&line.at(i+2)=='|'){CPP=true;i+=3;}
            if(i+2<line.size()&&line.at(i)=='|'&&line.at(i+1)=='|'&&line.at(i+2)=='*'){CPP=false;i+=3;}

            if(comment||longComment||CPP)
            {
                word+=line.at(i);

                continue;
            }


            while(i<line.size()&&is_alpha_num(line.at(i)))
            {
                word+=line.at(i); 
                i++;
            }

            if(word.size()>0){list.push_back(word);word="";i--;}
            
            if(i<line.size()&&is_special(line.at(i)))
            word+=line.at(i); 
            
            if(word.size()>0){list.push_back(word);word="";}
        }
   
    comment=false;
    if(word.size()>0){list.push_back(word);word="";}
    else
    list.push_back("\n");
    line=""; 
    }
    in.close();

    return list; 
}

inline std::string TokenStr(const TokenType& tk)noexcept
{
    switch(tk)
    {
        case TokenType::ASSIGN_OPERATOR: return "=";
        case TokenType::PLUS_OPERATOR: return "+";
        case TokenType::DIV_OPERATOR: return "/";
        case TokenType::MINUS_OPERATOR: return "-";
        case TokenType::PROD_OPERATOR: return "*";
        case TokenType::BRACKET_ON: return "(";
        case TokenType::BRACKET_CLOSE: return ")";
        case TokenType::GREATER_OPERATOR: return ">";
        case TokenType::SMALLER_OPERATOR: return "<";
        case TokenType::NOT_OPERATOR: return "<";
        case TokenType::MODULO_OPERATOR: return "%";
        default: 
        return "";
    }

    return "";
}

inline TokenList tokenize(const char* path)noexcept
{
    const SepList& words=seperate(path); 
    assert(words.size()!=0,"No Tokenizable Words exist");
    TokenList tlist; 
    for(size_t i=0; i<words.size();++i)
    {
        if(trivialTokens.find(words.at(i))!=trivialTokens.end())
        {
            tlist.push_back({trivialTokens.at(words.at(i))});
            continue;
        }
        if(words.at(i).size()>0&&is_num(words.at(i).front()))
        {
            if(words.at(i).size()>1&&words.at(i).back()=='f')tlist.push_back({TokenType::LFLOAT,words.at(i).substr(0,words.size()-1)});
            else tlist.push_back({TokenType::LINT,words.at(i)});
            continue; 
        } 
        tlist.push_back({TokenType::DEF_NAME,words.at(i)});
    }
    return tlist; 
}

inline std::string get_token_var_modifier(const TokenList& list, size_t id)
{
if(id!=0&&list.at(id-1).t==TokenType::DEF_CONST)return "inline constexpr "; 
if(id==0||list.at(id-1).t!=TokenType::DEF_MUT)return "const "; 
return "";

}
inline std::string get_token_fn_modifier(const TokenList& list, size_t id)
{
if(id==0||list.at(id-1).t!=TokenType::DEF_MUT)return "inline constexpr "; 
return "inline ";

}



struct StateJob{
bool add_noexcept;
bool copy;
};
inline CCode parse(const std::string& path)noexcept
{
    const TokenList& tlist=tokenize(path.c_str());
    std::string cProgram="#include<iostream>\n#include<string>\n#include<fstream>\n using namespace std;\n ";
    std::string outVal="";
    std::vector<std::string> structKeys; 
    StateJob job{0};
    for(size_t i=0; i< tlist.size();++i)
    {
        switch(tlist.at(i).t)
        {
            case TokenType::LINE_BREAK: 
            cProgram+="\n"; 
            break; 
            case TokenType::COPY: 
            job.copy=true; 
            break; 
            case TokenType::DEF_VOID: 
            cProgram+="void "; 
            break; 
            case TokenType::DEF_FLOAT32: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="float "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::DEF_FLOAT64: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="double "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::DEF_INT32:
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="long int "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::DEF_INT16: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="int "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::DEF_INT64: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="long long int "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::DEF_INT8: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="char "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::DEF_UINT32: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="unsigned long int "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::DEF_UINT16: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="unsigned int "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::DEF_UINT64: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="unsigned long long int "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::DEF_UINT8: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="unsigned char "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break;
            case TokenType::DEF_STR: 
            cProgram+=get_token_var_modifier(tlist,i)+"std::string "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::OFSTERAM: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="std::ofstream "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::IFSTREAM: 
            cProgram+= get_token_var_modifier(tlist,i);
            cProgram+="std::ifstream "; 
            if(job.copy){job.copy=false;break;}
            if(job.add_noexcept)cProgram+="& ";
            break; 
            case TokenType::ASSIGN_OPERATOR: 
            cProgram+="="; 
            break; 
            case TokenType::PLUS_OPERATOR: 
            cProgram+="+"; 
            break; 
            case TokenType::MINUS_OPERATOR: 
            cProgram+="-"; 
            break;
            case TokenType::PROD_OPERATOR: 
            cProgram+="*"; 
            break;
            case TokenType::DIV_OPERATOR: 
            cProgram+="/"; 
            break;
            case TokenType::GREATER_OPERATOR: 
            cProgram+=">"; 
            break;
            case TokenType::SMALLER_OPERATOR: 
            cProgram+="<"; 
            break;
            case TokenType::NOT_OPERATOR: 
            cProgram+="!"; 
            break;
            case TokenType::MODULO_OPERATOR: 
            cProgram+="%"; 
            break;
            case TokenType::DEF_NAME: 
            cProgram+=tlist.at(i).value; 
            break;
            case TokenType::LINT:
            cProgram+=tlist.at(i).value; 
            break; 
            case TokenType::LFLOAT:
            cProgram+=tlist.at(i).value; 
            break; 
            case TokenType::SEMICOLON:
            cProgram+=";"; 
            break; 
            case TokenType::GETLINE:
            cProgram+="std::getline"; 
            break; 
            case TokenType::STDOUT: 
            outVal="";
            while(i<tlist.size()&&tlist.at(i).t!=TokenType::SEMICOLON){outVal+=tlist.at(i).value+TokenStr(tlist.at(i).t);i++;}
            cProgram+="std::cout<<"+outVal+"<<std::endl<<std::flush;\n";
            break; 
            case TokenType::STR_TO_INT: 
            outVal="";
            while(i<tlist.size()&&tlist.at(i).t!=TokenType::SEMICOLON){outVal+=tlist.at(i).value+TokenStr(tlist.at(i).t);i++;}
            cProgram+="std::atoi(("+outVal+").c_str());";
            break; 
            case TokenType::STR_TO_FLOAT: 
            outVal="";
            while(i<tlist.size()&&tlist.at(i).t!=TokenType::SEMICOLON){outVal+=tlist.at(i).value+TokenStr(tlist.at(i).t);i++;}
            cProgram+="std::atof(("+outVal+").c_str());";
            break; 
            case TokenType::INT_TO_FLOAT: 
            outVal="";
            while(i<tlist.size()&&tlist.at(i).t!=TokenType::SEMICOLON){outVal+=tlist.at(i).value+TokenStr(tlist.at(i).t);i++;}
            cProgram+="(float)("+outVal+");";
            break;
            case TokenType::FLOAT_TO_INT: 
            outVal="";
            while(i<tlist.size()&&tlist.at(i).t!=TokenType::SEMICOLON){outVal+=tlist.at(i).value+TokenStr(tlist.at(i).t);i++;}
            cProgram+="(int)("+outVal+");";
            break;
            case TokenType::INT_TO_STR: 
            outVal="";
            while(i<tlist.size()&&tlist.at(i).t!=TokenType::SEMICOLON){outVal+=tlist.at(i).value+TokenStr(tlist.at(i).t);i++;}
            cProgram+="std::to_string(("+outVal+"));";
            break;
            case TokenType::FLOAT_TO_STR: 
            outVal="";
            while(i<tlist.size()&&tlist.at(i).t!=TokenType::SEMICOLON){outVal+=tlist.at(i).value+TokenStr(tlist.at(i).t);i++;}
            cProgram+="std::to_string(("+outVal+"));";
            break;
            case TokenType::INCLUDE: 
            i++;
            if(tlist.at(i).value.find(".vnd") != std::string::npos)
            {
                cProgram+="#ifndef "+tlist.at(i).value+"\n#define "+tlist.at(i).value+" "+tlist.at(i).value+"\n";
                cProgram+=parse(tlist.at(i).value.c_str());
                cProgram+="#endif";
                break;  
            }
            cProgram+="#include \""+tlist.at(i).value+"\" ";
            break; 
            case TokenType::ASSERT: 
            outVal="";
            while(i<tlist.size()&&tlist.at(i).t!=TokenType::SEMICOLON){outVal+=tlist.at(i).value+TokenStr(tlist.at(i).t);i++;}
            cProgram+="if(!("+outVal+")){\n std::cout<<\"assert called, condition: "+outVal+" failed\"<<std::endl<<std::flush;\n exit(EXIT_FAILURE); \n}\n";
            break; 
            case TokenType::SQUARE_ON:
            cProgram+="[";
            break; 
            case TokenType::SQUARE_CLOSE:
            cProgram+="]";
            break; 
            case TokenType::BRACKET_ON:
            cProgram+="(";
            break; 
            case TokenType::BRACKET_CLOSE:
            cProgram+=")";
            if(job.add_noexcept){cProgram+="noexcept";job.add_noexcept=false;}
            break; 
            case TokenType::CURLY_ON:
            cProgram+="{";
            break;
            case TokenType::CURLY_CLOSE:
            cProgram+="}";
            break; 
            case TokenType::ENTRY_POINT:
            cProgram+="main";
            break;
            case TokenType::RETURN:
            assert(i+3<tlist.size(),"Return not well defined!");
            cProgram+="return ";
            break;
            case TokenType::EXIT:
            assert(i+3<tlist.size(),"Return not well defined!");
            cProgram+="exit";
            break;
            case TokenType::DEF_FUNCTION:
            if(tlist.at(i+1).t==TokenType::ENTRY_POINT){cProgram+="int ";break;}

            cProgram+= get_token_fn_modifier(tlist,i);
            if(tlist.at(i+2).t==TokenType::BRACKET_ON)cProgram+="auto ";
            job.add_noexcept=true;
            break;  
            case TokenType::FOR:
            cProgram+="for";
            break; 
            case TokenType::WHILE:
            cProgram+="while";
            break; 
            case TokenType::STRUCT:
            cProgram+="struct ";
            i++;
            cProgram+=tlist.at(i).value;
     
            structKeys.push_back(tlist.at(i).value);
            break; 
            default:
            break;
        }
        

        if(i+1<tlist.size()&&contains(structKeys,tlist.at(i+1).value)){
            i++;
        cProgram+= get_token_var_modifier(tlist,i);
        cProgram+=tlist.at(i).value+" ";
        if(job.copy){job.copy=false;break;}
        if(job.add_noexcept)cProgram+="& ";
        
        }
    }

    std::ofstream out{path+".cpp"};
    out<<cProgram; 
    out.close();
    return cProgram; 
}

#endif

