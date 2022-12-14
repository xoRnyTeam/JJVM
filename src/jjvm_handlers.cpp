#include <jjvm.hpp>
#include <instructions.hpp>
#include <cmath>
#include <cstring>
#include <iostream>

namespace vm
{

void jjvm::opnop() {
    return;
}

void jjvm::opiconst_0() {
	Value v;
	v.i = 0;
	m_frames.top().stackPush(v);
}

void jjvm::opiconst_1() {
	Value v;
	v.i = 1;
	m_frames.top().stackPush(v);
}

void jjvm::opiconst_2() {
	Value v;
	v.i = 2;
	m_frames.top().stackPush(v);
}

void jjvm::opiconst_3() {
	Value v;
	v.i = 3;
	m_frames.top().stackPush(v);
}

void jjvm::opiconst_4() {
	Value v;
	v.i = 4;
	m_frames.top().stackPush(v);
}

void jjvm::opiconst_5() {
	Value v;
	v.i = 5;
	m_frames.top().stackPush(v);
}

void jjvm::opladd() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.l += v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opaconst_null() {
    Value v;
    v.heapID = m_heap.allocate(0, 0);
    m_frames.top().stackPush(v);
}

void jjvm::opiconst_m1() {
    Value v;
    v.i = -1;
    m_frames.top().stackPush(v);
}

void jjvm::oplconst_0() {
	Value v;
	v.l = 0;
	m_frames.top().stackPush(v);
}

void jjvm::oplconst_1() {
	Value v;
	v.l = 1;
	m_frames.top().stackPush(v);
}

void jjvm::opdconst_0() {
	Value v;
	v.d = 0;
	m_frames.top().stackPush(v);
}

void jjvm::opdconst_1() {
	Value v;
	v.d = 1;
	m_frames.top().stackPush(v);
}

void jjvm::opfconst_0() {
	Value v;
	v.f = 0;
	m_frames.top().stackPush(v);
}

void jjvm::opfconst_1() {
	Value v;
	v.f = 1;
	m_frames.top().stackPush(v);
}

void jjvm::opfconst_2() {
	Value v;
	v.f = 2;
	m_frames.top().stackPush(v);
}

void jjvm::opbipush() {
    Value v;
    v.i = m_frames.top().code->code[m_frames.top().pc++];
    m_frames.top().stackPush(v);
}

void jjvm::opldc() {
    Value v;
    uint16_t i = m_frames.top().code->code[m_frames.top().pc++];
    v = resolveConstant(i);
    m_frames.top().stackPush(v);
}

void jjvm::opldc_w() {
    Value v;
    uint16_t i = m_frames.top().code->code[m_frames.top().pc++] << 8;
    i |= m_frames.top().code->code[m_frames.top().pc++];
    v = resolveConstant(i);
    m_frames.top().stackPush(v);
}

void jjvm::opldc2_w() {
    Value v;
    uint16_t i = m_frames.top().code->code[m_frames.top().pc++] << 8;
    i |= m_frames.top().code->code[m_frames.top().pc++];
    v = resolveConstant(i);
    m_frames.top().stackPush(v);
}

void jjvm::opiload() {
    Value v;
    uint16_t i = m_frames.top().code->code[m_frames.top().pc++];
    v = m_frames.top().localLoad(i);
    m_frames.top().stackPush(v);
}

void jjvm::oplload() {
    Value v;
    uint16_t i = m_frames.top().code->code[m_frames.top().pc++];
    v = m_frames.top().localLoad(i);
    m_frames.top().stackPush(v);
}

void jjvm::opiload_0() {
    Value v;
    v = m_frames.top().localLoad(0);
    m_frames.top().stackPush(v);
}

void jjvm::opiload_1() {
    Value v;
    v = m_frames.top().localLoad(1);
    m_frames.top().stackPush(v);
}

void jjvm::opiload_2() {
    Value v;
    v = m_frames.top().localLoad(2);
    m_frames.top().stackPush(v);
}

void jjvm::opiload_3() {
    Value v;
    v = m_frames.top().localLoad(3);
    m_frames.top().stackPush(v);
}

void jjvm::oplload_0() {
    Value v;
    v = m_frames.top().localLoad(0);
    m_frames.top().stackPush(v);
}

void jjvm::oplload_1() {
    Value v;
    v = m_frames.top().localLoad(1);
    m_frames.top().stackPush(v);
}

void jjvm::oplload_2() {
    Value v;
    v = m_frames.top().localLoad(2);
    m_frames.top().stackPush(v);
}

void jjvm::oplload_3() {
    Value v;
    v = m_frames.top().localLoad(3);
    m_frames.top().stackPush(v);
}

void jjvm::opiaload() {
    Value va, vi, v;
    vi = m_frames.top().stackTop();
    m_frames.top().stackPop();
    va = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.i = m_heap.load<int>(va.heapID, vi.i);
    m_frames.top().stackPush(v);
}

void jjvm::oplaload() {
    Value va, vi, v;
    vi = m_frames.top().stackTop();
    m_frames.top().stackPop();
    va = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.i = m_heap.load<long>(va.heapID, vi.i);
    m_frames.top().stackPush(v);
}

void jjvm::opfaload() {
    Value va, vi, v;
    vi = m_frames.top().stackTop();
    m_frames.top().stackPop();
    va = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.f = m_heap.load<float>(va.heapID, vi.i);
    m_frames.top().stackPush(v);
}

void jjvm::opdaload() {
    Value va, vi, v;
    vi = m_frames.top().stackTop();
    m_frames.top().stackPop();
    va = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.d = m_heap.load<double>(va.heapID, vi.i);

    m_frames.top().stackPush(v);
}

void jjvm::opistore() {
    Value v;
    uint16_t i = m_frames.top().code->code[m_frames.top().pc++];
    v = m_frames.top().stackTop();
    m_frames.top().localStore(i, v);
}

void jjvm::opistore_0() {
    Value v;
    v = m_frames.top().stackTop();
    m_frames.top().localStore(0, v);
}

void jjvm::opistore_1() {
    Value v;
    v = m_frames.top().stackTop();
    m_frames.top().localStore(1, v);
}

void jjvm::opistore_2() {
    Value v;
    v = m_frames.top().stackTop();
    m_frames.top().localStore(2, v);
}

void jjvm::opistore_3() {
    Value v;
    v = m_frames.top().stackTop();
    m_frames.top().localStore(3, v);
}

void jjvm::oplstore() {
    Value v;
    uint16_t i = m_frames.top().code->code[m_frames.top().pc++];
    v = m_frames.top().stackTop();
    m_frames.top().localStore(i, v);
    m_frames.top().localStore(i + 1, v);
}

void jjvm::oplstore_0() {
    Value v;
    v = m_frames.top().stackTop();
    m_frames.top().localStore(0, v);
    m_frames.top().localStore(1, v);
}

void jjvm::oplstore_1() {
    Value v;
    v = m_frames.top().stackTop();
    m_frames.top().localStore(1, v);
    m_frames.top().localStore(2, v);
}

void jjvm::oplstore_2() {
    Value v;
    v = m_frames.top().stackTop();
    m_frames.top().localStore(2, v);
    m_frames.top().localStore(3, v);
}

void jjvm::oplstore_3() {
    Value v;
    v = m_frames.top().stackTop();
    m_frames.top().localStore(3, v);
    m_frames.top().localStore(4, v);
}

void jjvm::opiastore() {
    Value va, vi, vv;
    vv = m_frames.top().stackTop();
    m_frames.top().stackPop();
    vi = m_frames.top().stackTop();
    m_frames.top().stackPop();
    va = m_frames.top().stackTop();
    m_frames.top().stackPop();
    m_heap.store(va.heapID, vi.i, vv.i);
}

void jjvm::oplastore() {
    Value va, vi, vv;
    vv = m_frames.top().stackTop();
    m_frames.top().stackPop();
    vi = m_frames.top().stackTop();
    m_frames.top().stackPop();
    va = m_frames.top().stackTop();
    m_frames.top().stackPop();
    m_heap.store(va.heapID, vi.i, vv.l);
}

void jjvm::opfastore() {
    Value va, vi, vv;
    vv = m_frames.top().stackTop();
    m_frames.top().stackPop();
    vi = m_frames.top().stackTop();
    m_frames.top().stackPop();
    va = m_frames.top().stackTop();
    m_frames.top().stackPop();
    m_heap.store(va.heapID, vi.i, vv.f);
}

void jjvm::opdastore() {
    Value va, vi, vv;
    vv = m_frames.top().stackTop();
    m_frames.top().stackPop();
    vi = m_frames.top().stackTop();
    m_frames.top().stackPop();
    va = m_frames.top().stackTop();
    m_frames.top().stackPop();

    m_heap.store<double>(va.heapID, vi.i, vv.d);
}

void jjvm::oppop() {
    m_frames.top().stackPop();
}

void jjvm::oppop2() {
    m_frames.top().stackPop();
    m_frames.top().stackPop();
}

void jjvm::opdup() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPush(v);
}

