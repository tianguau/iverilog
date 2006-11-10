/*
 * Copyright (c) 1998-2005 Stephen Williams (steve@icarus.com)
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
#ifdef HAVE_CVS_IDENT
#ident "$Id: emit.cc,v 1.88 2006/11/10 05:44:44 steve Exp $"
#endif

# include "config.h"

# include  <iostream>

/*
 * The emit function is called to generate the output required of the
 * target.
 */
# include  "target.h"
# include  "netlist.h"
# include  <typeinfo>
# include  <cassert>

bool NetNode::emit_node(struct target_t*tgt) const
{
      cerr << "EMIT: Gate type? " << typeid(*this).name() << endl;
      return false;
}

bool NetLogic::emit_node(struct target_t*tgt) const
{
      tgt->logic(this);
      return true;
}

bool NetUDP::emit_node(struct target_t*tgt) const
{
      tgt->udp(this);
      return true;
}

bool NetAddSub::emit_node(struct target_t*tgt) const
{
      tgt->lpm_add_sub(this);
      return true;
}

bool NetCaseCmp::emit_node(struct target_t*tgt) const
{
      tgt->net_case_cmp(this);
      return true;
}

bool NetCLShift::emit_node(struct target_t*tgt) const
{
      tgt->lpm_clshift(this);
      return true;
}

bool NetCompare::emit_node(struct target_t*tgt) const
{
      tgt->lpm_compare(this);
      return true;
}

bool NetConcat::emit_node(struct target_t*tgt) const
{
      return tgt->concat(this);
}

bool NetConst::emit_node(struct target_t*tgt) const
{
      return tgt->net_const(this);
}

bool NetDivide::emit_node(struct target_t*tgt) const
{
      tgt->lpm_divide(this);
      return true;
}

bool NetFF::emit_node(struct target_t*tgt) const
{
      tgt->lpm_ff(this);
      return true;
}

bool NetLiteral::emit_node(struct target_t*tgt) const
{
      return tgt->net_literal(this);
}

bool NetModulo::emit_node(struct target_t*tgt) const
{
      tgt->lpm_modulo(this);
      return true;
}

bool NetMult::emit_node(struct target_t*tgt) const
{
      tgt->lpm_mult(this);
      return true;
}

bool NetMux::emit_node(struct target_t*tgt) const
{
      tgt->lpm_mux(this);
      return true;
}

bool NetPartSelect::emit_node(struct target_t*tgt) const
{
      return tgt->part_select(this);
}

bool NetRamDq::emit_node(struct target_t*tgt) const
{
      tgt->lpm_ram_dq(this);
      return true;
}

bool NetReplicate::emit_node(struct target_t*tgt) const
{
      return tgt->replicate(this);
}

bool NetSignExtend::emit_node(struct target_t*tgt) const
{
      return tgt->sign_extend(this);
}

bool NetUReduce::emit_node(struct target_t*tgt) const
{
      return tgt->ureduce(this);
}

bool NetSysFunc::emit_node(struct target_t*tgt) const
{
      return tgt->net_sysfunction(this);
}

bool NetUserFunc::emit_node(struct target_t*tgt) const
{
      return tgt->net_function(this);
}

bool NetBUFZ::emit_node(struct target_t*tgt) const
{
      return tgt->bufz(this);
}

bool NetProcTop::emit(struct target_t*tgt) const
{
      return tgt->process(this);
}

bool NetProc::emit_proc(struct target_t*tgt) const
{
      cerr << "EMIT: Proc type? " << typeid(*this).name() << endl;
      return false;
}

bool NetAssign::emit_proc(struct target_t*tgt) const
{
      tgt->proc_assign(this);
      return true;
}

bool NetAssignNB::emit_proc(struct target_t*tgt) const
{
      tgt->proc_assign_nb(this);
      return true;
}

bool NetBlock::emit_proc(struct target_t*tgt) const
{
      return tgt->proc_block(this);
}

bool NetCase::emit_proc(struct target_t*tgt) const
{
      tgt->proc_case(this);
      return true;
}

bool NetCAssign::emit_proc(struct target_t*tgt) const
{
      return tgt->proc_cassign(this);
}

bool NetCondit::emit_proc(struct target_t*tgt) const
{
      return tgt->proc_condit(this);
}

bool NetDeassign::emit_proc(struct target_t*tgt) const
{
      return tgt->proc_deassign(this);
}

bool NetDisable::emit_proc(struct target_t*tgt) const
{
      return tgt->proc_disable(this);
}

bool NetForce::emit_proc(struct target_t*tgt) const
{
      return tgt->proc_force(this);
}

bool NetForever::emit_proc(struct target_t*tgt) const
{
      tgt->proc_forever(this);
      return true;
}

