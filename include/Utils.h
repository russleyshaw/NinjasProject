#ifndef EXCEPTION_H
#define EXCEPTION_H

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)


#define GEN_EXCEPT(msg) "ERROR: " __FILE__ ":" LINE_STRING " - " msg

#endif
