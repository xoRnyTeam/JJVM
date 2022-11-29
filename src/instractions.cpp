

#include <instructions.hpp>

#include <array>


namespace vm
{


struct NOperands final {
    std::array<int, 0xFF> noperands = {};

    NOperands() noexcept {
    noperands[NOP]             = 0;
	noperands[ACONST_NULL]     = 0;
	noperands[ICONST_M1]       = 0;
	noperands[ICONST_0]        = 0;
	noperands[ICONST_1]        = 0;
	noperands[ICONST_2]        = 0;
	noperands[ICONST_3]        = 0;
	noperands[ICONST_4]        = 0;
	noperands[ICONST_5]        = 0;
	noperands[LCONST_0]        = 0;
	noperands[LCONST_1]        = 0;
	noperands[FCONST_0]        = 0;
	noperands[FCONST_1]        = 0;
	noperands[FCONST_2]        = 0;
	noperands[DCONST_0]        = 0;
	noperands[DCONST_1]        = 0;
	noperands[BIPUSH]          = 1;
	noperands[SIPUSH]          = 2;
	noperands[LDC]             = 1;
	noperands[LDC_W]           = 2;
	noperands[LDC2_W]          = 2;
	noperands[ILOAD]           = 1;
	noperands[LLOAD]           = 1;
	noperands[FLOAD]           = 1;
	noperands[DLOAD]           = 1;
	noperands[ALOAD]           = 1;
	noperands[ILOAD_0]         = 0;
	noperands[ILOAD_1]         = 0;
	noperands[ILOAD_2]         = 0;
	noperands[ILOAD_3]         = 0;
	noperands[LLOAD_0]         = 0;
	noperands[LLOAD_1]         = 0;
	noperands[LLOAD_2]         = 0;
	noperands[LLOAD_3]         = 0;
	noperands[FLOAD_0]         = 0;
	noperands[FLOAD_1]         = 0;
	noperands[FLOAD_2]         = 0;
	noperands[FLOAD_3]         = 0;
	noperands[DLOAD_0]         = 0;
	noperands[DLOAD_1]         = 0;
	noperands[DLOAD_2]         = 0;
	noperands[DLOAD_3]         = 0;
	noperands[ALOAD_0]         = 0;
	noperands[ALOAD_1]         = 0;
	noperands[ALOAD_2]         = 0;
	noperands[ALOAD_3]         = 0;
	noperands[IALOAD]          = 0;
	noperands[LALOAD]          = 0;
	noperands[FALOAD]          = 0;
	noperands[DALOAD]          = 0;
	noperands[AALOAD]          = 0;
	noperands[BALOAD]          = 0;
	noperands[CALOAD]          = 0;
	noperands[SALOAD]          = 0;
	noperands[ISTORE]          = 1;
	noperands[LSTORE]          = 1;
	noperands[FSTORE]          = 1;
	noperands[DSTORE]          = 1;
	noperands[ASTORE]          = 1;
	noperands[ISTORE_0]        = 0;
	noperands[ISTORE_1]        = 0;
	noperands[ISTORE_2]        = 0;
	noperands[ISTORE_3]        = 0;
	noperands[LSTORE_0]        = 0;
	noperands[LSTORE_1]        = 0;
	noperands[LSTORE_2]        = 0;
	noperands[LSTORE_3]        = 0;
	noperands[FSTORE_0]        = 0;
	noperands[FSTORE_1]        = 0;
	noperands[FSTORE_2]        = 0;
	noperands[FSTORE_3]        = 0;
	noperands[DSTORE_0]        = 0;
	noperands[DSTORE_1]        = 0;
	noperands[DSTORE_2]        = 0;
	noperands[DSTORE_3]        = 0;
	noperands[ASTORE_0]        = 0;
	noperands[ASTORE_1]        = 0;
	noperands[ASTORE_2]        = 0;
	noperands[ASTORE_3]        = 0;
	noperands[IASTORE]         = 0;
	noperands[LASTORE]         = 0;
	noperands[FASTORE]         = 0;
	noperands[DASTORE]         = 0;
	noperands[AASTORE]         = 0;
	noperands[BASTORE]         = 0;
	noperands[CASTORE]         = 0;
	noperands[SASTORE]         = 0;
	noperands[POP]             = 0;
	noperands[POP2]            = 0;
	noperands[DUP]             = 0;
	noperands[DUP_X1]          = 0;
	noperands[DUP_X2]          = 0;
	noperands[DUP2]            = 0;
	noperands[DUP2_X1]         = 0;
	noperands[DUP2_X2]         = 0;
	noperands[SWAP]            = 0;
	noperands[IADD]            = 0;
	noperands[LADD]            = 0;
	noperands[FADD]            = 0;
	noperands[DADD]            = 0;
	noperands[ISUB]            = 0;
	noperands[LSUB]            = 0;
	noperands[FSUB]            = 0;
	noperands[DSUB]            = 0;
	noperands[IMUL]            = 0;
	noperands[LMUL]            = 0;
	noperands[FMUL]            = 0;
	noperands[DMUL]            = 0;
	noperands[IDIV]            = 0;
	noperands[LDIV]            = 0;
	noperands[FDIV]            = 0;
	noperands[DDIV]            = 0;
	noperands[IREM]            = 0;
	noperands[LREM]            = 0;
	noperands[FREM]            = 0;
	noperands[DREM]            = 0;
	noperands[INEG]            = 0;
	noperands[LNEG]            = 0;
	noperands[FNEG]            = 0;
	noperands[DNEG]            = 0;
	noperands[ISHL]            = 0;
	noperands[LSHL]            = 0;
	noperands[ISHR]            = 0;
	noperands[LSHR]            = 0;
	noperands[IUSHR]           = 0;
	noperands[LUSHR]           = 0;
	noperands[IAND]            = 0;
	noperands[LAND]            = 0;
	noperands[IOR]             = 0;
	noperands[LOR]             = 0;
	noperands[IXOR]            = 0;
	noperands[LXOR]            = 0;
	noperands[IINC]            = 2;
	noperands[I2L]             = 0;
	noperands[I2F]             = 0;
	noperands[I2D]             = 0;
	noperands[L2I]             = 0;
	noperands[L2F]             = 0;
	noperands[L2D]             = 0;
	noperands[F2I]             = 0;
	noperands[F2L]             = 0;
	noperands[F2D]             = 0;
	noperands[D2I]             = 0;
	noperands[D2L]             = 0;
	noperands[D2F]             = 0;
	noperands[I2B]             = 0;
	noperands[I2C]             = 0;
	noperands[I2S]             = 0;
	noperands[LCMP]            = 0;
	noperands[FCMPL]           = 0;
	noperands[FCMPG]           = 0;
	noperands[DCMPL]           = 0;
	noperands[DCMPG]           = 0;
	noperands[IFEQ]            = 2;
	noperands[IFNE]            = 2;
	noperands[IFLT]            = 2;
	noperands[IFGE]            = 2;
	noperands[IFGT]            = 2;
	noperands[IFLE]            = 2;
	noperands[IF_ICMPEQ]       = 2;
	noperands[IF_ICMPNE]       = 2;
	noperands[IF_ICMPLT]       = 2;
	noperands[IF_ICMPGE]       = 2;
	noperands[IF_ICMPGT]       = 2;
	noperands[IF_ICMPLE]       = 2;
	noperands[IF_ACMPEQ]       = 2;
	noperands[IF_ACMPNE]       = 2;
	noperands[GOTO]            = 2;
	noperands[JSR]             = 2;
	noperands[RET]             = 1;
	noperands[TABLESWITCH]     = OP_TABLESWITCH;
	noperands[LOOKUPSWITCH]    = OP_LOOKUPSWITCH;
	noperands[IRETURN]         = 0;
	noperands[LRETURN]         = 0;
	noperands[FRETURN]         = 0;
	noperands[DRETURN]         = 0;
	noperands[ARETURN]         = 0;
	noperands[RETURN]          = 0;
	noperands[GETSTATIC]       = 2;
	noperands[PUTSTATIC]       = 2;
	noperands[GETFIELD]        = 2;
	noperands[PUTFIELD]        = 2;
	noperands[INVOKEVIRTUAL]   = 2;
	noperands[INVOKESPECIAL]   = 2;
	noperands[INVOKESTATIC]    = 2;
	noperands[INVOKEINTERFACE] = 4;
	noperands[INVOKEDYNAMIC]   = 4;
	noperands[NEW]             = 2;
	noperands[NEWARRAY]        = 1;
	noperands[ANEWARRAY]       = 2;
	noperands[ARRAYLENGTH]     = 0;
	noperands[ATHROW]          = 0;
	noperands[CHECKCAST]       = 2;
	noperands[INSTANCEOF]      = 2;
	noperands[MONITORENTER]    = 0;
	noperands[MONITOREXIT]     = 0;
	noperands[WIDE]            = OP_WIDE;
	noperands[MULTIANEWARRAY]  = 3;
	noperands[IFNULL]          = 2;
	noperands[IFNONNULL]       = 2;
	noperands[GOTO_W]          = 4;
	noperands[JSR_W]           = 4;
    }

}; // NOperands


/// @brief get number of operands of a given instruction
int getnoperands(uint8_t instruction) {
    static NOperands ops;
    return ops.noperands[instruction];
}

} // namespace vm