void jjvm::opdup2() {
    Value v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    Value v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    m_frames.top().stackPush(v2);
    m_frames.top().stackPush(v1);
    m_frames.top().stackPush(v2);
    m_frames.top().stackPush(v1);
}

void jjvm::opdup_x1() {
    Value v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    Value v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    m_frames.top().stackPush(v1);
    m_frames.top().stackPush(v2);
    m_frames.top().stackPush(v1);
}

void jjvm::opdup_x2() {
    Value v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    Value v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    Value v3 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    m_frames.top().stackPush(v1);
    m_frames.top().stackPush(v3);
    m_frames.top().stackPush(v2);
    m_frames.top().stackPush(v1);
}
void jjvm::opdup2_x1() {
    Value v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    Value v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    Value v3 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    m_frames.top().stackPush(v2);
    m_frames.top().stackPush(v1);
    m_frames.top().stackPush(v3);
    m_frames.top().stackPush(v2);
    m_frames.top().stackPush(v1);
}

void jjvm::opdup2_x2() {
    Value v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    Value v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    Value v3 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    Value v4 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    m_frames.top().stackPush(v2);
    m_frames.top().stackPush(v1);
    m_frames.top().stackPush(v4);
    m_frames.top().stackPush(v3);
    m_frames.top().stackPush(v2);
    m_frames.top().stackPush(v1);
}

