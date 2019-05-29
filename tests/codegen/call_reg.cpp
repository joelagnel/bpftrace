#include "common.h"

namespace bpftrace {
namespace test {
namespace codegen {

TEST(codegen, call_reg) // Identical to builtin_func apart from variable names
{
  test("kprobe:f { @x = reg(\"ip\") }",

R"EXPECTED(%bpf_map = type opaque

; Function Attrs: nounwind
declare i64 @llvm.bpf.pseudo(i64, i64) #0

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

define i64 @"kprobe:f"(i8*) local_unnamed_addr section "s_kprobe:f_1" {
entry:
  %"@x_val" = alloca i64, align 8
  %"@x_key" = alloca i64, align 8
  %reg_ip = alloca i64, align 8
  %1 = bitcast i64* %reg_ip to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %1)
  %2 = getelementptr i8, i8* %0, i64 128
  %probe_read = call i64 inttoptr (i64 4 to i64 (i8*, i64, i8*)*)(i64* nonnull %reg_ip, i64 8, i8* %2)
  %3 = load i64, i64* %reg_ip, align 8
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %1)
  %4 = bitcast i64* %"@x_key" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %4)
  store i64 0, i64* %"@x_key", align 8
  %5 = bitcast i64* %"@x_val" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %5)
  store i64 %3, i64* %"@x_val", align 8
  %pseudo = call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %update_elem = call i64 inttoptr (i64 2 to i64 (%bpf_map*, i8*, i8*, i64)*)(%bpf_map* %bpf_map_ptr, i64* nonnull %"@x_key", i64* nonnull %"@x_val", i64 0)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %4)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %5)
  ret i64 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end.p0i8(i64, i8* nocapture) #1

attributes #0 = { nounwind }
attributes #1 = { argmemonly nounwind }
)EXPECTED");
}

} // namespace codegen
} // namespace test
} // namespace bpftrace
