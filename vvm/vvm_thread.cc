/*
 * Copyright (c) 1998 Stephen Williams (steve@icarus.com)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
#if !defined(WINNT)
#ident "$Id: vvm_thread.cc,v 1.2 1999/12/12 19:47:54 steve Exp $"
#endif

# include  "vvm.h"
# include  "vvm_thread.h"


class delay_event : public vvm_event {

    public:
      delay_event(vvm_thread*thr) : thr_(thr) { }
      void event_function() { while (thr_->go()) /* empty */; }
    private:
      vvm_thread*thr_;
};

vvm_thread::vvm_thread()
{
      thread_yield();
}

vvm_thread::~vvm_thread()
{
}

void vvm_thread::thread_yield(unsigned long delay)
{
      delay_event*ev = new delay_event(this);
      ev -> schedule(delay);
}

/*
 * $Log: vvm_thread.cc,v $
 * Revision 1.2  1999/12/12 19:47:54  steve
 *  Remove the useless vvm_simulation class.
 *
 * Revision 1.1  1998/11/09 23:44:11  steve
 *  Add vvm library.
 *
 */

