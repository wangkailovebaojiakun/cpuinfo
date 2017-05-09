#include <stdint.h>

#include <arm/linux/api.h>
#include <arm/linux/cp.h>
#include <log.h>


void cpuinfo_arm64_linux_decode_isa_from_proc_cpuinfo(
	const struct proc_cpuinfo proc_cpuinfo[restrict static 1],
	struct cpuinfo_arm_isa isa[restrict static 1])
{
	const uint32_t features = proc_cpuinfo->features;
	if (features & PROC_CPUINFO_FEATURE_AES) {
		isa->aes = true;
	}
	if (features & PROC_CPUINFO_FEATURE_PMULL) {
		isa->pmull = true;
	}
	if (features & PROC_CPUINFO_FEATURE_SHA1) {
		isa->sha1 = true;
	}
	if (features & PROC_CPUINFO_FEATURE_SHA2) {
		isa->sha2 = true;
	}
	if (features & PROC_CPUINFO_FEATURE_CRC32) {
		isa->crc32 = true;
	}
	if (features & PROC_CPUINFO_FEATURE_ATOMICS) {
		isa->atomics = true;
	}
	const uint32_t fp16arith_mask = PROC_CPUINFO_FEATURE_FPHP | PROC_CPUINFO_FEATURE_ASIMDHP;
	if ((features & fp16arith_mask) == fp16arith_mask) {
		isa->fp16arith = true;
	} else if (features & PROC_CPUINFO_FEATURE_FPHP) {
		cpuinfo_log_warning("FP16 arithmetics disabled: detected support only for scalar operations");
	} else if (features & PROC_CPUINFO_FEATURE_ASIMDHP) {
		cpuinfo_log_warning("FP16 arithmetics disabled: detected support only for SIMD operations");
	}
	if (features & PROC_CPUINFO_FEATURE_ASIMDRDM) {
		isa->rdm = true;
	}
	if (features & PROC_CPUINFO_FEATURE_JSCVT) {
		isa->jscvt = true;
	}
	if (features & PROC_CPUINFO_FEATURE_ASIMDRDM) {
		isa->rdm = true;
	}
	if (features & PROC_CPUINFO_FEATURE_JSCVT) {
		isa->jscvt = true;
	}
	if (features & PROC_CPUINFO_FEATURE_FCMA) {
		isa->fcma = true;
	}
}