#include "defuser.h"

#include <inttypes.h>
#include <stdio.h>

#define MAX_FIELDS 8

/*
 * 把 values 中的 count 个整数写成一行“空格分隔的无符号十进制整数”，存入 out。
 * 成功返回 0；count 为 0（还没有实现）、snprintf 出错或结果被截断时返回非零。
 */
static int write_answer(char *out, size_t cap, const uint32_t *values, size_t count) {
    size_t used = 0;
    for (size_t i = 0; i < count; ++i) {
        int size = snprintf(out + used, cap - used, "%s%" PRIu32, i ? " " : "", values[i]);
        if (size < 0 || (size_t)size >= cap - used) return 1;
        used += (size_t)size;
    }
    return count == 0;
}

int solve_phase_1(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;

    // TODO: 根据 phase_01 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    uint32_t lo  = (uint32_t)challenge;          // edi / r8d
    uint32_t hi  = (uint32_t)(challenge >> 32);  // shr rax,0x20
    uint32_t mid = (uint32_t)(challenge >> 16);  // shr rdx,0x10

    uint32_t a = (lo * 5u) ^ (hi + 0xd209u);     // p1_step0(lo, hi)
    uint32_t b = (hi - mid) * 5u + 0xef90u;      // p1_step1(hi, mid)
    uint32_t c = (lo + 0x510du) ^ b;             // p1_step2(b, lo)
    values[0] = c ^ a;                           // xor eax,ecx
    count = 1;                                   // valid_u32_fields(input, 1)
    return write_answer(out, cap, values, count);
}

int solve_phase_2(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;

    // TODO: 根据 phase_02 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    values[0] = (uint32_t)((challenge >> 47) & 0x7f);       // shr 0x2f; and 0x7f
    for (unsigned i = 1; i < 6; ++i) {
        uint32_t bits = (uint32_t)((challenge >> (20 + i)) & 0x3f);  // shr cl; and 0x3f
        values[i] = (values[i - 1] + bits) ^ (6u * i);       // add esi; xor edi
    }
    count = 6;                                               // valid_u32_fields(input, 6)
    return write_answer(out, cap, values, count);
}

int solve_phase_3(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;

    // TODO: 根据 phase_03 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    uint32_t k = (uint32_t)challenge & 7u;                                // and edi,0x7
    uint32_t x = (uint32_t)(challenge >> 32) ^ (uint32_t)(challenge >> 3); // xor esi,eax
    values[0] = k;
    switch (k) {
    case 0: {
        values[1] = (x ^ 0x4272u) + (x >> 1);   // 表[0] -> p3_case_6
        break;
    }
    case 1: {
        values[1] = x * 5u + 0xb679u;           // 表[1] -> p3_case_1
        break;
    }
    case 2: {
        values[1] = (x * 2u) ^ 0x10e9u;         // 表[2] -> p3_case_3
        break;
    }
    case 3: {
        values[1] = (x ^ 0x9ed2u) + (x >> 1);   // 表[3] -> p3_case_2
        break;
    }
    case 4: {
        values[1] = x * 5u + 0x41a5au;          // 表[4] -> p3_case_0
        break;
    }
    case 5: {
        values[1] = x * 3u + 0x1757u;           // 表[5] -> p3_case_4
        break;
    }
    case 6: {
        values[1] = (x * 4u) ^ 8u;              // 表[6] -> p3_case_5
        break;
    }
    default: {
        values[1] = x * 5u + 0x20116u;         // 表[7] -> p3_case_7
        break;
    }
    }
    count = 2;
    
    return write_answer(out, cap, values, count);
}

// p4_walk：二分查找，返回途中逐层折叠
static uint32_t p4_walk(uint32_t target, uint32_t lo, uint32_t hi, uint32_t key) {
    uint32_t mid = lo + ((hi - lo) >> 1);                 // sub; shr 1; add
    if (mid == target) {
        return (mid + 0xdfu) ^ key;        // 递归出口
    }
    uint32_t r;
    if (target < mid) {                                    // jb：往左
        r = p4_walk(target, lo, mid - 1u, key);
        return ((r * 5u) ^ (mid + key)) ^ 0x1au;
    }
    r = p4_walk(target, mid + 1u, hi, key);                // 往右
    return ((r * 5u) ^ (mid + key)) ^ 0x17u;
}

int solve_phase_4(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;

    // TODO: 根据 phase_04 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    uint32_t target = (uint32_t)challenge & 0x7fu;
    uint32_t key = (uint32_t)(challenge >> 7) ^ (uint32_t)(challenge >> 32);
    values[0] = p4_walk(target, 0u, 0x7fu, key);
    count = 1;
    return write_answer(out, cap, values, count);
}

