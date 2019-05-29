#include "common.h"

namespace bpftrace {
namespace test {
namespace codegen {

TEST(codegen, call_print)
{
  test("BEGIN { @x = 1; } kprobe:f { print(@x); }",

#if LLVM_VERSION_MAJOR > 6
R"EXPECTED(%bpf_map = type opaque

; Function Attrs: nounwind
declare i64 @llvm.bpf.pseudo(i64, i64) #0

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

define i64 @BEGIN(i8* nocapture readnone) local_unnamed_addr section "s_BEGIN_1" {
entry:
  %"@x_val" = alloca i64, align 8
  %"@x_key" = alloca i64, align 8
  %1 = bitcast i64* %"@x_key" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %1)
  store i64 0, i64* %"@x_key", align 8
  %2 = bitcast i64* %"@x_val" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %2)
  store i64 1, i64* %"@x_val", align 8
  %pseudo = tail call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %update_elem = call i64 inttoptr (i64 2 to i64 (%bpf_map*, i8*, i8*, i64)*)(%bpf_map* %bpf_map_ptr, i64* nonnull %"@x_key", i64* nonnull %"@x_val", i64 0)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %1)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %2)
  ret i64 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end.p0i8(i64, i8* nocapture) #1

define i64 @"kprobe:f"(i8*) local_unnamed_addr section "s_kprobe:f_1" {
entry:
  %perfdata = alloca [27 x i8], align 8
  %1 = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 0
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %1)
  store i64 20001, [27 x i8]* %perfdata, align 8
  %2 = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 8
  %str.sroa.0.0..sroa_idx = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 24
  call void @llvm.memset.p0i8.i64(i8* nonnull align 8 %2, i8 0, i64 16, i1 false)
  store i8 64, i8* %str.sroa.0.0..sroa_idx, align 8
  %str.sroa.4.0..sroa_idx = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 25
  store i8 120, i8* %str.sroa.4.0..sroa_idx, align 1
  %str.sroa.5.0..sroa_idx = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 26
  store i8 0, i8* %str.sroa.5.0..sroa_idx, align 2
  %pseudo = tail call i64 @llvm.bpf.pseudo(i64 1, i64 2)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %get_cpu_id = tail call i64 inttoptr (i64 8 to i64 ()*)()
  %perf_event_output = call i64 inttoptr (i64 25 to i64 (i8*, %bpf_map*, i64, [27 x i8]*, i64)*)(i8* %0, %bpf_map* %bpf_map_ptr, i64 %get_cpu_id, [27 x i8]* nonnull %perfdata, i64 27)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %1)
  ret i64 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1) #1

attributes #0 = { nounwind }
attributes #1 = { argmemonly nounwind }
)EXPECTED");
#elif LLVM_VERSION_MAJOR == 6
R"EXPECTED(%bpf_map = type opaque

; Function Attrs: nounwind
declare i64 @llvm.bpf.pseudo(i64, i64) #0

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

define i64 @BEGIN(i8* nocapture readnone) local_unnamed_addr section "s_BEGIN_1" {
entry:
  %"@x_val" = alloca i64, align 8
  %"@x_key" = alloca i64, align 8
  %1 = bitcast i64* %"@x_key" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %1)
  store i64 0, i64* %"@x_key", align 8
  %2 = bitcast i64* %"@x_val" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %2)
  store i64 1, i64* %"@x_val", align 8
  %pseudo = tail call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %update_elem = call i64 inttoptr (i64 2 to i64 (%bpf_map*, i8*, i8*, i64)*)(%bpf_map* %bpf_map_ptr, i64* nonnull %"@x_key", i64* nonnull %"@x_val", i64 0)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %1)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %2)
  ret i64 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end.p0i8(i64, i8* nocapture) #1

