#include "common.h"

namespace bpftrace {
namespace test {
namespace codegen {

TEST(codegen, builtin_ustack)
{
  test("kprobe:f { @x = ustack }",

R"EXPECTED(%bpf_map = type opaque

; Function Attrs: nounwind
declare i64 @llvm.bpf.pseudo(i64, i64) #0

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

define i64 @"kprobe:f"(i8*) local_unnamed_addr section "s_kprobe:f_1" {
entry:
  %"@x_val" = alloca i64, align 8
  %"@x_key" = alloca i64, align 8
  %pseudo = tail call i64 @llvm.bpf.pseudo(i64 1, i64 2)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %get_stackid = tail call i64 inttoptr (i64 27 to i64 (i8*, %bpf_map*, i64)*)(i8* %0, %bpf_map* %bpf_map_ptr, i64 256)
  %get_pid_tgid = tail call i64 inttoptr (i64 14 to i64 ()*)()
  %1 = shl i64 %get_pid_tgid, 32
  %2 = or i64 %1, %get_stackid
  %3 = bitcast i64* %"@x_key" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %3)
  store i64 0, i64* %"@x_key", align 8
  %4 = bitcast i64* %"@x_val" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %4)
  store i64 %2, i64* %"@x_val", align 8
  %pseudo1 = tail call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr2 = inttoptr i64 %pseudo1 to %bpf_map*
  %update_elem = call i64 inttoptr (i64 2 to i64 (%bpf_map*, i8*, i8*, i64)*)(%bpf_map* %bpf_map_ptr2, i64* nonnull %"@x_key", i64* nonnull %"@x_val", i64 0)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %3)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %4)
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