struct p5_node { uint32_t val; uint32_t tag; int next; };
    static const struct p5_node P5_NODES[12] = {
    {0xdbd5u, 0x27fu,  1}, {0xa2cfu, 0x66cu, -1}, {0xd64eu, 0x560u, 11},
    {0xfedau, 0xb78u,  6}, {0x3698u, 0xa7au,  3}, {0x11c3u, 0x787u,  0},
    {0x227cu, 0x003u, 10}, {0xf687u, 0x112u,  4}, {0x8526u, 0x94fu,  9},
    {0x8840u, 0x869u,  7}, {0xdd58u, 0x347u,  2}, {0xb7c1u, 0x453u,  5},
};
static const int P5_HEADS[8] = {8, 9, 7, 4, 3, 6, 10, 2};

int solve_phase_5(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;

    // TODO: 根据 phase_05 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    int n = P5_HEADS[challenge & 7u];
    uint32_t steps = (uint32_t)(challenge >> 3) & 3u;
    uint32_t acc = ((uint32_t)(challenge >> 6) ^ (uint32_t)(challenge >> 32)) ^ 0x88f9u;

    acc = (acc * 3u + P5_NODES[n].val) ^ P5_NODES[n].tag;   // 第一个节点
    uint32_t last = P5_NODES[n].tag;
    for (uint32_t i = 1; i <= steps; ++i) {                  // 再走 steps 步
        n = P5_NODES[n].next;
        acc = (acc * 3u + P5_NODES[n].val) ^ P5_NODES[n].tag;
        last = P5_NODES[n].tag;
    }
    values[0] = acc;
    values[1] = last;
    count = 2;
    return write_answer(out, cap, values, count);
}

// p6_op_0 ~ p6_op_5
static uint32_t p6_op(unsigned id, uint32_t x) {
    switch (id) {
    case 0: return (x + 0x419fu) ^ (x >> 3);
    case 1: return ((x >> 5) ^ x) + 0x37b2u;
    case 2: return (x >> 5) | (x << 27);                 // ror 5
    case 3: return ((x << 1) | (x >> 31)) ^ 0xb6d8u;     // rol 1
    case 4: return (x ^ 0xbdbfu) + x * 8u;
    default: return ((x << 7) + 0x1794u) ^ (x * 7u);     // op_5
    }
}
/* p6_ops 表（0x405e00），从 GDB x/8a 读出 */
static const unsigned P6_OPS[8] = {5, 1, 5, 0, 4, 2, 3, 2};

int solve_phase_6(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;

    // TODO: 根据 phase_06 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    uint32_t x = (uint32_t)(challenge >> 6) ^ (uint32_t)(challenge >> 32);
    uint32_t r = p6_op(P6_OPS[challenge & 7u], x) ^ 0xf22fu;   // 第一次间接调用
    r = p6_op(P6_OPS[(challenge >> 3) & 7u], r) + 0xd9adu;     // 第二次：c & 0x38 → (c>>3)&7
    values[0] = r;
    count = 1;

    return write_answer(out, cap, values, count);
}

int solve_secret(uint64_t challenge, uint64_t context, char *out, size_t cap) {
    // TODO（选做）: 根据 secret_gate、secret_copy 和 secret_phase 的汇编构造完整的第七行，写入 out 后返回 0。
    // 第七行不一定只有整数，可以直接用 snprintf 写入；还没完成时保持返回 1，测试会显示 not attempted。
    uint32_t k = (uint32_t)context & 3u;                                   // a
    uint32_t S = (uint32_t)(challenge >> 32) ^ (uint32_t)challenge;
    uint32_t T = (uint32_t)(context >> 32) ^ (uint32_t)context;
    uint32_t r9 = (k * 0xad24u) ^ (uint32_t)(context >> 16);

    uint32_t y = S ^ T;
    uint32_t m = (((y << 3) | (y >> 29)) + 0xad24u) ^ 0x806au;             // secret_mix
    uint32_t b = m ^ r9;
    uint32_t c = b ^ (T + k + 0x806au + (S >> 3));

    /* secret_gate：32 字节填充 + "OPEN"（小端 0x4e45504f）+ 三个数 */
    int n = snprintf(out, cap, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAOPEN%" PRIu32 " %" PRIu32 " %" PRIu32,k, b, c);
    if (n < 0 || (size_t)n >= cap) return 1;
    return 0;
}