define i64 @"kprobe:f"(i8*) local_unnamed_addr section "s_kprobe:f_1" {
entry:
  %perfdata = alloca [27 x i8], align 8
  %1 = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 0
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %1)
  store i64 20001, [27 x i8]* %perfdata, align 8
  %2 = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 8
  %str.sroa.0.0..sroa_idx = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 24
  call void @llvm.memset.p0i8.i64(i8* nonnull %2, i8 0, i64 16, i32 8, i1 false)
  store i8 64, i8* %str.sroa.0.0..sroa_idx, align 8
  %str.sroa.4.0..sroa_idx = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 25
  store i8 120, i8* %str.sroa.4.0..sroa_idx, align 1
  %str.sroa.5.0..sroa_idx = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 26
  store i8 0, i8* %str.sroa.5.0..sroa_idx, align 2
  %pseudo = tail call i64 @llvm.bpf.pseudo(i64 1, i64 2)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %get_cpu_id = tail call i64 inttoptr (i64 8 to i64 ()*)()
  %perf_event_output = call i64 inttoptr (i64 25 to i64 (i8*, %bpf_map*, i64, [27 x i8]*, i64)*)(i8* %0, %bpf_map* %bpf_map_ptr, i64 %get_cpu_id, [27 x i8]* nonnull %perfdata, i64 27)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %1)
  ret i64 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i32, i1) #1

attributes #0 = { nounwind }
attributes #1 = { argmemonly nounwind }
)EXPECTED");
#else
R"EXPECTED(%bpf_map = type opaque

; Function Attrs: nounwind
declare i64 @llvm.bpf.pseudo(i64, i64) #0

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

define i64 @BEGIN(i8* nocapture readnone) local_unnamed_addr section "s_BEGIN_1" {
entry:
  %"@x_val" = alloca i64, align 8
  %"@x_key" = alloca i64, align 8
  %1 = bitcast i64* %"@x_key" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %1)
  store i64 0, i64* %"@x_key", align 8
  %2 = bitcast i64* %"@x_val" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %2)
  store i64 1, i64* %"@x_val", align 8
  %pseudo = tail call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %update_elem = call i64 inttoptr (i64 2 to i64 (%bpf_map*, i8*, i8*, i64)*)(%bpf_map* %bpf_map_ptr, i64* nonnull %"@x_key", i64* nonnull %"@x_val", i64 0)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %1)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %2)
  ret i64 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end.p0i8(i64, i8* nocapture) #1

define i64 @"kprobe:f"(i8*) local_unnamed_addr section "s_kprobe:f_1" {
entry:
  %perfdata = alloca [27 x i8], align 8
  %1 = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 0
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %1)
  store i64 20001, [27 x i8]* %perfdata, align 8
  %2 = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 8
  %str.sroa.0.0..sroa_idx = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 24
  call void @llvm.memset.p0i8.i64(i8* %2, i8 0, i64 16, i32 8, i1 false)
  store i8 64, i8* %str.sroa.0.0..sroa_idx, align 8
  %str.sroa.4.0..sroa_idx = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 25
  store i8 120, i8* %str.sroa.4.0..sroa_idx, align 1
  %str.sroa.5.0..sroa_idx = getelementptr inbounds [27 x i8], [27 x i8]* %perfdata, i64 0, i64 26
  store i8 0, i8* %str.sroa.5.0..sroa_idx, align 2
  %pseudo = tail call i64 @llvm.bpf.pseudo(i64 1, i64 2)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %get_cpu_id = tail call i64 inttoptr (i64 8 to i64 ()*)()
  %perf_event_output = call i64 inttoptr (i64 25 to i64 (i8*, %bpf_map*, i64, [27 x i8]*, i64)*)(i8* %0, %bpf_map* %bpf_map_ptr, i64 %get_cpu_id, [27 x i8]* nonnull %perfdata, i64 27)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %1)
  ret i64 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i32, i1) #1

attributes #0 = { nounwind }
attributes #1 = { argmemonly nounwind }
)EXPECTED");
#endif
}

} // namespace codegen
} // namespace test
} // namespace bpftrace