bool NetPDelay::emit_proc(struct target_t*tgt) const
{
      return tgt->proc_delay(this);
}

bool NetPDelay::emit_proc_recurse(struct target_t*tgt) const
{
      if (statement_) return statement_->emit_proc(tgt);
      return true;
}

bool NetRelease::emit_proc(struct target_t*tgt) const
{
      return tgt->proc_release(this);
}

bool NetRepeat::emit_proc(struct target_t*tgt) const
{
      tgt->proc_repeat(this);
      return true;
}

bool NetSTask::emit_proc(struct target_t*tgt) const
{
      tgt->proc_stask(this);
      return true;
}

bool NetUTask::emit_proc(struct target_t*tgt) const
{
      tgt->proc_utask(this);
      return true;
}

bool NetWhile::emit_proc(struct target_t*tgt) const
{
      tgt->proc_while(this);
      return true;
}

void NetBlock::emit_recurse(struct target_t*tgt) const
{
      if (last_ == 0)
	    return;

      NetProc*cur = last_;
      do {
	    cur = cur->next_;
	    cur->emit_proc(tgt);
      } while (cur != last_);
}

bool NetCondit::emit_recurse_if(struct target_t*tgt) const
{
      if (if_)
	    return if_->emit_proc(tgt);
      else
	    return true;
}

bool NetCondit::emit_recurse_else(struct target_t*tgt) const
{
      if (else_)
	    return else_->emit_proc(tgt);
      else
	    return true;
}

bool NetEvProbe::emit_node(struct target_t*tgt) const
{
      tgt->net_probe(this);
      return true;
}

bool NetEvTrig::emit_proc(struct target_t*tgt) const
{
      return tgt->proc_trigger(this);
}

bool NetEvWait::emit_proc(struct target_t*tgt) const
{
      return tgt->proc_wait(this);
}

bool NetEvWait::emit_recurse(struct target_t*tgt) const
{
      if (!statement_) return true;
      return statement_->emit_proc(tgt);
}

void NetForever::emit_recurse(struct target_t*tgt) const
{
      if (statement_)
	    statement_->emit_proc(tgt);
}

void NetRepeat::emit_recurse(struct target_t*tgt) const
{
      if (statement_)
	    statement_->emit_proc(tgt);
}

void NetScope::emit_scope(struct target_t*tgt) const
{
      tgt->scope(this);

      for (NetEvent*cur = events_ ;  cur ;  cur = cur->snext_)
	    tgt->event(cur);

      for (NetScope*cur = sub_ ;  cur ;  cur = cur->sib_)
	    cur->emit_scope(tgt);

      if (signals_) {
	    NetNet*cur = signals_->sig_next_;
	    do {
		  tgt->signal(cur);
		  cur = cur->sig_next_;
	    } while (cur != signals_->sig_next_);

	      /* Run the signals again, but this time to connect the
	         delay paths. This is done as a second pass because
	         the paths reference other signals that may be later
	         in the list. We can do it here becase delay paths are
	         always connected within the scope. */
	    cur = signals_->sig_next_;
	    do {
		  tgt->signal_paths(cur);
		  cur = cur->sig_next_;
	    } while (cur != signals_->sig_next_);
      }

      if (memories_) {
	    NetMemory*cur = memories_->snext_;
	    do {
		  tgt->memory(cur);
		  cur = cur->snext_;
	    } while (cur != memories_->snext_);
      }
}

bool NetScope::emit_defs(struct target_t*tgt) const
{
      bool flag = true;

      switch (type_) {
	  case MODULE:
	    for (NetScope*cur = sub_ ;  cur ;  cur = cur->sib_)
		  flag &= cur->emit_defs(tgt);
	    break;

	  case FUNC:
	    flag &= tgt->func_def(this);
	    break;
	  case TASK:
	    tgt->task_def(this);
	    break;
	  default:  /* BEGIN_END and FORK_JOIN, do nothing */
	    break;
      }

      return flag;
}

void NetWhile::emit_proc_recurse(struct target_t*tgt) const
{
      proc_->emit_proc(tgt);
}

int Design::emit(struct target_t*tgt) const
{
      int rc = 0;

      if (tgt->start_design(this) == false)
	    return -2;

	// enumerate the scopes
      for (list<NetScope*>::const_iterator scope = root_scopes_.begin();
	   scope != root_scopes_.end(); scope++)
	    (*scope)->emit_scope(tgt);


	// emit nodes
      bool nodes_rc = true;
      if (nodes_) {
	    NetNode*cur = nodes_->node_next_;
	    do {
		  nodes_rc = nodes_rc && cur->emit_node(tgt);
		  cur = cur->node_next_;
	    } while (cur != nodes_->node_next_);
      }


	// emit task and function definitions
      bool tasks_rc = true;
      for (list<NetScope*>::const_iterator scope = root_scopes_.begin();
	   scope != root_scopes_.end(); scope++)
	    tasks_rc &= (*scope)->emit_defs(tgt);


	// emit the processes
      bool proc_rc = true;
      for (const NetProcTop*idx = procs_ ;  idx ;  idx = idx->next_)
	    proc_rc &= idx->emit(tgt);

      rc = tgt->end_design(this);

      if (nodes_rc == false)
	    return -1;
      if (tasks_rc == false)
	    return -2;
      if (proc_rc == false)
	  return -3;

      return rc;
}

