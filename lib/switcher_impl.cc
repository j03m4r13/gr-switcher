/* -*- c++ -*- */
/*
 * Copyright 2021 gr-switcher jaliling.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <gnuradio/gr_complex.h>
#include "switcher_impl.h"

namespace gr {
  namespace switcher {

    switcher::sptr
    switcher::make()
    {
      return gnuradio::get_initial_sptr
        (new switcher_impl());
    }


    /*
     * The private constructor
     */
    switcher_impl::switcher_impl()
      : gr::block("switcher",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
      d_antenna_offset = 1;
    }

    /*
     * Our virtual destructor.
     */
    switcher_impl::~switcher_impl()
    {
    }

    void
    switcher_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    switcher_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float *out = (float *) output_items[0];

      for(int i = 0; i < noutput_items; i++) {
        add_item_tag(0,
            nitems_written(0) + i,
            pmt::mp("Ant:"),
            pmt::from_long(d_antenna_offset)
        );

        out[i] = in[i];
        if(d_antenna_offset < 8) d_antenna_offset++;
        else d_antenna_offset = 1;
      }

      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace switcher */
} /* namespace gr */