void jjvm::opswap() {
    Value v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    Value v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    m_frames.top().stackPush(v1);
    m_frames.top().stackPush(v2);
}

void jjvm::opiadd() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.i += v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::opfadd() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.f += v2.f;
    m_frames.top().stackPush(v1);
}

void jjvm::opdadd() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.d += v2.d;
    m_frames.top().stackPush(v1);
}

void jjvm::opisub() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.i -= v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::oplsub() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.l -= v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opfsub() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.f -= v2.f;
    m_frames.top().stackPush(v1);
}

void jjvm::opdsub() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.d -= v2.d;
    m_frames.top().stackPush(v1);
}

void jjvm::opimul() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.i *= v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::oplmul() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.l *= v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opfmul() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.f *= v2.f;
    m_frames.top().stackPush(v1);
}

void jjvm::opdmul() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.d *= v2.d;
    m_frames.top().stackPush(v1);
}

void jjvm::opidiv() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.i /= v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::opldiv() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.l /= v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opfdiv() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.f /= v2.f;
    m_frames.top().stackPush(v1);
}

void jjvm::opddiv() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.d /= v2.d;
    m_frames.top().stackPush(v1);
}

void jjvm::opirem() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

    v1.i = v1.i - (v1.i / v2.i) * v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::oplrem() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

    v1.l = v1.l - (v1.l / v2.l) * v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opfrem() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v1.f = std::fmod(v1.f, v2.f);
    m_frames.top().stackPush(v1);
}

void jjvm::opdrem() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v1.d = std::fmod(v1.d, v2.d);
    m_frames.top().stackPush(v1);
}

void jjvm::opineg() {
    Value v;
	v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.i *= -1;
    m_frames.top().stackPush(v);
}

void jjvm::oplneg() {
    Value v;
	v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.l *= -1;
    m_frames.top().stackPush(v);
}

void jjvm::opfneg() {
    Value v;
	v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.f *= -1;
    m_frames.top().stackPush(v);
}

void jjvm::opdneg() {
    Value v;
	v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.i *= -1;
    m_frames.top().stackPush(v);
}

void jjvm::opishl() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.i <<= v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::oplshl() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.l <<= v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opishr() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.i >>= v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::oplshr() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.l >>= v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opiushr() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.i = static_cast<unsigned>(v1.i) >> v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::oplushr() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.l = static_cast<unsigned>(v1.l) >> v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opiand() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.i &= v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::opland() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.l &= v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opior() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.i |= v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::oplor() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.l |= v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opixor() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.i ^= v2.i;
    m_frames.top().stackPush(v1);
}

void jjvm::oplxor() {
    Value v1, v2;
	v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1.l ^= v2.l;
    m_frames.top().stackPush(v1);
}

void jjvm::opiinc() {
    Value v;
    uint8_t i = m_frames.top().code->code[m_frames.top().pc++];
    int8_t c = static_cast<int8_t>(m_frames.top().code->code[m_frames.top().pc++]);
    v = m_frames.top().localLoad(i);
    v.i += c;
    m_frames.top().localStore(i, v);
}

void jjvm::opi2l() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.l = v.i;
    m_frames.top().stackPush(v);
}

void jjvm::opi2f() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.f = static_cast<float>(v.i);
    m_frames.top().stackPush(v);
}

void jjvm::opi2d() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.d = static_cast<double>(v.i);
    m_frames.top().stackPush(v);
}

void jjvm::opl2i() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.i = static_cast<int32_t>(v.l);
    m_frames.top().stackPush(v);
}

void jjvm::opl2f() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.f = static_cast<float>(v.l);
    m_frames.top().stackPush(v);
}

void jjvm::opl2d() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.d = static_cast<double>(v.l);
    m_frames.top().stackPush(v);
}

void jjvm::opf2i() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.i = static_cast<int32_t>(v.f);
    m_frames.top().stackPush(v);
}

void jjvm::opf2l() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.l = static_cast<long>(v.f);
    m_frames.top().stackPush(v);
}

void jjvm::opf2d() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.d = static_cast<double>(v.f);
    m_frames.top().stackPush(v);
}

void jjvm::opd2i() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.i = static_cast<int32_t>(v.d);
    m_frames.top().stackPush(v);
}

void jjvm::opd2l() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.l = static_cast<long>(v.d);
    m_frames.top().stackPush(v);
}

void jjvm::opd2f() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v.f = static_cast<float>(v.d);
    m_frames.top().stackPush(v);
}

void jjvm::oplcmp() {
    Value v1, v2, v;
    v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    if (v1.l > v2.l) {
        v.i = 1;
    }
    else if (v1.l < v2.l) {
        v.i = -1;
    }
    else {
        v.i = 0;
    }
    m_frames.top().stackPush(v);
}

