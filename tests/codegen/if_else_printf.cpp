#include "common.h"

namespace bpftrace {
namespace test {
namespace codegen {

TEST(codegen, if_else_printf)
{
  test("kprobe:f { if (pid > 10) { printf(\"hi\\n\"); } else {printf(\"hello\\n\")} }",

R"EXPECTED(%printf_t.0 = type { i64 }
%printf_t = type { i64 }
%bpf_map = type opaque

; Function Attrs: nounwind
declare i64 @llvm.bpf.pseudo(i64, i64) #0

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

define i64 @"kprobe:f"(i8*) local_unnamed_addr section "s_kprobe:f_1" {
entry:
  %printf_args1 = alloca %printf_t.0, align 8
  %printf_args = alloca %printf_t, align 8
  %get_pid_tgid = tail call i64 inttoptr (i64 14 to i64 ()*)()
  %1 = icmp ugt i64 %get_pid_tgid, 47244640255
  br i1 %1, label %if_stmt, label %else_stmt

if_stmt:                                          ; preds = %entry
  %2 = bitcast %printf_t* %printf_args to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %2)
  %3 = getelementptr inbounds %printf_t, %printf_t* %printf_args, i64 0, i32 0
  store i64 0, i64* %3, align 8
  %pseudo = tail call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %get_cpu_id = tail call i64 inttoptr (i64 8 to i64 ()*)()
  %perf_event_output = call i64 inttoptr (i64 25 to i64 (i8*, %bpf_map*, i64, %printf_t*, i64)*)(i8* %0, %bpf_map* %bpf_map_ptr, i64 %get_cpu_id, %printf_t* nonnull %printf_args, i64 8)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %2)
  br label %done

else_stmt:                                        ; preds = %entry
  %4 = bitcast %printf_t.0* %printf_args1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %4)
  %5 = getelementptr inbounds %printf_t.0, %printf_t.0* %printf_args1, i64 0, i32 0
  store i64 1, i64* %5, align 8
  %pseudo2 = tail call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr3 = inttoptr i64 %pseudo2 to %bpf_map*
  %get_cpu_id4 = tail call i64 inttoptr (i64 8 to i64 ()*)()
  %perf_event_output5 = call i64 inttoptr (i64 25 to i64 (i8*, %bpf_map*, i64, %printf_t.0*, i64)*)(i8* %0, %bpf_map* %bpf_map_ptr3, i64 %get_cpu_id4, %printf_t.0* nonnull %printf_args1, i64 8)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %4)
  br label %done

done:                                             ; preds = %else_stmt, %if_stmt
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
