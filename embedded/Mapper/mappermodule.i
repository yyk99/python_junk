/* File : mappermodule.i */
%module example

%{
#include "Mapper.h"
#include "ControlCenter.h"
%}

/* Let's just grab the original header file here */
%include "ControlCenter.h"