#include "TextUtil.h"

namespace TextUtil{
  String toAscii(const String& in){
    String out;
    out.reserve(in.length());

    for(size_t i = 0; i< in.length(); i++){
      char c = in[i];

      if((c>=32 && c <= 126) || c == '\n' || c == '\r' || c== '\t'){
        out += c;
      }
    }
    return out;
  }
}
