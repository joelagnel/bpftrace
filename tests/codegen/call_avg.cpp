#include "common.h"

namespace bpftrace {
namespace test {
namespace codegen {

TEST(codegen, call_avg)
{
  test("kprobe:f { @x = avg(pid) }",

R"EXPECTED(%bpf_map = type opaque

; Function Attrs: nounwind
declare i64 @llvm.bpf.pseudo(i64, i64) #0

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

define i64 @"kprobe:f"(i8* nocapture readnone) local_unnamed_addr section "s_kprobe:f_1" {
entry:
  %"@x_val" = alloca i64, align 8
  %"@x_key3" = alloca i64, align 8
  %"@x_num" = alloca i64, align 8
  %"@x_key" = alloca i64, align 8
  %1 = bitcast i64* %"@x_key" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %1)
  store i64 0, i64* %"@x_key", align 8
  %pseudo = tail call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %lookup_elem = call i8* inttoptr (i64 1 to i8* (%bpf_map*, i8*)*)(%bpf_map* %bpf_map_ptr, i64* nonnull %"@x_key")
  %map_lookup_cond = icmp eq i8* %lookup_elem, null
  br i1 %map_lookup_cond, label %lookup_merge, label %lookup_success

lookup_success:                                   ; preds = %entry
  %2 = load i64, i8* %lookup_elem, align 8
  %phitmp = add i64 %2, 1
  br label %lookup_merge

lookup_merge:                                     ; preds = %entry, %lookup_success
  %lookup_elem_val.0 = phi i64 [ %phitmp, %lookup_success ], [ 1, %entry ]
  %3 = bitcast i64* %"@x_num" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %3)
  store i64 %lookup_elem_val.0, i64* %"@x_num", align 8
  %pseudo1 = call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr2 = inttoptr i64 %pseudo1 to %bpf_map*
  %update_elem = call i64 inttoptr (i64 2 to i64 (%bpf_map*, i8*, i8*, i64)*)(%bpf_map* %bpf_map_ptr2, i64* nonnull %"@x_key", i64* nonnull %"@x_num", i64 0)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %1)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %3)
  %4 = bitcast i64* %"@x_key3" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %4)
  store i64 1, i64* %"@x_key3", align 8
  %pseudo4 = call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr5 = inttoptr i64 %pseudo4 to %bpf_map*
  %lookup_elem6 = call i8* inttoptr (i64 1 to i8* (%bpf_map*, i8*)*)(%bpf_map* %bpf_map_ptr5, i64* nonnull %"@x_key3")
  %map_lookup_cond11 = icmp eq i8* %lookup_elem6, null
  br i1 %map_lookup_cond11, label %lookup_merge9, label %lookup_success7

lookup_success7:                                  ; preds = %lookup_merge
  %5 = load i64, i8* %lookup_elem6, align 8
  br label %lookup_merge9

lookup_merge9:                                    ; preds = %lookup_merge, %lookup_success7
  %lookup_elem_val10.0 = phi i64 [ %5, %lookup_success7 ], [ 0, %lookup_merge ]
  %6 = bitcast i64* %"@x_val" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %6)
  %get_pid_tgid = call i64 inttoptr (i64 14 to i64 ()*)()
  %7 = lshr i64 %get_pid_tgid, 32
  %8 = add i64 %7, %lookup_elem_val10.0
  store i64 %8, i64* %"@x_val", align 8
  %pseudo12 = call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr13 = inttoptr i64 %pseudo12 to %bpf_map*
  %update_elem14 = call i64 inttoptr (i64 2 to i64 (%bpf_map*, i8*, i8*, i64)*)(%bpf_map* %bpf_map_ptr13, i64* nonnull %"@x_key3", i64* nonnull %"@x_val", i64 0)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %4)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %6)
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
