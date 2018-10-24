//
//  TestReeferenceWrapper.h
//  GinsengProject
//
//  Created by Daniel Shiposha on 14/07/2018.
//

#ifndef TestReeferenceWrapper_h
#define TestReeferenceWrapper_h

#include <IsReferenceWrapper.h>

namespace ggmeta = metaxxa;

TEST(TestMeta, TestReferenceWrapper)
{
    EXPECT_TRUE(ggmeta::IsReferenceWrapper<std::reference_wrapper<int>>);
    EXPECT_FALSE(ggmeta::IsReferenceWrapper<int>);
}

#endif /* TestReeferenceWrapper_h */
