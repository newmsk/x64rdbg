#include "bridgemain.h"

#include "pluginmain.h"
#include "rpc.h"

Status BridgeMain::DbgCmdExec(::grpc::ServerContext* context, const ::base::String* request, ::base::Boolean* response) 
{
	(void)context;
	const std::string &cmd = request->value();
	bool result = ::DbgCmdExec(cmd.c_str());
	response->set_boolean(result);
	return Status::OK;
}

Status BridgeMain::DbgCmdExecDirect(::grpc::ServerContext* context, const ::base::String* request, ::base::Boolean* response)
{
	(void)context;
	const std::string& cmd = request->value();
	bool result = ::DbgCmdExecDirect(cmd.c_str());
	response->set_boolean(result);
	return Status::OK;
}

Status BridgeMain::DbgEval(::grpc::ServerContext* context, const ::base::String* request, ::bridgemain::DbgExprValue* response)
{
	(void)context;
	const std::string& expr = request->value();
	bool success = false;
	duint value = ::DbgEval(expr.c_str(), &success);
	response->mutable_success()->set_boolean(success);
	if (success)
		response->mutable_value()->set_value(value);
	return Status::OK;
}


Status BridgeMain::GuiCloseApplication(::grpc::ServerContext* context, const ::base::Empty* request, ::base::Empty* response)
{
	(void)context; (void)request; (void)response;
	::GuiCloseApplication();
	return Status::OK;
}

Status BridgeMain::DbgGetBpList(::grpc::ServerContext* context, const ::base::Empty* request, ::bridgemain::BPList* response)
{
	(void)context; (void)request;

	BPMAP bpmap;
	::DbgGetBpList(bp_none, &bpmap);

	for (int i = 0; i < bpmap.count; i++)
	{
		auto& bp = bpmap.bp[i];
		auto* new_bp = response->add_bps();
		new_bp->set_type(static_cast<bridgemain::BPType>(bp.type));
		new_bp->mutable_addr()->set_address(bp.addr);
		new_bp->mutable_enabled()->set_boolean(bp.enabled);
		new_bp->mutable_single_shoot()->set_boolean(bp.singleshoot);
		new_bp->mutable_active()->set_boolean(bp.active);
		new_bp->mutable_name()->set_value(bp.name);
		new_bp->mutable_mod()->set_value(bp.mod);
		new_bp->mutable_typeex()->set_value(bp.typeEx);
		new_bp->mutable_hw_size()->set_value(bp.hwSize);
		new_bp->mutable_hit_count()->set_value(bp.hitCount);
		new_bp->mutable_fast_resume()->set_boolean(bp.fastResume);
		new_bp->mutable_silent()->set_boolean(bp.silent);
		new_bp->mutable_break_condition()->set_value(bp.breakCondition);
		new_bp->mutable_log_text()->set_value(bp.logCondition);
		new_bp->mutable_command_text()->set_value(bp.commandText);
		new_bp->mutable_command_condition()->set_value(bp.commandCondition);
	}

	return Status::OK;
}