void jjvm::opfcmpl() {
    Value v1, v2, v;
    v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    if (v1.f > v2.f) {
        v.i = 1;
    }
    else if (v1.f == v2.f) {
        v.i = 0;
    }
    else {
        v.i = -1;
    }
    m_frames.top().stackPush(v);
}

void jjvm::opfcmpg() {
    Value v1, v2, v;
    v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    if (v1.f > v2.f) {
        v.i = 1;
    }
    else if (v1.f == v2.f) {
        v.i = 0;
    }
    else {
        v.i = 1;
    }
    m_frames.top().stackPush(v);
}

void jjvm::opdcmpl() {
    Value v1, v2, v;
    v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    if (v1.d > v2.d) {
        v.i = 1;
    }
    else if (v1.d == v2.d) {
        v.i = 0;
    }
    else {
        v.i = -1;
    }
    m_frames.top().stackPush(v);
}

void jjvm::opdcmpg() {
    Value v1, v2, v;
    v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();

	v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    if (v1.d > v2.d) {
        v.i = 1;
    }
    else if (v1.d == v2.d) {
        v.i = 0;
    }
    else {
        v.i = 1;
    }
    m_frames.top().stackPush(v);
}

void jjvm::opifne() {
    Value v;
    int16_t off = 0;
    uint16_t base, i;
    base = m_frames.top().pc - 1;
    i = m_frames.top().code->code[m_frames.top().pc++] << 8;
    i |= m_frames.top().code->code[m_frames.top().pc++];
    v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    if (v.i != 0) {
        std::memcpy(&off, &i, sizeof off);
        m_frames.top().pc = base + off;
    }
}

void jjvm::opifle() {
    Value v;
    int16_t off = 0;
    uint16_t base, i;
    base = m_frames.top().pc - 1;
    i = m_frames.top().code->code[m_frames.top().pc++] << 8;
    i |= m_frames.top().code->code[m_frames.top().pc++];
    v = m_frames.top().stackTop();
    m_frames.top().stackPop();
    if (v.i <= 0) {
        std::memcpy(&off, &i, sizeof(off));
        m_frames.top().pc = base + off;
    }
}

void jjvm::opif_icmpne() {
    Value v1, v2;
    int16_t off = 0;
    uint16_t base, i;
    base = m_frames.top().pc - 1;
    i = m_frames.top().code->code[m_frames.top().pc++] << 8;
    i |= m_frames.top().code->code[m_frames.top().pc++];
    v1 = m_frames.top().stackTop(); // TODO check
    m_frames.top().stackPop();
    v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    if (v1.i != v2.i) {
        std::memcpy(&off, &i, sizeof(off));
        m_frames.top().pc = base + off;
    }
}

void jjvm::opif_icmpge() {
    Value v1, v2;
    int16_t off = 0;
    uint16_t base, i;
    base = m_frames.top().pc - 1;
    i = m_frames.top().code->code[m_frames.top().pc++] << 8;
    i |= m_frames.top().code->code[m_frames.top().pc++];
    v2 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    v1 = m_frames.top().stackTop();
    m_frames.top().stackPop();
    if (v1.i >= v2.i) {
        std::memcpy(&off, &i, sizeof(off));
        m_frames.top().pc = base + off;
    }
}

void jjvm::opgoto() {
    int16_t off = 0;
    uint16_t base, i;
    base = m_frames.top().pc - 1;
    i = m_frames.top().code->code[m_frames.top().pc++] << 8;
    i |= m_frames.top().code->code[m_frames.top().pc++];
    std::memcpy(&off, &i, sizeof(off));
    m_frames.top().pc = base + off;
}

void jjvm::opreturn() {
    m_frames.top().pc = -1;
}

void jjvm::opireturn() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();

    Frame tmp = m_frames.top();
    m_frames.pop();

    m_frames.top().stackPush(v);
    m_frames.push(tmp);
    
    m_frames.top().pc = -1;
}

void jjvm::oparraylength() {
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();

    v.i = static_cast<int32_t>(m_heap.get_nmembers(v.heapID));
    m_frames.top().stackPush(v);
}

void jjvm::opnewarray() {
    TypeCode type = static_cast<TypeCode>(m_frames.top().code->code[m_frames.top().pc++]);
    Value v = m_frames.top().stackTop();
    m_frames.top().stackPop();

    size_t size = 0;
    switch (type)
    {
    case TypeCode::LONG:
        size = sizeof(int64_t);
        break;
    case TypeCode::DOUBLE:
        size = sizeof(double);
        break;
    case TypeCode::FLOAT:
        size = sizeof(float);
        break;
    
    default:
        size = sizeof(int32_t);
        break;
    }

    size_t h_id = m_heap.allocate(size, v.i);
    v.heapID = h_id;
    m_frames.top().stackPush(v);
}

