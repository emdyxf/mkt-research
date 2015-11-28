all : BUILD_OBJ

DATE=$(shell echo `date +'%Y%m%d'`)
TIME=$(shell echo `date +'%H%M%S'`)

PLATFORM = X64
C++ = g++ -rdynamic
C++FLAGS= -Wreturn-type -O2 -Wno-deprecated -Wno-unused-result -Wall

DEFINE  =       -DFOR_UNIX
DEFINE += -DBUILD_DATE="\"$(DATE)\"" -DBUILD_TIME="\"$(TIME)\""

INC	+= -I./includes
INC	+= -I./utils

OBJ = main.out

%.out: %.cpp
	$(C++) $(C++FLAGS) $(INC) $(DEFINE) -O2 $<  -o $(PLATFORM)/$@

clean: 
	$(RM) -rf $(PLATFORM)

MAKEDIR:
	-mkdir $(PLATFORM)

BUILD_OBJ: clean MAKEDIR $(OBJ)