Status BridgeMain::DbgGetRegDumpEx(::grpc::ServerContext* context, const ::base::Empty* request, ::bridgemain::RegDump* response)
{
	(void)context; (void)request;
	REGDUMP regdump = {};
	::DbgGetRegDumpEx(&regdump, sizeof(REGDUMP));

	auto* rpc_ctx = MF(response, reg_context);
	auto& ctx = regdump.regcontext;
	MFS1(rpc_ctx, cax, value, ctx.cax);
	MFS1(rpc_ctx, ccx, value, ctx.ccx);
	MFS1(rpc_ctx, cdx, value, ctx.cdx);
	MFS1(rpc_ctx, cbx, value, ctx.cbx);
	MFS1(rpc_ctx, csp, value, ctx.csp);
	MFS1(rpc_ctx, cbp, value, ctx.cbp);
	MFS1(rpc_ctx, csi, value, ctx.csi);
	MFS1(rpc_ctx, cdi, value, ctx.cdi);

#ifdef _WIN64
	MFS1(rpc_ctx, r8, value, ctx.r8);
	MFS1(rpc_ctx, r9, value, ctx.r9);
	MFS1(rpc_ctx, r10, value, ctx.r10);
	MFS1(rpc_ctx, r11, value, ctx.r11);
	MFS1(rpc_ctx, r12, value, ctx.r12);
	MFS1(rpc_ctx, r13, value, ctx.r13);
	MFS1(rpc_ctx, r14, value, ctx.r14);
	MFS1(rpc_ctx, r15, value, ctx.r15);
#endif //_WIN64

	MFS1(rpc_ctx, cip, value, ctx.cip);
	MFS1(rpc_ctx, eflags, value, ctx.eflags);
	MFS1(rpc_ctx, gs, value, ctx.gs);
	MFS1(rpc_ctx, fs, value, ctx.fs);
	MFS1(rpc_ctx, es, value, ctx.es);
	MFS1(rpc_ctx, ds, value, ctx.ds);
	MFS1(rpc_ctx, cs, value, ctx.cs);
	MFS1(rpc_ctx, ss, value, ctx.ss);
	MFS1(rpc_ctx, dr0, value, ctx.dr0);
	MFS1(rpc_ctx, dr1, value, ctx.dr1);
	MFS1(rpc_ctx, dr2, value, ctx.dr2);
	MFS1(rpc_ctx, dr3, value, ctx.dr3);
	MFS1(rpc_ctx, dr6, value, ctx.dr6);
	MFS1(rpc_ctx, dr7, value, ctx.dr7);

	MFS1(rpc_ctx, register_area, size, 80);
	MFS1(rpc_ctx, register_area, data, ctx.RegisterArea, 80);

	MFS2(rpc_ctx, x87fpu, control_word, value, ctx.x87fpu.ControlWord);
	MFS2(rpc_ctx, x87fpu, status_word, value, ctx.x87fpu.StatusWord);
	MFS2(rpc_ctx, x87fpu, tag_word, value, ctx.x87fpu.TagWord);
	MFS2(rpc_ctx, x87fpu, error_offset, value, ctx.x87fpu.ErrorOffset);
	MFS2(rpc_ctx, x87fpu, error_selector, value, ctx.x87fpu.ErrorSelector);
	MFS2(rpc_ctx, x87fpu, data_offset, value, ctx.x87fpu.DataOffset);
	MFS2(rpc_ctx, x87fpu, data_selector, value, ctx.x87fpu.DataSelector);
	MFS2(rpc_ctx, x87fpu, cr0npx_state, value, ctx.x87fpu.Cr0NpxState);

	MFS1(rpc_ctx, mx_csr, value, ctx.MxCsr);

#ifdef _WIN64
	constexpr int xymm_register_count = 16;
#else
	constexpr int xymm_register_count = 8;
#endif

	MFS2(rpc_ctx, xmm_registers, size, value, xymm_register_count);
	for (int i = 0; i < xymm_register_count; i++) {
		auto* rpc_xmm_register = rpc_ctx->mutable_xmm_registers()->add_xmm_registers();
		auto& xmm_register = ctx.XmmRegisters[i];
		MFS1(rpc_xmm_register, low, value, xmm_register.Low);
		MFS1(rpc_xmm_register, high, value, xmm_register.High);
	}
	for (int i = 0; i < xymm_register_count; i++) {
		auto* rpc_ymm_register = rpc_ctx->mutable_ymm_registers()->add_ymm_registers();
		auto& ymm_register = ctx.YmmRegisters[i];
		MFS2(rpc_ymm_register, low, low, value, ymm_register.Low.Low);
		MFS2(rpc_ymm_register, low, high, value, ymm_register.Low.High);
		MFS2(rpc_ymm_register, high, low, value, ymm_register.High.Low);
		MFS2(rpc_ymm_register, high, high, value, ymm_register.High.High);
	}

	auto* rpc_flags = MF(response, flags);
	auto& flags = regdump.flags;
	MFS1(rpc_flags, c, boolean, flags.c);
	MFS1(rpc_flags, p, boolean, flags.p);
	MFS1(rpc_flags, a, boolean, flags.a);
	MFS1(rpc_flags, z, boolean, flags.z);
	MFS1(rpc_flags, s, boolean, flags.s);
	MFS1(rpc_flags, t, boolean, flags.t);
	MFS1(rpc_flags, i, boolean, flags.i);
	MFS1(rpc_flags, d, boolean, flags.d);
	MFS1(rpc_flags, o, boolean, flags.o);

	auto* rpc_x87fpu = MF(response, x87fpu_reg);
	MFS1(rpc_x87fpu, size, value, 8);
	for (int i = 0; i < 8; i++) {
		auto* rpc_x87fpu_reg = rpc_x87fpu->add_x87fpu_reg();
		MFS1(rpc_x87fpu_reg, data, size, 10);
		MFS1(rpc_x87fpu_reg, data, data, regdump.x87FPURegisters[i].data, 10);
		MFS1(rpc_x87fpu_reg, st_value, value, regdump.x87FPURegisters[i].st_value);
		MFS1(rpc_x87fpu_reg, tag, value, regdump.x87FPURegisters[i].tag);
	}

	auto* rpc_mmx = MF(response, mmx);
	MFS1(rpc_mmx, size, value, 8);
	for (int i = 0; i < 8; i++) {
		auto* rpc_mmx_reg = rpc_mmx->add_mmx();
		MFS0(rpc_mmx_reg, value, regdump.mmx[i]);
	}

	auto* rpc_mx_csr_field = MF(response, mx_csr_field);
	auto& mx_csr_field = regdump.MxCsrFields;
	MFS1(rpc_mx_csr_field, fz, boolean, mx_csr_field.FZ);
	MFS1(rpc_mx_csr_field, pm, boolean, mx_csr_field.PM);
	MFS1(rpc_mx_csr_field, um, boolean, mx_csr_field.UM);
	MFS1(rpc_mx_csr_field, om, boolean, mx_csr_field.OM);
	MFS1(rpc_mx_csr_field, zm, boolean, mx_csr_field.ZM);
	MFS1(rpc_mx_csr_field, im, boolean, mx_csr_field.IM);
	MFS1(rpc_mx_csr_field, dm, boolean, mx_csr_field.DM);
	MFS1(rpc_mx_csr_field, daz, boolean, mx_csr_field.DAZ);
	MFS1(rpc_mx_csr_field, pe, boolean, mx_csr_field.PE);
	MFS1(rpc_mx_csr_field, ue, boolean, mx_csr_field.UE);
	MFS1(rpc_mx_csr_field, oe, boolean, mx_csr_field.OE);
	MFS1(rpc_mx_csr_field, ze, boolean, mx_csr_field.ZE);
	MFS1(rpc_mx_csr_field, de, boolean, mx_csr_field.DE);
	MFS1(rpc_mx_csr_field, ie, boolean, mx_csr_field.IE);
	MFS1(rpc_mx_csr_field, rc, value, mx_csr_field.RC);

	auto* rpc_x87_status_word_field = MF(response, x87_status_word_field);
	auto& x87_status_word_field = regdump.x87StatusWordFields;
	MFS1(rpc_x87_status_word_field, b, boolean, x87_status_word_field.B);
	MFS1(rpc_x87_status_word_field, c3, boolean, x87_status_word_field.C3);
	MFS1(rpc_x87_status_word_field, c2, boolean, x87_status_word_field.C2);
	MFS1(rpc_x87_status_word_field, c1, boolean, x87_status_word_field.C1);
	MFS1(rpc_x87_status_word_field, c0, boolean, x87_status_word_field.C0);
	MFS1(rpc_x87_status_word_field, es, boolean, x87_status_word_field.ES);
	MFS1(rpc_x87_status_word_field, sf, boolean, x87_status_word_field.SF);
	MFS1(rpc_x87_status_word_field, p, boolean, x87_status_word_field.P);
	MFS1(rpc_x87_status_word_field, u, boolean, x87_status_word_field.U);
	MFS1(rpc_x87_status_word_field, o, boolean, x87_status_word_field.O);
	MFS1(rpc_x87_status_word_field, z, boolean, x87_status_word_field.Z);
	MFS1(rpc_x87_status_word_field, d, boolean, x87_status_word_field.D);
	MFS1(rpc_x87_status_word_field, i, boolean, x87_status_word_field.I);
	MFS1(rpc_x87_status_word_field, top, value, x87_status_word_field.TOP);

	auto* rpc_x87_control_word_field = MF(response, x87_control_word_field);
	auto& x87_control_word_field = regdump.x87ControlWordFields;
	MFS1(rpc_x87_control_word_field, ic, boolean, x87_control_word_field.IC);
	MFS1(rpc_x87_control_word_field, iem, boolean, x87_control_word_field.IEM);
	MFS1(rpc_x87_control_word_field, pm, boolean, x87_control_word_field.PM);
	MFS1(rpc_x87_control_word_field, um, boolean, x87_control_word_field.UM);
	MFS1(rpc_x87_control_word_field, om, boolean, x87_control_word_field.OM);
	MFS1(rpc_x87_control_word_field, zm, boolean, x87_control_word_field.ZM);
	MFS1(rpc_x87_control_word_field, dm, boolean, x87_control_word_field.DM);
	MFS1(rpc_x87_control_word_field, im, boolean, x87_control_word_field.IM);
	MFS1(rpc_x87_control_word_field, rc, value, x87_control_word_field.RC);
	MFS1(rpc_x87_control_word_field, pc, value, x87_control_word_field.PC);

	auto* rpc_last_error = MF(response, last_error);
	auto& last_error = regdump.lastError;
	MFS1(rpc_last_error, code, value, last_error.code);
	MFS1(rpc_last_error, name, value, last_error.name);

	auto* rpc_last_status = MF(response, last_status);
	auto& last_status = regdump.lastStatus;
	MFS1(rpc_last_status, code, value, last_status.code);
	MFS1(rpc_last_status, name, value, last_status.name);

	return Status::OK;
}