void jjvm::opinvokestatic() {
    uint16_t i = m_frames.top().code->code[m_frames.top().pc++] << 8;
    i |= m_frames.top().code->code[m_frames.top().pc++];

    auto&& method_ref = std::static_pointer_cast<CONSTANT_Methodref_info>(m_class.cp[i]);
    auto&& class_name = m_class.getClassName(method_ref->class_index);
    auto&& method_str = m_class.getNameAndType(method_ref->name_and_type_index);

    methodCall(method_str.first, method_str.second, ACC_STATIC);
}

void jjvm::opgetstatic() {
	uint16_t i = m_frames.top().code->code[m_frames.top().pc++] << 8;
	i |= m_frames.top().code->code[m_frames.top().pc++];

    // std::cout << "WARNING: opgetstatic ignored with i = " + std::to_string(i) << std::endl;
}

void jjvm::opinvokevirtual() {
	uint16_t i = m_frames.top().code->code[m_frames.top().pc++] << 8;
	i |= m_frames.top().code->code[m_frames.top().pc++];

    auto&& method_ref = std::static_pointer_cast<CONSTANT_Methodref_info>(m_class.cp[i]);
    auto&& class_name = m_class.getClassName(method_ref->class_index);
    auto&& method_str = m_class.getNameAndType(method_ref->name_and_type_index);

    if(class_name == "java/io/PrintStream") {
        if(method_str.first == "println") {
            println(method_str.second);
            return;
        }
    }

    throw std::runtime_error("Can't resolve virtual call!");
}

void jjvm::println(const std::string &descriptor) {
    Value val = m_frames.top().stackTop();
    m_frames.top().stackPop();

    if (descriptor == "(Ljava/lang/String;)V") {
        std::cout << "WARNING: can't printl string" << std::endl;
    }
	else if (descriptor == "(B)V") {
        std::cout << val.i << std::endl;
    }
	else if (descriptor == "(C)V") {
        std::cout << val.i << std::endl;
    }
	else if (descriptor == "(D)V") {
        std::cout << val.d << std::endl;
    }
	else if (descriptor == "(F)V") {
        std::cout << val.f << std::endl;
    }
	else if (descriptor == "(I)V") {
        std::cout << val.i << std::endl;
    }
	else if (descriptor == "(J)V") {
        std::cout << val.l << std::endl;
    }
	else if (descriptor == "(S)V") {
        std::cout << val.i << std::endl;
    }
	else if (descriptor == "(Z)V") {
        std::cout << val.i << std::endl;
    }
}