void NetEBinary::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_binary(this);
}

void NetEConcat::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_concat(this);
}

void NetEConst::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_const(this);
}

void NetEConstParam::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_param(this);
}

void NetECReal::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_creal(this);
}

void NetECRealParam::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_rparam(this);
}

void NetEMemory::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_memory(this);
}

void NetEParam::expr_scan(struct expr_scan_t*tgt) const
{
      cerr << get_line() << ":internal error: unexpected NetEParam."
	   << endl;
}

void NetEEvent::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_event(this);
}

void NetEScope::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_scope(this);
}

void NetESelect::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_select(this);
}

void NetESFunc::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_sfunc(this);
}

void NetEUFunc::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_ufunc(this);
}

void NetESignal::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_signal(this);
}

void NetETernary::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_ternary(this);
}

void NetEUnary::expr_scan(struct expr_scan_t*tgt) const
{
      tgt->expr_unary(this);
}

int emit(const Design*des, const char*type)
{
      for (unsigned idx = 0 ;  target_table[idx] ;  idx += 1) {
	    const struct target*tgt = target_table[idx];
	    if (strcmp(tgt->name, type) == 0)
		  return des->emit(tgt->meth);

      }

      cerr << "error: Code generator type " << type
	   << " not found." << endl;
      return -1;
}


/*
 * $Log: emit.cc,v $
 * Revision 1.88  2006/11/10 05:44:44  steve
 *  Process delay paths in second path over signals.
 *
 * Revision 1.87  2006/06/18 04:15:50  steve
 *  Add support for system functions in continuous assignments.
 *
 * Revision 1.86  2005/07/11 16:56:50  steve
 *  Remove NetVariable and ivl_variable_t structures.
 *
 * Revision 1.85  2005/07/07 16:22:49  steve
 *  Generalize signals to carry types.
 *
 * Revision 1.84  2005/05/24 01:44:27  steve
 *  Do sign extension of structuran nets.
 *
 * Revision 1.83  2005/02/08 00:12:36  steve
 *  Add the NetRepeat node, and code generator support.
 *
 * Revision 1.82  2005/02/03 04:56:20  steve
 *  laborate reduction gates into LPM_RED_ nodes.
 *
 * Revision 1.81  2005/01/24 05:28:30  steve
 *  Remove the NetEBitSel and combine all bit/part select
 *  behavior into the NetESelect node and IVL_EX_SELECT
 *  ivl_target expression type.
 *
 * Revision 1.80  2005/01/22 01:06:55  steve
 *  Change case compare from logic to an LPM node.
 *
 * Revision 1.79  2004/12/29 23:55:43  steve
 *  Unify elaboration of l-values for all proceedural assignments,
 *  including assing, cassign and force.
 *
 *  Generate NetConcat devices for gate outputs that feed into a
 *  vector results. Use this to hande gate arrays. Also let gate
 *  arrays handle vectors of gates when the outputs allow for it.
 *
 * Revision 1.78  2004/12/11 02:31:26  steve
 *  Rework of internals to carry vectors through nexus instead
 *  of single bits. Make the ivl, tgt-vvp and vvp initial changes
 *  down this path.
 *
 * Revision 1.77  2004/10/04 01:10:53  steve
 *  Clean up spurious trailing white space.
 *
 * Revision 1.76  2004/05/31 23:34:37  steve
 *  Rewire/generalize parsing an elaboration of
 *  function return values to allow for better
 *  speed and more type support.
 *
 * Revision 1.75  2003/09/13 01:30:07  steve
 *  Missing case warnings.
 *
 * Revision 1.74  2003/05/30 02:55:32  steve
 *  Support parameters in real expressions and
 *  as real expressions, and fix multiply and
 *  divide with real results.
 *
 * Revision 1.73  2003/04/22 04:48:29  steve
 *  Support event names as expressions elements.
 *
 * Revision 1.72  2003/03/10 23:40:53  steve
 *  Keep parameter constants for the ivl_target API.
 *
 * Revision 1.71  2003/01/26 21:15:58  steve
 *  Rework expression parsing and elaboration to
 *  accommodate real/realtime values and expressions.
 */

