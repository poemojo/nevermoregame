#pragma once

#define STRING std::string
#define     DS /
#define     ES .

#define    NADDA(x)    x

#define  SJOIN_X(s, x, y) x ## s ## y
#define    SJOIN(s, x, y) SJOIN_X(s, x, y)

#define   JOIN_X(x, y) x ## _ ## y
#define     JOIN(x, y) JOIN_X(x, y)

#define CONCAT2_X(a, b) a ## b
#define   CONCAT2(a, b) CONCAT2_X(a,b)

#define CONCAT3_X(a, b, c) CONCAT2(a, b) ## c
#define   CONCAT3(a, b, c) CONCAT3_X(a,b,c)

#define CONCAT4_X(a, b, c, d) CONCAT3(a, b, c) ## d
#define   CONCAT4(a, b, c, d) CONCAT4_X(a, b, c, d)

#define CONCAT5_X(a, b, c, d, e) CONCAT4(a, b, c, d) ## e
#define   CONCAT5(a, b, c, d, e) CONCAT5_X(a, b, c, d, e)

#define MCONCAT(a, ...) _VARG5(a, __VA_ARGS__, CONCAT5, CONCAT4, CONCAT3, CONCAT2)(a, __VA_ARGS__)



#define  QUOTE_X(x)    #x
#define    QUOTE(x)    QUOTE_X(x)

#define CONCAT_X(x, y) x ## y
#define   CONCAT(x, y) CONCAT_X(x, y)


#define   DCAT_X(x)    x ## x
#define     DCAT(x)    DCAT_X(x)


#define    CMT_X(str)  CONCAT(DCAT(/), str)
#define      CMT(str)  CMT_X(str)

#define UINTID_X(N)    CONCAT(UInt,N)
#define   UINTID(N)    UINTID_X(N)

#define   UITD_X(N)    JOIN(CONCAT(uint,N),t)
#define     UITD(N)    UITD_X(N)

#define   UIID_X(N)    JOIN(CONCAT(uint,N),p)
#define     UIID(N)    UIID_X(N)

#define     PJ_X(A, B) A ## / ## B
#define       PJ(A, B) PJ_X(A,B)

#define      H_X(x)    x ## ES ## h
#define        H(x)    H_X(x) 


#define  PATH5(A, B, C, D, E) PJ(A, PJ(B, PJ(C, PJ(D, E))))
#define  PATH4(A, B, C, D)    PJ(A, PJ(B, PJ(C, D)))
#define  PATH3(A, B, C)       PJ(A, PJ(B, C))
#define  PATH2(A, B)          PJ(A, B)
#define  PATH1(A)					A



#define  PP_PATH(...) QUOTE(_VARG5(__VA_ARGS__, PATH5, PATH4, PATH3, PATH2, PATH1)(__VA_ARGS__))