void jjvm::intiHandlers() {
    m_handlers[NOP]             = std::bind(&jjvm::opnop, this);
    m_handlers[ACONST_NULL]     = std::bind(&jjvm::opaconst_null, this);
    m_handlers[ICONST_M1]       = std::bind(&jjvm::opiconst_m1, this);
    m_handlers[ICONST_0]        = std::bind(&jjvm::opiconst_0, this);
    m_handlers[ICONST_1]        = std::bind(&jjvm::opiconst_1, this);
    m_handlers[ICONST_2]        = std::bind(&jjvm::opiconst_2, this);
    m_handlers[ICONST_3]        = std::bind(&jjvm::opiconst_3, this);
    m_handlers[ICONST_4]        = std::bind(&jjvm::opiconst_4, this);
    m_handlers[ICONST_5]        = std::bind(&jjvm::opiconst_5, this);
    m_handlers[LCONST_0]        = std::bind(&jjvm::oplconst_0, this);
    m_handlers[LCONST_1]        = std::bind(&jjvm::oplconst_1, this);
    m_handlers[FCONST_0]        = std::bind(&jjvm::opfconst_0, this);
    m_handlers[FCONST_1]        = std::bind(&jjvm::opfconst_1, this);
    m_handlers[FCONST_2]        = std::bind(&jjvm::opfconst_2, this);
    m_handlers[DCONST_0]        = std::bind(&jjvm::opdconst_0, this);
    m_handlers[DCONST_1]        = std::bind(&jjvm::opdconst_1, this);
    m_handlers[BIPUSH]          = std::bind(&jjvm::opbipush, this);
    //m_handlers[SIPUSH]          = std::bind(&jjvm::opsipush, this);
    m_handlers[LDC]             = std::bind(&jjvm::opldc, this);
    m_handlers[LDC_W]           = std::bind(&jjvm::opldc_w, this);
    m_handlers[LDC2_W]          = std::bind(&jjvm::opldc2_w, this);
    m_handlers[ILOAD]           = std::bind(&jjvm::opiload, this);
    m_handlers[LLOAD]           = std::bind(&jjvm::oplload, this);
    m_handlers[FLOAD]           = std::bind(&jjvm::opiload, this);
    m_handlers[DLOAD]           = std::bind(&jjvm::oplload, this);
    m_handlers[ALOAD]           = std::bind(&jjvm::opiload, this);
    m_handlers[ILOAD_0]         = std::bind(&jjvm::opiload_0, this);
    m_handlers[ILOAD_1]         = std::bind(&jjvm::opiload_1, this);
    m_handlers[ILOAD_2]         = std::bind(&jjvm::opiload_2, this);
    m_handlers[ILOAD_3]         = std::bind(&jjvm::opiload_3, this);
    m_handlers[LLOAD_0]         = std::bind(&jjvm::oplload_0, this);
    m_handlers[LLOAD_1]         = std::bind(&jjvm::oplload_1, this);
    m_handlers[LLOAD_2]         = std::bind(&jjvm::oplload_2, this);
    m_handlers[LLOAD_3]         = std::bind(&jjvm::oplload_3, this);
    m_handlers[FLOAD_0]         = std::bind(&jjvm::opiload_0, this);
    m_handlers[FLOAD_1]         = std::bind(&jjvm::opiload_1, this);
    m_handlers[FLOAD_2]         = std::bind(&jjvm::opiload_2, this);
    m_handlers[FLOAD_3]         = std::bind(&jjvm::opiload_3, this);
    m_handlers[DLOAD_0]         = std::bind(&jjvm::oplload_0, this);
    m_handlers[DLOAD_1]         = std::bind(&jjvm::oplload_1, this);
    m_handlers[DLOAD_2]         = std::bind(&jjvm::oplload_2, this);
    m_handlers[DLOAD_3]         = std::bind(&jjvm::oplload_3, this);
    m_handlers[ALOAD_0]         = std::bind(&jjvm::opiload_0, this);
    m_handlers[ALOAD_1]         = std::bind(&jjvm::opiload_1, this);
    m_handlers[ALOAD_2]         = std::bind(&jjvm::opiload_2, this);
    m_handlers[ALOAD_3]         = std::bind(&jjvm::opiload_3, this);
    m_handlers[IALOAD]          = std::bind(&jjvm::opiaload, this);
    m_handlers[LALOAD]          = std::bind(&jjvm::oplaload, this);
    m_handlers[FALOAD]          = std::bind(&jjvm::opfaload, this);
    m_handlers[DALOAD]          = std::bind(&jjvm::opdaload, this);
    //m_handlers[AALOAD]          = std::bind(&jjvm::opaaload, this);
    m_handlers[BALOAD]          = std::bind(&jjvm::opiaload, this);
    m_handlers[CALOAD]          = std::bind(&jjvm::opiaload, this);
    m_handlers[SALOAD]          = std::bind(&jjvm::opiaload, this);
    m_handlers[ISTORE]          = std::bind(&jjvm::opistore, this);
    m_handlers[LSTORE]          = std::bind(&jjvm::oplstore, this);
    m_handlers[FSTORE]          = std::bind(&jjvm::opistore, this);
    m_handlers[DSTORE]          = std::bind(&jjvm::oplstore, this);
    m_handlers[ASTORE]          = std::bind(&jjvm::opistore, this);
    m_handlers[ISTORE_0]        = std::bind(&jjvm::opistore_0, this);
    m_handlers[ISTORE_1]        = std::bind(&jjvm::opistore_1, this);
    m_handlers[ISTORE_2]        = std::bind(&jjvm::opistore_2, this);
    m_handlers[ISTORE_3]        = std::bind(&jjvm::opistore_3, this);
    m_handlers[LSTORE_0]        = std::bind(&jjvm::oplstore_0, this);
    m_handlers[LSTORE_1]        = std::bind(&jjvm::oplstore_1, this);
    m_handlers[LSTORE_2]        = std::bind(&jjvm::oplstore_2, this);
    m_handlers[LSTORE_3]        = std::bind(&jjvm::oplstore_3, this);
    m_handlers[FSTORE_0]        = std::bind(&jjvm::opistore_0, this);
    m_handlers[FSTORE_1]        = std::bind(&jjvm::opistore_1, this);
    m_handlers[FSTORE_2]        = std::bind(&jjvm::opistore_2, this);
    m_handlers[FSTORE_3]        = std::bind(&jjvm::opistore_3, this);
    m_handlers[DSTORE_0]        = std::bind(&jjvm::oplstore_0, this);
    m_handlers[DSTORE_1]        = std::bind(&jjvm::oplstore_1, this);
    m_handlers[DSTORE_2]        = std::bind(&jjvm::oplstore_2, this);
    m_handlers[DSTORE_3]        = std::bind(&jjvm::oplstore_3, this);
    m_handlers[ASTORE_0]        = std::bind(&jjvm::opistore_0, this);
    m_handlers[ASTORE_1]        = std::bind(&jjvm::opistore_1, this);
    m_handlers[ASTORE_2]        = std::bind(&jjvm::opistore_2, this);
    m_handlers[ASTORE_3]        = std::bind(&jjvm::opistore_3, this);
    m_handlers[IASTORE]         = std::bind(&jjvm::opiastore, this);
    m_handlers[LASTORE]         = std::bind(&jjvm::oplastore, this);
    m_handlers[FASTORE]         = std::bind(&jjvm::opfastore, this);
    m_handlers[DASTORE]         = std::bind(&jjvm::opdastore, this);
    //m_handlers[AASTORE]         = std::bind(&jjvm::opaastore, this);
    m_handlers[BASTORE]         = std::bind(&jjvm::opiastore, this);
    m_handlers[CASTORE]         = std::bind(&jjvm::opiastore, this);
    m_handlers[SASTORE]         = std::bind(&jjvm::opiastore, this);
    m_handlers[POP]             = std::bind(&jjvm::oppop, this);
    m_handlers[POP2]            = std::bind(&jjvm::oppop2, this);
    m_handlers[DUP]             = std::bind(&jjvm::opdup, this);
    m_handlers[DUP_X1]          = std::bind(&jjvm::opdup_x1, this);
    m_handlers[DUP_X2]          = std::bind(&jjvm::opdup_x2, this);
    m_handlers[DUP2]            = std::bind(&jjvm::opdup2, this);
    m_handlers[DUP2_X1]         = std::bind(&jjvm::opdup2_x1, this);
    m_handlers[DUP2_X2]         = std::bind(&jjvm::opdup2_x2, this);
    m_handlers[SWAP]            = std::bind(&jjvm::opswap, this);
    m_handlers[IADD]            = std::bind(&jjvm::opiadd, this);
    m_handlers[LADD]            = std::bind(&jjvm::opladd, this);
    m_handlers[FADD]            = std::bind(&jjvm::opfadd, this);
    m_handlers[DADD]            = std::bind(&jjvm::opdadd, this);
    m_handlers[ISUB]            = std::bind(&jjvm::opisub, this);
    m_handlers[LSUB]            = std::bind(&jjvm::oplsub, this);
    m_handlers[FSUB]            = std::bind(&jjvm::opfsub, this);
    m_handlers[DSUB]            = std::bind(&jjvm::opdsub, this);
    m_handlers[IMUL]            = std::bind(&jjvm::opimul, this);
    m_handlers[LMUL]            = std::bind(&jjvm::oplmul, this);
    m_handlers[FMUL]            = std::bind(&jjvm::opfmul, this);
    m_handlers[DMUL]            = std::bind(&jjvm::opdmul, this);
    m_handlers[IDIV]            = std::bind(&jjvm::opidiv, this);
    m_handlers[LDIV]            = std::bind(&jjvm::opldiv, this);
    m_handlers[FDIV]            = std::bind(&jjvm::opfdiv, this);
    m_handlers[DDIV]            = std::bind(&jjvm::opddiv, this);
    m_handlers[IREM]            = std::bind(&jjvm::opirem, this);
    m_handlers[LREM]            = std::bind(&jjvm::oplrem, this);
    m_handlers[FREM]            = std::bind(&jjvm::opfrem, this);
    m_handlers[DREM]            = std::bind(&jjvm::opdrem, this);
    m_handlers[INEG]            = std::bind(&jjvm::opineg, this);
    m_handlers[LNEG]            = std::bind(&jjvm::oplneg, this);
    m_handlers[FNEG]            = std::bind(&jjvm::opfneg, this);
    m_handlers[DNEG]            = std::bind(&jjvm::opdneg, this);
    m_handlers[ISHL]            = std::bind(&jjvm::opishl, this);
    m_handlers[LSHL]            = std::bind(&jjvm::oplshl, this);
    m_handlers[ISHR]            = std::bind(&jjvm::opishr, this);
    m_handlers[LSHR]            = std::bind(&jjvm::oplshr, this);
    m_handlers[IUSHR]           = std::bind(&jjvm::opiushr, this);
    m_handlers[LUSHR]           = std::bind(&jjvm::oplushr, this);
    m_handlers[IAND]            = std::bind(&jjvm::opiand, this);
    m_handlers[LAND]            = std::bind(&jjvm::opland, this);
    m_handlers[IOR]             = std::bind(&jjvm::opior, this);
    m_handlers[LOR]             = std::bind(&jjvm::oplor, this);
    m_handlers[IXOR]            = std::bind(&jjvm::opixor, this);
    m_handlers[LXOR]            = std::bind(&jjvm::oplxor, this);
    m_handlers[IINC]            = std::bind(&jjvm::opiinc, this);
    m_handlers[I2L]             = std::bind(&jjvm::opi2l, this);
    m_handlers[I2F]             = std::bind(&jjvm::opi2f, this);
    m_handlers[I2D]             = std::bind(&jjvm::opi2d, this);
    m_handlers[L2I]             = std::bind(&jjvm::opl2i, this);
    m_handlers[L2F]             = std::bind(&jjvm::opl2f, this);
    m_handlers[L2D]             = std::bind(&jjvm::opl2d, this);
    m_handlers[F2I]             = std::bind(&jjvm::opf2i, this);
    m_handlers[F2L]             = std::bind(&jjvm::opf2l, this);
    m_handlers[F2D]             = std::bind(&jjvm::opf2d, this);
    m_handlers[D2I]             = std::bind(&jjvm::opd2i, this);
    m_handlers[D2L]             = std::bind(&jjvm::opd2l, this);
    m_handlers[D2F]             = std::bind(&jjvm::opd2f, this);
    //m_handlers[I2B]             = std::bind(&jjvm::opi2b, this);
    //m_handlers[I2C]             = std::bind(&jjvm::opi2c, this);
    //m_handlers[I2S]             = std::bind(&jjvm::opi2s, this);
    m_handlers[LCMP]            = std::bind(&jjvm::oplcmp, this);
    m_handlers[FCMPL]           = std::bind(&jjvm::opfcmpl, this);
    m_handlers[FCMPG]           = std::bind(&jjvm::opfcmpg, this);
    m_handlers[DCMPL]           = std::bind(&jjvm::opdcmpl, this);
    m_handlers[DCMPG]           = std::bind(&jjvm::opdcmpg, this);
    //m_handlers[IFEQ]            = std::bind(&jjvm::opifeq, this);
    m_handlers[IFNE]            = std::bind(&jjvm::opifne, this);
    //m_handlers[IFLT]            = std::bind(&jjvm::opiflt, this);
    //m_handlers[IFGE]            = std::bind(&jjvm::opifge, this);
    //m_handlers[IFGT]            = std::bind(&jjvm::opifgt, this);
    m_handlers[IFLE]            = std::bind(&jjvm::opifle, this);
    //m_handlers[IF_ICMPEQ]       = std::bind(&jjvm::opif_icmpeq, this);
    m_handlers[IF_ICMPNE]       = std::bind(&jjvm::opif_icmpne, this);
    //m_handlers[IF_ICMPLT]       = std::bind(&jjvm::opif_icmplt, this);
    m_handlers[IF_ICMPGE]       = std::bind(&jjvm::opif_icmpge, this);
    //m_handlers[IF_ICMPGT]       = std::bind(&jjvm::opif_icmpgt, this);
    //m_handlers[IF_ICMPLE]       = std::bind(&jjvm::opif_icmple, this);
    //m_handlers[IF_ACMPEQ]       = std::bind(&jjvm::opif_acmpeq, this);
    //m_handlers[IF_ACMPNE]       = std::bind(&jjvm::opif_acmpne, this);
    m_handlers[GOTO]            = std::bind(&jjvm::opgoto, this);
    //m_handlers[JSR]             = std::bind(&jjvm::opjsr, this);
    //m_handlers[RET]             = std::bind(&jjvm::opret, this);
    //m_handlers[TABLESWITCH]     = std::bind(&jjvm::optableswitch, this);
   // m_handlers[LOOKUPSWITCH]    = std::bind(&jjvm::oplookupswitch, this);
    m_handlers[IRETURN]         = std::bind(&jjvm::opireturn, this);
    m_handlers[LRETURN]         = std::bind(&jjvm::opireturn, this);
    m_handlers[FRETURN]         = std::bind(&jjvm::opireturn, this);
    m_handlers[DRETURN]         = std::bind(&jjvm::opireturn, this);
    m_handlers[ARETURN]         = std::bind(&jjvm::opireturn, this);
    m_handlers[RETURN]          = std::bind(&jjvm::opreturn, this);
    m_handlers[GETSTATIC]       = std::bind(&jjvm::opgetstatic, this);
    //m_handlers[PUTSTATIC]       = std::bind(&jjvm::opputstatic, this);
    m_handlers[GETFIELD]        = std::bind(&jjvm::opnop, this);
    m_handlers[PUTFIELD]        = std::bind(&jjvm::opnop, this);
    m_handlers[INVOKEVIRTUAL]   = std::bind(&jjvm::opinvokevirtual, this);
    m_handlers[INVOKESPECIAL]   = std::bind(&jjvm::opnop, this);
    m_handlers[INVOKESTATIC]    = std::bind(&jjvm::opinvokestatic, this);
    m_handlers[INVOKEINTERFACE] = std::bind(&jjvm::opnop, this);
    m_handlers[INVOKEDYNAMIC]   = std::bind(&jjvm::opnop, this);
    m_handlers[NEW]             = std::bind(&jjvm::opnop, this);
    m_handlers[NEWARRAY]        = std::bind(&jjvm::opnewarray, this);//TODO
    m_handlers[ANEWARRAY]       = std::bind(&jjvm::opnop, this);
    m_handlers[ARRAYLENGTH]     = std::bind(&jjvm::oparraylength, this);//TODO
    m_handlers[ATHROW]          = std::bind(&jjvm::opnop, this);
    m_handlers[CHECKCAST]       = std::bind(&jjvm::opnop, this);
    m_handlers[INSTANCEOF]      = std::bind(&jjvm::opnop, this);
    m_handlers[MONITORENTER]    = std::bind(&jjvm::opnop, this);
    m_handlers[MONITOREXIT]     = std::bind(&jjvm::opnop, this);
    m_handlers[WIDE]            = std::bind(&jjvm::opnop, this);
    //m_handlers[MULTIANEWARRAY]  = std::bind(&jjvm::opmultianewarray, this);
    //m_handlers[IFNULL]          = std::bind(&jjvm::opifnull, this);
    //m_handlers[IFNONNULL]       = std::bind(&jjvm::opifnonnull, this);
    //m_handlers[GOTO_W]          = std::bind(&jjvm::opgoto_w, this);
    //m_handlers[JSR_W]           = std::bind(&jjvm::opjsr_w, this);
}

} // namespace vm