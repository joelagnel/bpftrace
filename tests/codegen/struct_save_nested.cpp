#include "common.h"

namespace bpftrace {
namespace test {
namespace codegen {

TEST(codegen, struct_save_nested)
{
  auto expected = R"EXPECTED(%bpf_map = type opaque

; Function Attrs: nounwind
declare i64 @llvm.bpf.pseudo(i64, i64) #0

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

define i64 @"kprobe:f"(i8* nocapture readnone) local_unnamed_addr section "s_kprobe:f_1" {
entry:
  %"@x_val" = alloca i64, align 8
  %"@x_key" = alloca i64, align 8
  %"@foo_key7" = alloca i64, align 8
  %"@bar_key" = alloca i64, align 8
  %internal_Foo.bar = alloca i64, align 8
  %tmpcast = bitcast i64* %internal_Foo.bar to [8 x i8]*
  %"@foo_key1" = alloca i64, align 8
  %"@foo_val" = alloca [16 x i8], align 1
  %"@foo_key" = alloca i64, align 8
  %1 = bitcast i64* %"@foo_key" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %1)
  store i64 0, i64* %"@foo_key", align 8
  %2 = getelementptr inbounds [16 x i8], [16 x i8]* %"@foo_val", i64 0, i64 0
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %2)
  %probe_read = call i64 inttoptr (i64 4 to i64 (i8*, i64, i8*)*)([16 x i8]* nonnull %"@foo_val", i64 16, i64 0)
  %pseudo = call i64 @llvm.bpf.pseudo(i64 1, i64 2)
  %bpf_map_ptr = inttoptr i64 %pseudo to %bpf_map*
  %update_elem = call i64 inttoptr (i64 2 to i64 (%bpf_map*, i8*, i8*, i64)*)(%bpf_map* %bpf_map_ptr, i64* nonnull %"@foo_key", [16 x i8]* nonnull %"@foo_val", i64 0)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %1)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %2)
  %3 = bitcast i64* %"@foo_key1" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %3)
  store i64 0, i64* %"@foo_key1", align 8
  %pseudo2 = call i64 @llvm.bpf.pseudo(i64 1, i64 2)
  %bpf_map_ptr3 = inttoptr i64 %pseudo2 to %bpf_map*
  %lookup_elem = call i8* inttoptr (i64 1 to i8* (%bpf_map*, i8*)*)(%bpf_map* %bpf_map_ptr3, i64* nonnull %"@foo_key1")
  %map_lookup_cond = icmp eq i8* %lookup_elem, null
  br i1 %map_lookup_cond, label %lookup_merge, label %lookup_success

lookup_success:                                   ; preds = %entry
  %lookup_elem_val.sroa.3.0.lookup_elem.sroa_idx = getelementptr inbounds i8, i8* %lookup_elem, i64 4
  %lookup_elem_val.sroa.3.0.lookup_elem.sroa_cast = bitcast i8* %lookup_elem_val.sroa.3.0.lookup_elem.sroa_idx to i64*
  %lookup_elem_val.sroa.3.0.copyload = load i64, i64* %lookup_elem_val.sroa.3.0.lookup_elem.sroa_cast, align 1
  br label %lookup_merge

lookup_merge:                                     ; preds = %entry, %lookup_success
  %lookup_elem_val.sroa.3.0 = phi i64 [ %lookup_elem_val.sroa.3.0.copyload, %lookup_success ], [ 0, %entry ]
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %3)
  %4 = bitcast i64* %internal_Foo.bar to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %4)
  store i64 %lookup_elem_val.sroa.3.0, i64* %internal_Foo.bar, align 8
  %5 = bitcast i64* %"@bar_key" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %5)
  store i64 0, i64* %"@bar_key", align 8
  %pseudo4 = call i64 @llvm.bpf.pseudo(i64 1, i64 1)
  %bpf_map_ptr5 = inttoptr i64 %pseudo4 to %bpf_map*
  %update_elem6 = call i64 inttoptr (i64 2 to i64 (%bpf_map*, i8*, i8*, i64)*)(%bpf_map* %bpf_map_ptr5, i64* nonnull %"@bar_key", [8 x i8]* nonnull %tmpcast, i64 0)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %5)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %4)
  %6 = bitcast i64* %"@foo_key7" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %6)
  store i64 0, i64* %"@foo_key7", align 8
  %pseudo8 = call i64 @llvm.bpf.pseudo(i64 1, i64 2)
  %bpf_map_ptr9 = inttoptr i64 %pseudo8 to %bpf_map*
  %lookup_elem10 = call i8* inttoptr (i64 1 to i8* (%bpf_map*, i8*)*)(%bpf_map* %bpf_map_ptr9, i64* nonnull %"@foo_key7")
  %map_lookup_cond15 = icmp eq i8* %lookup_elem10, null
  br i1 %map_lookup_cond15, label %lookup_merge13, label %lookup_success11

lookup_success11:                                 ; preds = %lookup_merge
  %lookup_elem_val14.sroa.3.0.lookup_elem10.sroa_idx = getelementptr inbounds i8, i8* %lookup_elem10, i64 4
  %lookup_elem_val14.sroa.3.0.lookup_elem10.sroa_cast = bitcast i8* %lookup_elem_val14.sroa.3.0.lookup_elem10.sroa_idx to i64*
  %lookup_elem_val14.sroa.3.0.copyload = load i64, i64* %lookup_elem_val14.sroa.3.0.lookup_elem10.sroa_cast, align 1
  %phitmp21 = and i64 %lookup_elem_val14.sroa.3.0.copyload, 4294967295
  br label %lookup_merge13

lookup_merge13:                                   ; preds = %lookup_merge, %lookup_success11
  %lookup_elem_val14.sroa.3.0 = phi i64 [ %phitmp21, %lookup_success11 ], [ 0, %lookup_merge ]
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %6)
  %7 = bitcast i64* %"@x_key" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %7)
  store i64 0, i64* %"@x_key", align 8
  %8 = bitcast i64* %"@x_val" to i8*
  call void @llvm.lifetime.start.p0i8(i64 -1, i8* nonnull %8)
  store i64 %lookup_elem_val14.sroa.3.0, i64* %"@x_val", align 8
  %pseudo17 = call i64 @llvm.bpf.pseudo(i64 1, i64 3)
  %bpf_map_ptr18 = inttoptr i64 %pseudo17 to %bpf_map*
  %update_elem19 = call i64 inttoptr (i64 2 to i64 (%bpf_map*, i8*, i8*, i64)*)(%bpf_map* %bpf_map_ptr18, i64* nonnull %"@x_key", i64* nonnull %"@x_val", i64 0)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %7)
  call void @llvm.lifetime.end.p0i8(i64 -1, i8* nonnull %8)
  ret i64 0
}

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end.p0i8(i64, i8* nocapture) #1

attributes #0 = { nounwind }
attributes #1 = { argmemonly nounwind }
)EXPECTED";

  test("struct Foo { int m; struct { int x; int y; } bar; int n; }"
       "kprobe:f"
       "{"
       "  @foo = (Foo)0;"
       "  @bar = @foo.bar;"
       "  @x = @foo.bar.x;"
       "}",
       expected);
}

} // namespace codegen
} // namespace test
} // namespace bpftrace
