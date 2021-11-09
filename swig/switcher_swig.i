/* -*- c++ -*- */

#define SWITCHER_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "switcher_swig_doc.i"

%{
#include "switcher/switcher.h"
%}

%include "switcher/switcher.h"
GR_SWIG_BLOCK_MAGIC2(switcher, switcher);
