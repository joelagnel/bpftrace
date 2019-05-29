#include "common.h"

namespace bpftrace {
namespace test {
namespace codegen {

TEST(codegen, call_cat)
{
  test("kprobe:f { cat(\"/proc/loadavg\"); }",

R"EXPECTED(%bpf_map = type opaque

; Function Attrs: nounwind
declare i64 @llvm.bpf.pseudo(i64, i64) #0

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

define i64 @"kprobe:f"(i8*) local_unnamed_addr section "s_kprobe:f_1" {
entry:
  %perfdata = alloca [16 x i8], align 8
  %1 = getelementptr inbounds [16 x i8], [16 x i8]* %perfdata, i64 0, i64 0
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %1)
  store i64 20006, [16 x i8]* %perfdata, align 8
  %2 = getelementptr inbounds [16 x i8], [16 x i8]* %perfdata, i64 0, i64 8
  store i64 0, i8* %2, align 8
  %pseudo = tail call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %get_cpu_id = tail call i64 inttoptr (i64 8 to i64 ()*)()
  %perf_event_output = call i64 inttoptr (i64 25 to i64 (i8*, %bpf_map*, i64, [16 x i8]*, i64)*)(i8* %0, %bpf_map* %bpf_map_ptr, i64 %get_cpu_id, [16 x i8]* nonnull %perfdata, i64 16)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %1)
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
